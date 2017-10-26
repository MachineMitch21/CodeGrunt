#include <iostream>
#include <cmath>

#include "LineCounter.h"
#include "DirectoryParser.h"

using namespace lc;

#define VERSION "0.1.0"

#define PERCENTAGE_STEP 5

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

    int lastPercentageCheck = 0;

    for (unsigned int i = 0; i < fileList.size(); i++)
    {
        if (!dirParser.isExcluded(fileList[i]))
        {
            // Check the percent of the fileList that has been checked so far
            int percentage = round(((float)(i + 1) / (float)fileList.size()) * 100.0f);
            if (percentage >= lastPercentageCheck + PERCENTAGE_STEP)
            {
                // Only display percentages every 5% as to not spam the console
                std::cout << "[" << percentage << "%]" << std::endl;
                lastPercentageCheck = percentage;
            }

            LineCounter::countNumberLines(fileList[i]);
        }
    }

    std::cout << "TOTAL LINES FOUND:    " << LineCounter::getTotalLines() << std::endl << std::endl;

    std::cout << "Biggest FILE:         " << LineCounter::getBiggestFile().Name << std::endl << std::endl;

    std::cout << "Biggest FILE LINES:   " << LineCounter::getBiggestFile().Lines << std::endl << std::endl;
    return 0;
}
