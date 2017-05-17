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

  std::string              run_command(const Parsed_line &line);
  Command&                 get_command(const Parsed_line &line);
  std::vector<std::string> get_possible_completions(const Parsed_line &line);

private:
  const std::vector<std::unique_ptr<Command>> commands_;
};

