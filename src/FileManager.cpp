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

        std::ifstream ifs(path);

        int numberOfLines = 0;

        if (ifs.is_open())
        {
            std::string line;
            while(std::getline(ifs, line))
            {
                searchManager.searchLine(path, line);
                numberOfLines++;
            }
        }

        lineCounter.updateCount(path, numberOfLines);

        ifs.close();
    }

    std::string FileManager::readFile(const std::string& path)
    {
        std::ifstream ifs(path);
        std::string src;

        if (ifs.is_open())
        {
            std::string line;
            while (std::getline(ifs, line))
            {
                src += line;
                src += "\0";
            }
        }

        ifs.close();
        return src;
    }

    std::vector<std::string> FileManager::readFileLines(const std::string& path)
    {
        std::ifstream ifs(path);
        std::vector<std::string> lines;

        if (ifs.is_open())
        {
            std::string line;
            while (std::getline(ifs, line))
            {
                lines.push_back(line);
            }
        }

        ifs.close();
        return lines;
    }

    int FileManager::fileSize(const std::string& path)
    {
        std::ifstream ifs;

        ifs.open(path, std::ios::binary);
        return fileSize(ifs);
    }

    int FileManager::fileSize(std::ifstream& ifs)
    {
        ifs.seekg(0, std::ios::end);

        return ifs.tellg();
    }
}
