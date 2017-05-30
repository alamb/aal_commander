#include "test_directory.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>

namespace fs = boost::filesystem;

Test_directory::Test_directory() :
    temp_dir_(std::make_unique<fs::path>(fs::temp_directory_path() / fs::unique_path("aal_temp_dir-%%%%%%%")))
{
//    std::cout << "Using temp directory " << temp_dir_->string() << std::endl;
}

Test_directory::~Test_directory()
{
    try 
    {
        fs::remove_all(*temp_dir_);
    }
    catch (std::exception &e) 
    {
        std::cerr << "WARNING: can't remove temporary test dir " << temp_dir_->string() << std::endl;
    }
}

std::string Test_directory::base_directory() const
{
    return temp_dir_->string();
}

void Test_directory::mkdir(const std::string &relative_path)
{
    fs::create_directories(*temp_dir_ / fs::path(relative_path));
}

// also makes any necessary directories and writes content to
void Test_directory::write_file(const std::string &relative_path, const std::string &content)
{
    fs::path target_path = *temp_dir_ / fs::path(relative_path);
    fs::path src_dir = target_path.parent_path();
    if (!src_dir.empty()) 
    {
        //std::cout << "Creating director(ies): " << src_dir.string() << std::endl; 
        fs::create_directories(src_dir); 
    }

    //std::cout << "Writing content to " << target_path.string() << std::endl;
    fs::ofstream ofs(target_path, std::ios_base::binary | std::ios_base::out);
    if (!ofs) 
    { 
        throw std::runtime_error("Error writing to " + target_path.string());
    }
    ofs << content;
}
