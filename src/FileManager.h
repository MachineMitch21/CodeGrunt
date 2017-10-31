#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "LineCounter.h"
#include "SearchManager.h"

#include <fstream>

namespace codegrunt
{
    class FileManager
    {
    public:
        FileManager();
        ~FileManager();

        void processFile(const std::string& path);

    private:
        std::string readFile(const std::string& path);
    };
}

#endif // FILEMANAGER_H
