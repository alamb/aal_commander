#include "ls_command.h"
class DIR_Command : public LS_Command
{
public:
    DIR_Command(View_state &state) : LS_Command("dir", state) {}
};
