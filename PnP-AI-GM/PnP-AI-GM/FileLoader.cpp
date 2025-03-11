#include "FileLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>

FileLoader::FileLoader() {}

std::string FileLoader::loadFile(const std::string& fileName) {
    std::ifstream file(fileName);
    std::stringstream buffer;

    if (file) {
        buffer << file.rdbuf();  // Read file contents into stringstream
        if (!buffer.str().empty()) {
            return buffer.str();
        }
        else {
            return "#!#!#! error Failed to load file.";
        }
    }
    else {
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        return "#!#!#! error Unable to open file";
    }
}
