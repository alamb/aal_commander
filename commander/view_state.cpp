#include "view_state.h"

#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

View_state::View_state() :
    cwd_(std::make_unique<fs::path>(fs::current_path()))
{}


View_state::~View_state()
{
}


std::string View_state::cwd() const
{
    return cwd_->filename().string();
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



  