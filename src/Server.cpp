#include <boost/log/trivial.hpp>
#include <utility>
#include "../include/Server.hpp"

Server::Server(boost::asio::io_context& io_context, short port, std::shared_ptr<KVStore> store)
  :m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
  m_store(std::move(store)){
  BOOST_LOG_TRIVIAL(info) << "Server started on port " << port;
  do_accept();
}

void Server::do_accept(){
  m_acceptor.async_accept(
    [this](boost::system::error_code erc, tcp::socket socket) -> void {
      if(!erc){
        std::make_shared<Session>(std::move(socket), m_store, m_next_session_id) -> start();

        BOOST_LOG_TRIVIAL(info) << "New connection. [id] #" << m_next_session_id;

        m_next_session_id++;
      } else {
        BOOST_LOG_TRIVIAL(error) << "Accept error: " << erc.message();
      }

      this->do_accept();
    }
  );
}
