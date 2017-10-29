#include <iostream>
#include <cmath>

#include "LineCounter.h"
#include "DirectoryParser.h"
#include "SearchManager.h"
#include "FileManager.h"
#include "ArgumentParser.h"

using namespace lc;

#define VERSION "0.2.5"

#define PERCENTAGE_STEP 5

int main(int argc, char** argv)
{
    ArgumentParser argParser;
    PARSE_STAT p_stat = argParser.parseArgs(argc, argv);

    if (p_stat != PARSE_STAT::PARSE_OKAY)
    {
        std::cout << "USAGE: lines [directory] (optional commands) --search [words/phrases to search for] --exclude [files-to-exclude]" << std::endl;
    }

    if (p_stat == PARSE_STAT::PARSE_INVALID_DIRECTORY)
    {
        std::cerr << "ERROR: Unknown directory was specified or you didn't specify one" << std::endl << std::endl;
        return -1;
    }
    else if (p_stat == PARSE_STAT::PARSE_INVALID_COMMAND)
    {
        std::cerr << "ERROR: Unknown command was used" << std::endl << std::endl;
        return -1;
    }
    else if (p_stat == PARSE_STAT::PARSE_UNKOWN_ERROR)
    {
        std::cerr << "ERROR: An Unknown error has occured" << std::endl << std::endl;
        return -1;
    }

    std::cout << "\n\n\n--------------- LINES -- VERSION " << VERSION << "----------------\n\n\n";

    DirectoryParser dirParser(argParser.getDirectory(), false);
    FileManager fileManager;

    SearchManager::addAllCriteria(argParser.getCommandArguments(COMMAND::SEARCH));
    dirParser.addAllExcludedFiles(argParser.getCommandArguments(COMMAND::EXCLUDE));

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


    std::map<std::string, SearchData> searchResults = SearchManager::getAllSearchData();

    if (searchResults.size() > 0)
    {
        std::cout << "-----------------------Search Criteria-------------------------" << std::endl << std::endl;

        for (std::map<std::string, SearchData>::iterator it = searchResults.begin(); it != searchResults.end(); ++it)
        {
            std::string criteria    = it->first;
            SearchData results      = it->second;

            std::cout << "SEARCH CRITERIA (" << criteria << ") appeared " << results.NumOccurences << " times." << std::endl << std::endl;
        }

        std::cout << "--------------------END SEARCH CRITERIA------------------------" << std::endl << std::endl;
    }
    return 0;
}
