#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "LineCounter.h"
#include "SearchManager.h"

#include <fstream>
#include <string>
#include <vector>

namespace codegrunt
{
    class FileManager
    {
    public:
        FileManager();
        ~FileManager();

        void processFile(const std::string& path);
        std::string readFile(const std::string& path);
        std::vector<std::string> readFileLines(const std::string& path);
        int fileSize(const std::string& path);
        int fileSize(std::ifstream& ifs);

    private:
    };
}

#endif // FILEMANAGER_H
