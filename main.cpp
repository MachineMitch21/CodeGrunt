#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>

#define VERSION "0.0.2"

std::vector<std::string> fileList;
std::vector<std::string> excludedFiles;

std::vector<std::string> listdir(const char *path);
int countNumberLines(const std::string& file);
bool isExcluded(const std::string& file);

int main(int argc, char** argv)
{

    if (argc > 2)
    {
        for (int i = 2; i < argc; i++)
        {
            excludedFiles.push_back(std::string(argv[i]));
        }
    }

    std::cout << "\n\n\n--------------- LINES -- VERSION " << VERSION << "----------------\n\n\n";

    if (argc < 2)
    {
        std::cerr << "Usage: lines [directory-of-source-files] (Excluding files is optional) [files-to-exclude]" << std::endl;
        return -1;
    }

    fileList = listdir(argv[1]);

    int totalLinesFound = 0;

    for (int i = 0; i < fileList.size(); i++)
    {
        if (!isExcluded(fileList[i]))
            totalLinesFound += countNumberLines(std::string(argv[1]) + fileList[i]);
    }

    std::cout << "LINES FOUND: " << totalLinesFound << std::endl << std::endl;
    return 0;
}

std::vector<std::string> listdir(const char* path)
{
    std::vector<std::string> fileList;

    struct dirent *entry;
    DIR *dp;

    dp = opendir(path);
    if (dp == NULL) {
        perror("opendir: Path does not exist or could not be read.");
        exit(-1);
    }

    int fileCount = 0;
    while ((entry = readdir(dp)))
    {
        fileCount++;

        std::string name = std::string(entry->d_name);
        if (fileCount > 2)
            fileList.push_back(name);
    }

    closedir(dp);

    return fileList;
}

int countNumberLines(const std::string& path)
{
    std::ifstream fis(path);

    int numberOfLines = 0;

    if (fis.is_open())
    {
        std::string line;
        while(std::getline(fis, line))
        {
            numberOfLines++;
        }
    }

    fis.close();

    return numberOfLines;
}

bool isExcluded(const std::string& file)
{
    for (int i = 0; i < excludedFiles.size(); i++)
    {
        if (file == excludedFiles[i])
        {
            return true;
        }
    }

    return false;
}
