#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

enum class CmdType : std::uint8_t{
  SET,
  GET,
  REMOVE,
  UNKNOWN
};

struct Command{
  CmdType type;
  std::string key;
  std::optional<std::string> value;
};

class Parser{
public:
  static auto parse(std::string_view line) -> Command;
};
