#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <sys/stat.h>

#include "LineCounter.h"
#include "DirectoryParser.h"

using namespace lc;

#define VERSION "0.0.2"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: lines [directory-of-source-files] (Excluding files is optional) [files-to-exclude]" << std::endl;
        return -1;
    }

    std::cout << "\n\n\n--------------- LINES -- VERSION " << VERSION << "----------------\n\n\n";

    std::string directory = argv[1];

    DirectoryParser dirParser(directory, false);

    if (argc > 2)
    {
        for (int i = 2; i < argc; i++)
        {
            dirParser.addExcludedFile(std::string(argv[i]));
        }
    }

    std::cout << "Locating files..." << std::endl << std::endl;
    dirParser.parse();

    std::vector<std::string> fileList = dirParser.getFileList();

    std::cout << "Counting files..." << std::endl << std::endl;
    for (unsigned int i = 0; i < fileList.size(); i++)
    {
        if (!dirParser.isExcluded(fileList[i]))
            LineCounter::countNumberLines(fileList[i]);
    }

    std::cout << "TOTAL LINES FOUND:    " << LineCounter::getTotalLines() << std::endl << std::endl;

    std::cout << "Biggest FILE:         " << LineCounter::getBiggestFile().Name << std::endl << std::endl;

    std::cout << "Biggest FILE LINES:   " << LineCounter::getBiggestFile().Lines << std::endl << std::endl;
    return 0;
}
