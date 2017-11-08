
#ifndef DIRECTORYPARSER_H
#define DIRECTORYPARSER_H

#include <string>
#include <dirent.h>
#include <vector>
#include <cstring>
#include <sys/stat.h>
#include <iostream>
#include <stdio.h>

namespace codegrunt
{
    class DirectoryParser
    {
    public:
        DirectoryParser(const std::string& directory, bool doParse);
        ~DirectoryParser();

        void addExcludedFile(const std::string& file);
        void addAllExcludedFiles(const std::vector<std::string>& files);
        bool isExcluded(const std::string& file);

        void addExtFilter(const std::string& filter);
        void addAllExtFilters(const std::vector<std::string>& filters);
        bool hasFilteredExt(const std::string& file);

        std::vector<std::string>& getFileList();

        void parse();

    private:
        std::vector<std::string> listdir(const std::string& path);
        bool isDirectory(const std::string& path);
        void verifySeperator(std::string& directory);
        std::string findNameInPath(const std::string& path);

    private:
        std::vector<std::string>    _fileList;
        std::vector<std::string>    _excludedFiles;
        std::vector<std::string>    _extFilters;
        std::string                 _directoryToParse;

    };
}

#endif // DIRECTORYPARSER_H
