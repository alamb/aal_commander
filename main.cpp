#include "commander/view_state.h"
#include "commander/linenoise.h"
#include "commander/command_registry.h"
#include "commander/commands.h"
#include "commander/command.h"
#include "commander/hints.h"
#include "commander/parsed_line.h"

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

// sadly linenoise requires a global -- we 
// could thread through a user data or thread local
//  if this really irks someone in the future
static View_state   g_state;
static Commands     g_commands(Command_registry::get_commands(g_state));

// memory management for prompt/hints
Hints g_hints;

static void completion_shim(const char *buf, linenoiseCompletions *lc)
{
    Parsed_line line(buf);

    for (const std::string &s : g_commands.get_possible_completions(line))
    {
        linenoiseAddCompletion(lc, s.c_str());
    }
}

static const char *hints_shim(const char *buf, int *color, int *bold)
{
    Parsed_line line(buf);

    g_hints = Hints(line, g_commands.get_possible_completions(line));

    *color = g_hints.color();
    *bold  = g_hints.bold() ? 1 : 0;
    return g_hints.hint_text().c_str();
}

int main(int argc, char **argv)
{

    /* Set the completion callback. This will be called every time the
     * user uses the <tab> key. */
    linenoiseSetCompletionCallback(completion_shim);
    linenoiseSetHintsCallback(hints_shim);

    /* Load history from file. The history file is just a plain text file
     * where entries are separated by newlines. */
    linenoiseHistoryLoad("history.txt"); /* Load the history at startup */
    linenoiseSetMultiLine(1);

    /* Now this is the main loop of the typical linenoise-based application.
     * The call to linenoise() will block as long as the user types something
     * and presses enter.
     *
     * The typed string is returned as a malloc() allocated string by
     * linenoise, so the user needs to free() it. */
    char *line;
    while ((line = linenoise("command> ")) != NULL && !g_state.exit_requested())
    {
        try
        {
            Parsed_line parsed_line(line);
            std::cout << g_commands.run_command(parsed_line) << std::endl;
            linenoiseHistoryAdd(line);           /* Add to the history. */
            linenoiseHistorySave("history.txt"); /* Save the history on disk. */
        }
        catch (std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        free(line);
        if (g_state.exit_requested()) break;
    }
    return 0;
}
