#include "../include/KVStore.hpp"
#include <mutex>

void KVStore::set(const std::string& key, const std::string& value){
  std::unique_lock lock(m_smutex);

  m_data.insert_or_assign(key, value);
}

auto KVStore::get(const std::string& key) const -> std::optional<std::string>{
  std::shared_lock lock(m_smutex);
  
  auto iter = m_data.find(key);

  if(iter != m_data.end()){
    return iter->second;
  }

  return std::nullopt;
}

void KVStore::remove(const std::string& key){
  std::unique_lock lock(m_smutex);

    m_data.erase(key);
}

