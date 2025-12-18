#pragma once
#include <string>
#include <shared_mutex>
#include <unordered_map>
#include <optional>

class KVStore {
  std::unordered_map<std::string, std::string> m_data;
  std::shared_mutex m_smutex;

public:
  void set(const std::string& key, const std::string& value);
  auto get(const std::string& key) const -> std::optional<std::string>;
  void remove(const std::string& key);
};
