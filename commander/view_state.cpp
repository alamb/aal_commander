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
    auto new_path = *cwd_ / fs::path(relative_path);

    if (!fs::exists(new_path))
    { throw std::runtime_error("No such directory: "  + new_path.string()); }
    if (!fs::is_directory(new_path))
    { throw std::runtime_error("Path not directory: " + new_path.string()); }

    // interpret all . and .. paths
    new_path = fs::canonical(new_path);

    // all checks are good, make the change
    auto new_cwd = std::make_unique<fs::path>(new_path);
    std::swap(cwd_, new_cwd);
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
    dirs.push_back("..");
    return dirs;
}

static inline std::string to_formatted_string(const fs::path &p)
{
    std::string d_string = fs::is_directory(p) ? "(d) " : "(f) ";
    return d_string + p.filename().string();
}


std::vector<std::string> View_state::get_directory_listing(const std::string &dir) const
{
    fs::path dir_path = *cwd_ / fs::path(dir);
    if (!fs::exists(dir_path))
    {
        throw std::runtime_error("Unknown file or path: "  + dir_path.string());
    }

    if (!fs::is_directory(dir_path))
    {
        return { to_formatted_string(dir_path) };
    }

    std::vector<std::string> ret;
    for (fs::directory_iterator itr(dir_path); itr != fs::directory_iterator(); ++itr)
    {
        ret.push_back(to_formatted_string(itr->path()));
    }
    return ret;

}
