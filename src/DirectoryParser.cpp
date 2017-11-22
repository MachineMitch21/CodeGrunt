
#include "DirectoryParser.h"
#include <iostream>

namespace codegrunt
{
    DirectoryParser::DirectoryParser(const std::string& directory, bool doParse)
    :   _directoryToParse(directory)
    {
        verifySeperator(_directoryToParse);

        if (doParse)
        {
            parse();
        }
    }

    DirectoryParser::~DirectoryParser()
    {

    }

    void DirectoryParser::addExtFilter(const std::string& filter)
    {
        _extFilters.push_back(filter);
    }

    void DirectoryParser::addAllExtFilters(const std::vector<std::string>& filters)
    {
        _extFilters = filters;
    }

    bool DirectoryParser::hasFilteredExt(const std::string& file)
    {
        // Only check for an extension on the given (file) string
        // if _extFilters vector has elements
        if (_extFilters.size() > 0)
        {
            std::size_t lastPeriod = file.find_last_of('.');
            std::string ext;

            if (lastPeriod != std::string::npos)
            {
                ext = file.substr(lastPeriod, file.length() - lastPeriod);

                for (unsigned int i = 0; i < _extFilters.size(); i++)
                {
                    if (ext == _extFilters[i])
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        // Default to true if execution reaches this point
        return true;
    }

    void DirectoryParser::addExcludedFile(const std::string& file)
    {
        _excludedFiles.push_back(file);
    }

    void DirectoryParser::addAllExcludedFiles(const std::vector<std::string>& files)
    {
        _excludedFiles = files;
    }

    bool DirectoryParser::isExcluded(const std::string& file)
    {
        for (unsigned int i = 0; i < _excludedFiles.size(); i++)
        {
            if (findNameInPath(file) == findNameInPath(_excludedFiles[i]))
            {
                return true;
            }
        }

        return false;
    }

    std::vector<std::string>& DirectoryParser::getFileList()
    {
        return _fileList;
    }

    void DirectoryParser::parse()
    {
        _fileList = listdir(_directoryToParse);
    }

    std::vector<std::string> DirectoryParser::listdir(const std::string& path)
    {
        std::vector<std::string> fileList;

        struct dirent *entry;
        DIR *dp;

        dp = opendir(path.c_str());
        if (dp == NULL) {
            printf("opendir: Path %s does not exist or could not be read.", path.c_str());
            exit(-1);
        }

        int fileCount = 0;
        while ((entry = readdir(dp)))
        {
            fileCount++;

            std::vector<std::string> subDirectoryFileList;

            std::string name = path + std::string(entry->d_name);

            // We do not want to include current and previous directory entries
            // in the fileList ('.' and '..' and the 1st and 2nd entries in dirent struct)
            if (fileCount > 2)
            {
                if (isDirectory(name))
                {
                    // We have to append a backslash at the end of subdirectory entries
                    verifySeperator(name);
                    // Recursively find all files in all subdirectories as well
                    subDirectoryFileList = listdir(name);
                }
                else
                {
                    // Go ahead and check internally whether or not a fileName is excluded from
                    // processing or not
                    if (!isExcluded(name) && hasFilteredExt(name))
                    {
                        fileList.push_back(name);
                    }
                }
            }

            for (unsigned int i = 0; i < subDirectoryFileList.size(); i++)
            {
                fileList.push_back(subDirectoryFileList[i]);
            }
        }

        closedir(dp);

        return fileList;
    }


    bool DirectoryParser::isDirectory(const std::string& path)
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

    void DirectoryParser::verifySeperator(std::string& directory)
    {
        if (isDirectory(directory))
        {
            std::string finalChar = directory.substr(directory.length() - 1, 1);

            // Append a backslash if there isn't one so listdir recieves correct input format
            if (finalChar != "\\" && finalChar != "/")
            {
                directory += "/";
            }
        }
    }

    std::string DirectoryParser::findNameInPath(const std::string& path)
    {
        bool foundSeperator = false;

        int length      = path.length();
        int lastIndex   = length - 1;

        std::string name = "";

        // Iterate in reverse over through the path
        // Until a seperator character is found
        for (int i = lastIndex; i >= 0; i--)
        {
            if (path[i] == '\\' || path[i] == '/')
            {
                foundSeperator = true;

                // i is at seperator so we need the char at the index ahead of i
                // length - 1 gives us the length of the file name in the path
                name = path.substr(i + 1, length - i);
                break;
            }
        }

        if (!foundSeperator)
        {
            name = path;
        }

        return name;
    }
}
