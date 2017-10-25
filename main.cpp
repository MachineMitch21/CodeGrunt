#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <sys/stat.h>

#define VERSION "0.0.2"

std::vector<std::string> fileList;
std::vector<std::string> excludedFiles;

int linesInBiggestFile = 0;
std::string biggestFile;

std::vector<std::string> listdir(const char *path);
int countNumberLines(const std::string& file);
bool isExcluded(const std::string& file);
bool isDirectory(const std::string& path);

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

    std::cout << "Locating files..." << std::endl << std::endl;
    fileList = listdir(argv[1]);

    int totalLinesFound = 0;

    std::cout << "Counting files..." << std::endl << std::endl;
    for (int i = 0; i < fileList.size(); i++)
    {
        if (!isExcluded(fileList[i]))
            totalLinesFound += countNumberLines(fileList[i]);
    }

    std::cout << "TOTAL LINES FOUND:    " << totalLinesFound << std::endl << std::endl;

    std::cout << "Biggest FILE:         " << biggestFile << std::endl << std::endl;

    std::cout << "Biggest FILE LINES:   " << linesInBiggestFile << std::endl << std::endl;
    return 0;
}

std::vector<std::string> listdir(const char* path)
{
    std::vector<std::string> fileList;

    struct dirent *entry;
    DIR *dp;

    dp = opendir(path);
    if (dp == NULL) {
        printf("opendir: Path %s does not exist or could not be read.", path);
        exit(-1);
    }

    int fileCount = 0;
    while ((entry = readdir(dp)))
    {
        fileCount++;

        std::vector<std::string> subDirectoryFileList;

        std::string name = std::string(path) + std::string(entry->d_name);

        // We do not want to include current and previous directory entries
        // in the fileList ('.' and '..' and the 1st and 2nd entries in dirent struct)
        if (fileCount > 2)
        {
            if (isDirectory(name))
            {
                // We have to append a backslash at the end of subdirectory entries
                name += "\\";
                // Recursively find all files in all subdirectories as well
                subDirectoryFileList = listdir(name.c_str());
            }
            else
            {
                fileList.push_back(name);
            }
        }

        for (int i = 0; i < subDirectoryFileList.size(); i++)
        {
            fileList.push_back(subDirectoryFileList[i]);
        }
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

    if (numberOfLines > linesInBiggestFile)
    {
        biggestFile = path;
        linesInBiggestFile = numberOfLines;
    }

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

bool isDirectory(const std::string& path)
{
    struct stat s;
    bool isDirectory = false;

    if (stat(path.c_str(), &s) == 0)
    {
        if( s.st_mode & S_IFDIR )
        {
            isDirectory = true;
        }
        else
        {
            isDirectory = false;
        }
    }

    return isDirectory;
}
