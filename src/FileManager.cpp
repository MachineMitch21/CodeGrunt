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

    std::string readFile(const std::string& path)
    {
        std::ifstream fis(path);
        std::string src;

        if (fis.is_open())
        {
            std::string line;
            while (std::getline(fis, line))
            {
                src += line;
                src += "\0";
            }
        }

        return src;
    }

    std::vector<std::string> readFileLines(const std::string& path)
    {
        std::ifstream fis(path);
        std::vector<std::string> lines;

        if (fis.is_open())
        {
            std::string line;
            while (std::getline(fis, line))
            {
                lines.push_back(line);
            }
        }

        return lines;
    }
}
