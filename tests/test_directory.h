#pragma once

#include <string>
#include <memory>

namespace boost { namespace filesystem { class path; } }

// A temporary virtual directory w/ accessors for testing View_state
class Test_directory
{
public:
    Test_directory();
    ~Test_directory(); // recursively cleanup any contents of base directory

    // Returns the base directory on the file system
    std::string base_directory() const;
    const boost::filesystem::path &base_path() const { return *temp_dir_; }

    // create a directory relative to the temp_dir_
    void mkdir(const std::string &relative_path);

    // also makes any necessary directories and writes content to
    void write_file(const std::string &relative_path, const std::string &content = "data");

private:
    std::unique_ptr<boost::filesystem::path> temp_dir_;
};
