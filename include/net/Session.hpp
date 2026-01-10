#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <array>
#include <utility>
#include "../core/KVStore.hpp"
#include "../core/Parser.hpp"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
  tcp::socket m_socket;
  std::array<char, 1024> m_data{};
  std::string m_response;
  int m_id{};

  std::shared_ptr<KVStore> m_store;

  void make_response(const Command& cmd);

public:
  Session(const Session &) = delete;
  Session(Session &&) = delete;
  auto operator=(const Session &) -> Session & = delete;
  auto operator=(Session &&) -> Session & = delete;
  Session(tcp::socket socket, std::shared_ptr<KVStore> store, int sId)
      : m_socket(std::move(socket)), m_id(sId), m_store(std::move(store)) {}
  ~Session();

  void start();
  void do_read();
  void do_write(size_t length);
};
