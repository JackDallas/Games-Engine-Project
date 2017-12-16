#include "FileUtils.h"

#include "Logger.h"

// todo some cross platform support would be nice here
//I think this covers 32 and 64 while WIN32 is just 32
#ifdef _WIN32
#include <windows.h>
#endif

std::string FileUtils::getExePath()
{
    char result[ MAX_PATH ];
    //Finds the path to the exe
    std::string filePath = std::string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
    //Removes the exe part leaving the containing folder
    std::string folderPath = filePath.substr(0,filePath.find_last_of("\\"));
    return folderPath;
}
std::string FileUtils::getProgramPath() {
//pre made for future cross platform
    return getExePath();

}
std::string FileUtils::readFileToString(std::string filePath) {
    std::string content;
    std::ifstream fileStream;

    fileStream.open(filePath);

    if (!fileStream.is_open()) {
        Logger::Error("Could not read file " + filePath + " . File does not exist.");
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}
/*std::ifstream FileUtils::readFileToStream(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        //Logger::Error("Could not read file " + filePath + ". File does not exist.");
        return nullptr;
    }

    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}*/