#include "FileManager.h"

namespace lc
{
    FileManager::FileManager()
    {

    }

    FileManager::~FileManager()
    {

    }

    void FileManager::processFile(const std::string& path)
    {
        std::ifstream fis(path);

        int numberOfLines = 0;

        if (fis.is_open())
        {
            std::string line;
            while(std::getline(fis, line))
            {
                SearchManager::searchLine(path, line);
                numberOfLines++;
            }
        }

        LineCounter::updateCount(path, numberOfLines);

        fis.close();
    }
}
