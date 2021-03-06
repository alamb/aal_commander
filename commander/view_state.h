#pragma once

#include <memory>
#include <string>
#include <vector>

namespace boost { namespace filesystem { class path; } }

/**
 * Manages the 'state' of the commander (for example the working directory)
 */
class View_state
{
public:
    View_state();
    View_state(const std::string &initial_dir);
    virtual ~View_state();

    // return the current working directory
    virtual std::string pwd() const;

    // change the current working directory relative to pwd.
    // throws exception if no such path
    virtual void cd(const std::string &relative_path);

    // return all subdirectories of the current working directory
    virtual std::vector<std::string> get_directories() const;

    // lists the contents of the specified directory in a format suitable for display
    virtual std::vector<std::string> get_directory_listing(const std::string &dir) const;

    bool exit_requested() const { return exit_requested_; }
    void set_exit_requested()   { exit_requested_ = true; }

private:
    bool exit_requested_ = false;
    std::unique_ptr<boost::filesystem::path> cwd_;
};
