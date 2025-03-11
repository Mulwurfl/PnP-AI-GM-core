#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>

class FileLoader {
public:
    FileLoader();
    std::string loadFile(const std::string& fileName);
};

#endif // FILELOADER_H


