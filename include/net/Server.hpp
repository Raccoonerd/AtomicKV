#pragma once

#include "Session.hpp"
#include "../core/KVStore.hpp"
#include <memory>

class Server{
  tcp::acceptor m_acceptor;
  int m_next_session_id{};
  std::shared_ptr<KVStore> m_store;

  void do_accept();

public:
  Server(boost::asio::io_context& io_context, short port, std::shared_ptr<KVStore> store);
};
