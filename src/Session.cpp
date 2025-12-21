#include "../include/Session.hpp"
#include <boost/asio/error.hpp>
#include <boost/asio/write.hpp>
#include <boost/log/trivial.hpp>

Session::~Session(){
  BOOST_LOG_TRIVIAL(info) << "Succesfully destroyed #" << m_id << " session";
}

void Session::make_response(const Command& cmd){
  if(cmd.type == CmdType::SET){
    m_store->set(cmd.key, cmd.value.value_or(" "));
    m_response = "Set " + cmd.value.value_or(" ") + " at key: " + cmd.key + '\n';

  } else if(cmd.type == CmdType::GET){
    auto value = m_store->get(cmd.key);
    if (value) {
        m_response = *value + "\n";
    } else {
        m_response = "NOT_FOUND\n";
    }
  } else if(cmd.type == CmdType::REMOVE){
    m_response = "Deleted field at: " + cmd.key + '\n';

  } else if(cmd.type == CmdType::UNKNOWN){
    m_response = "No such command. Try:\nGET [key]\nSET [key] [value]\nREMOVE [key]\n";
  }
}

void Session::start() {
 try {

    auto endpoint = m_socket.remote_endpoint();
    BOOST_LOG_TRIVIAL(info) << "Session #" << m_id
                            << " started for client: "
                            << endpoint.address().to_string();

  } catch (const std::exception& exc) {
    BOOST_LOG_TRIVIAL(error) << "Session #" << m_id
                             << " cant reach endpoint:" << exc.what();
  }

  do_read();
}

void Session::do_read(){
  auto self(shared_from_this());

  BOOST_LOG_TRIVIAL(trace) << "Session #" << m_id << " is waiting for data...";

  m_socket.async_read_some(boost::asio::buffer(m_data),
                           [this, self](boost::system::error_code erc, size_t length) -> void{
                            if(!erc){
                              Command cmd;

                              cmd = Parser::parse(std::string_view(m_data.data(), length));

                              make_response(cmd);

                              BOOST_LOG_TRIVIAL(debug) << "Session #" << m_id << " received"
                                                       << length << " bytes";
                              do_write(m_response.size());
                            } else if(erc == boost::asio::error::eof){
                              BOOST_LOG_TRIVIAL(info) << "Session #" << m_id << " disconnected";
                            } else if(erc == boost::asio::error::operation_aborted){
                              BOOST_LOG_TRIVIAL(warning) << "Session #" << m_id << " aborted";
                            } else {
                              BOOST_LOG_TRIVIAL(error) << "Session #" << m_id << " read error: "
                                                       << erc.message();
                            }
                           });
}

void Session::do_write(size_t length){
  auto self(shared_from_this());

  BOOST_LOG_TRIVIAL(trace) << "Session #" << m_id << "sending " << length << "bytes";

  boost::asio::async_write(m_socket,
                           boost::asio::buffer(m_response, length),
                           [this, self](boost::system::error_code erc, size_t bytes_send) -> void{
                              if(!erc){
                                BOOST_LOG_TRIVIAL(debug) << "Session #" << m_id 
                                                         << " sent " << bytes_send << " bytes";
                                do_read();
                              } else {
                                BOOST_LOG_TRIVIAL(error) << "Session #" << m_id 
                                                         << " write error: " << erc.message();
                              }
                           });
}
