#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <array>
#include <utility>
#include "KVStore.hpp"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
  tcp::socket m_socket;
  std::array<char, 1024> m_data{};
  std::string m_command;

  std::shared_ptr<KVStore> m_store;

  void parse_bytes();
  
public:
  Session(tcp::socket socket, std::shared_ptr<KVStore> store)
      : m_socket(std::move(socket)), m_store(std::move(store)){}

  void start();
  void do_read();
  void do_write(size_t length);
};
