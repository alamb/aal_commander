#include "ls_command.h"
/**
 * The DIR command is an alias for the LS command
 */
class DIR_Command : public LS_Command
{
public:
    DIR_Command(View_state &state) : LS_Command("dir", state) {}
};
