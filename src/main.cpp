#include "../include/Logger.hpp"
#include "../include/Server.hpp"
#include "../include/KVStore.hpp"
#include <boost/log/trivial.hpp>
#include <memory>
#include <thread>
#include <vector>


auto main (int argc, char *argv[]) -> int {
  init_logging();

  try{
    short port = 12345;

    BOOST_LOG_TRIVIAL(info) << "Starting AtomicKV server on " << port << " port...";

    auto store = std::make_shared<KVStore>();

    boost::asio::io_context io_context;

    Server server(io_context, port, store);

    auto thread_count = std::thread::hardware_concurrency();
    if(thread_count == 0){
      thread_count = 1;
    }

    std::vector<std::thread> threads;
    BOOST_LOG_TRIVIAL(info) << "Running on " << thread_count << " threads";

    threads.reserve(thread_count);

    for(int i = 0; i < thread_count; i++){
      threads.emplace_back(
        [&io_context]() -> void{
          io_context.run();
        });
    }

    for(auto& thread : threads){
      if(thread.joinable()){
        thread.join();
      }
    }

  } catch(const std::exception& exc){
    BOOST_LOG_TRIVIAL(fatal) << "Fatal error: " << exc.what();
    return 1;
  }

  return 0;
}
