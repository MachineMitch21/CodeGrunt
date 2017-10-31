#include "FileManager.h"

namespace codegrunt
{
    FileManager::FileManager()
    {

    }

    FileManager::~FileManager()
    {

    }

    void FileManager::processFile(const std::string& path)
    {
        SearchManager searchManager;
        LineCounter lineCounter;

        std::ifstream fis(path);

        int numberOfLines = 0;

        if (fis.is_open())
        {
            std::string line;
            while(std::getline(fis, line))
            {
                searchManager.searchLine(path, line);
                numberOfLines++;
            }
        }

        lineCounter.updateCount(path, numberOfLines);

        fis.close();
    }
}
