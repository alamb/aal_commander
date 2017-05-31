#include "gtest/gtest.h"

#include "commander/command_registry.h"
#include "commander/view_state.h"

#include <set>


TEST(test_command_registry, list)
{
    View_state state;
    std::set<std::string> expected_commands = 
    {
        "cd", "pwd", "ls", "dir", "exit"
    };

    auto commands = Command_registry::get_commands(state);
    EXPECT_EQ(expected_commands.size(), commands.size());

    std::set<std::string> previously_seen;
    for (const auto &c : commands) 
    {
        std::string command_id = c->command_id();
        EXPECT_TRUE(expected_commands.count(command_id) == 1) << "Unexpected command " << command_id;
        EXPECT_TRUE(previously_seen.count(command_id) == 0)   << "Duplicate command: " << command_id;
        previously_seen.insert(command_id);
    }


}