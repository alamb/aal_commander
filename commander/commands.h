#pragma once

class Command;
class Parsed_line;

#include <string>
#include <vector>
#include <memory>

class Command;

/**
 * Encapsulates the list of auto complete behavior based on a list of commands.
 */
class Commands
{
public:
  Commands(std::vector<std::unique_ptr<Command>> &&commands);

  Commands() = default;
  void add_command(std::unique_ptr<Command> &&command);


  std::string              run_command(const Parsed_line &line);
  // throws exception if no known command
  Command&                 get_command(const Parsed_line &line);

  // returns full possible completion strings
  std::vector<std::string> get_possible_completions(const Parsed_line &line);
  std::vector<std::string> get_collapsed_completions(const Parsed_line &line)
  { return collapse_completions(get_possible_completions(line)); }


  // If multiple completions share a prefix, collapse them into the shared prefix
  static std::vector<std::string> collapse_completions(const std::vector<std::string> &completions);

private:
  std::vector<std::unique_ptr<Command>> commands_;
};
