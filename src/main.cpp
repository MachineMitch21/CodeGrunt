#include <iostream>
#include <cmath>

#ifdef __MINGW32__
#include <mingw.thread.h>
#include <mingw.mutex.h>
#else
#include <thread>
#endif // __WIN32_MINGW__

#include <deque>
#include <ctime>

#include "LineCounter.h"
#include "DirectoryParser.h"
#include "SearchManager.h"
#include "FileManager.h"
#include "ArgumentParser.h"

using namespace lc;

#define VERSION "0.2.5"

#define PERCENTAGE_STEP 5

void processFile(std::string& file)
{
    FileManager fileManager;
    fileManager.processFile(file);
}

int main(int argc, char** argv)
{
    std::clock_t start;
    double duration;
    start = std::clock();

    unsigned int nThreads = std::thread::hardware_concurrency();

    nThreads -= 1;

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


    // Erase all excluded files
    // TODO: Do this better
    for (unsigned int i = 0; i < fileList.size(); i++)
    {
        if (dirParser.isExcluded(fileList[i]))
        {
            fileList.erase(fileList.begin() + i);
        }
    }

    int fileListSize = fileList.size();

    std::deque<std::string> fileQueue(fileList.begin(), fileList.end());

    std::vector<std::thread> threads;

    int fileIndex = 0;
    while (!fileQueue.empty())
    {
        for (unsigned int i = 0; i < nThreads; i++)
        {
            // Generate a new thread while there are still items in the deque
            if (!fileQueue.empty())
            {
                std::string file = fileQueue.back();
                fileQueue.pop_back();

                threads.push_back(std::thread(processFile, std::ref(file)));
            }
        }

        // Make sure all our current threads finish executing before we destroy them
        // and start all over again
        for (unsigned int i = 0; i < threads.size(); i++)
        {
            threads[i].join();
        }

        fileIndex += threads.size();
        threads.clear();

        // Check the percent of the fileList that has been checked so far
        int percentage = round(((float)(fileIndex) / (float)fileListSize) * 100.0f);
        if (percentage >= lastPercentageCheck + PERCENTAGE_STEP)
        {
            // Only display percentages every 5% as to not spam the console
            std::cout << "[" << percentage << "%]" << std::endl;
            lastPercentageCheck = percentage;
        }
    }

    std::cout << std::endl << std::endl;

    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

    std::cout << "Execution took: " << duration << " seconds." << std::endl << std::endl;

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
