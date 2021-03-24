#include <iostream>
#include <fstream>
#include <filesystem>

#include "OEMFile.hpp"
#include "OEMFile.cpp"

int main() {

    std::ofstream ofs;
    ofs.open("prova/data.txt");
    ofs << "Second try" << std::endl; 
    ofs.close(); 

    OEMFile oem("Satellite_","");

    std::ifstream ifs("Data/Satellite_OEM_POSITION.txt");
    std::string text;
    std::getline(ifs, text);
    std::getline(ifs,text);
    std::getline(ifs,text);
    std::getline(ifs,text);
    std::getline(ifs,text);
    std::cout<< text << std::endl;




    return 0;
}