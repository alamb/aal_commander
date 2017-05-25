#pragma once

class Command;
class Parsed_line;

#include <string>
#include <vector>
#include <memory>

class Command;

/**
 * Encapsulates auto complete behavior based on a list of commands.
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
  std::vector<std::string> get_possible_completions(const Parsed_line &line);

private:
  std::vector<std::unique_ptr<Command>> commands_;
};

