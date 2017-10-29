#include <iostream>
#include <cmath>

#include "LineCounter.h"
#include "DirectoryParser.h"
#include "SearchManager.h"
#include "FileManager.h"

using namespace lc;

#define VERSION "0.1.0"

#define PERCENTAGE_STEP 5

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: lines [directory-of-source-files]  --exclude (Excluding files is optional) [files-to-exclude]"
                                                             << "--search (Searching is optional) [words-to-search-for]" << std::endl;
        return -1;
    }

    std::cout << "\n\n\n--------------- LINES -- VERSION " << VERSION << "----------------\n\n\n";

    std::string directory = argv[1];

    DirectoryParser dirParser(directory, false);
    FileManager fileManager;

    if (argc > 2)
    {
        for (int i = 2; i < argc; i++)
        {
            std::string arg(argv[i]);

            if (arg == "--exclude")
            {
                for (int j = i + 1; j < argc; j++)
                {
                    std::string arg(argv[j]);

                    if (arg != "--search")
                    {
                        dirParser.addExcludedFile(arg);
                        i++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else if (arg == "--search")
            {
                for (int j = i + 1; j < argc; j++)
                {
                    std::string arg(argv[j]);

                    if (arg != "--exclude")
                    {
                        SearchManager::addSearchCriteria(arg);
                        i++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
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

            fileManager.processFile(fileList[i]);
        }
    }

    std::cout << std::endl;

    std::cout << "TOTAL LINES FOUND:    " << LineCounter::getTotalLines() << std::endl << std::endl;

    std::cout << "Biggest FILE:         " << LineCounter::getBiggestFile().Name << std::endl << std::endl;

    std::cout << "Biggest FILE LINES:   " << LineCounter::getBiggestFile().Lines << std::endl << std::endl;

    std::cout << "-----------------------Search Criteria-------------------------" << std::endl << std::endl;

    std::map<std::string, SearchData> searchResults = SearchManager::getAllSearchData();

    for (std::map<std::string, SearchData>::iterator it = searchResults.begin(); it != searchResults.end(); ++it)
    {
        std::string criteria    = it->first;
        SearchData results      = it->second;

        std::cout << "SEARCH CRITERIA (" << criteria << ") appeared " << results.NumOccurences << " times." << std::endl << std::endl;
    }

    std::cout << "--------------------END SEARCH CRITERIA------------------------" << std::endl << std::endl;
    return 0;
}
