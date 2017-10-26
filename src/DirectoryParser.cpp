
#include "DirectoryParser.h"

namespace lc
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
            if (file == _excludedFiles[i])
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
                    fileList.push_back(name);
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
                directory += "\\";
            }
        }
        else
        {
            std::cerr << "ERROR: Trying to add seperator to file.  Action ignored" << std::endl;
        }
    }
}
