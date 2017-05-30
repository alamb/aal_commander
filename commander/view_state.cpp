#include "view_state.h"

#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

View_state::View_state() :
    cwd_(std::make_unique<fs::path>(fs::current_path()))
{}

View_state::View_state(const std::string &initial_dir) :
    cwd_(std::make_unique<fs::path>(initial_dir))
{
}

View_state::~View_state()
{
}

std::string View_state::pwd() const
{
    return cwd_->string();
}

void View_state::cd(const std::string &relative_path)
{
    auto new_path = std::make_unique<fs::path>
        (*cwd_ / fs::path(relative_path));

    if (!fs::exists(*new_path))       { throw std::runtime_error("No such directory: "     + new_path->string()); }
    if (!fs::is_directory(*new_path)) { throw std::runtime_error("Path not directory: " + new_path->string()); }

    // all checks are good, return
    std::swap(cwd_, new_path);
}


std::vector<std::string> View_state::get_directories() const
{
    std::vector<std::string> dirs;
    for (fs::directory_iterator itr(*cwd_); itr != fs::directory_iterator(); ++itr)
    {
        fs::path ent = itr->path();
        if (fs::exists(ent) && fs::is_directory(ent))
        {
            dirs.push_back(ent.filename().string());
        }
    }
    return dirs;
}

std::vector<std::string> View_state::get_directory_listing() const
{
    std::vector<std::string> ret;
    for (fs::directory_iterator itr(*cwd_); itr != fs::directory_iterator(); ++itr)
    {
        fs::path ent = itr->path();
        std::string d_string = fs::is_directory(ent) ? "(d) " : "(f) ";
        {
            ret.push_back(d_string + ent.filename().string());
        }
    }
    return ret;
    
}



  