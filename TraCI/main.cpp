#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <fstream>
namespace fs = std::experimental::filesystem;
 
int main()
{
    fs::path path = fs::current_path();
    std::string path_name  = path.string() + "/Car1";
    std::ofstream file (path_name.c_str(), std::ofstream::app); 
    std::cout << path_name << std::endl;
    std::string text = "hola\n"; 
    file.write(text.c_str(), text.length());

    file.close();
}