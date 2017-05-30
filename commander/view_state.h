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
    std::string pwd() const;

    // change the current working directory relative to pwd. 
    // throws exception if no such path
    void cd(const std::string &relative_path);

    // return all subdirectories of the current working directory
    std::vector<std::string> get_directories() const;

    // lists the contents of the  current working directory
    std::vector<std::string> get_directory_listing() const;

    bool exit_requested() const { return exit_requested_; }
    void set_exit_requested()   { exit_requested_ = true; }

protected:
    View_state(const std::string &initial_dir);

private:
    bool exit_requested_ = false;
    std::unique_ptr<boost::filesystem::path> cwd_;
};
