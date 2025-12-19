#include "../include/Parser.hpp"
#include <string_view>

// GET key
// SET key value with spaces
// REMOVE key

auto Parser::parse(std::string_view line) -> Command{
  Command cmd;

  auto space_pos = line.find(' ');

  std::string_view type_str = (space_pos == std::string_view::npos)
                              ? line
                              : line.substr(0, space_pos);

  if (type_str == "GET") { cmd.type = CmdType::GET; }
  else if (type_str == "SET") { cmd.type = CmdType::SET; }
  else if (type_str == "REMOVE") { cmd.type = CmdType::REMOVE; }
  else { cmd.type = CmdType::UNKNOWN; return cmd;}

  if (space_pos == std::string_view::npos) { return cmd; }

  line.remove_prefix(space_pos + 1);

  if(cmd.type == CmdType::SET){
    space_pos = line.find(' ');

    std::string_view key_str = (space_pos == std::string_view::npos)
                                ? line
                                :line.substr(0, space_pos);
    cmd.key = key_str;

    if (space_pos == std::string_view::npos) { return cmd; }

    line.remove_prefix(space_pos + 1);
  
    std::string_view value_str = line;

    cmd.value = value_str;
  } else {
    std::string_view key_str = line;
    cmd.key = key_str;
  }

 return cmd;
}
