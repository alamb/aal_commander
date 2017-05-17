#pragma once

#include <memory>
#include <string>
#include <vector>

namespace boost { namespace filesystem { class path; } }

/**
* Manages the state of what we want to show
*/
class View_state
{
public: 
    View_state();
    ~View_state();

    // return the current working directory
    std::string cwd() const;

    // return all subdirectories of the current working directory
    std::vector<std::string> get_directories() const;

private:
    std::unique_ptr<boost::filesystem::path> cwd_;
};
