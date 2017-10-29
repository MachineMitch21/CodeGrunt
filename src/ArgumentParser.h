#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <map>
#include <vector>
#include <string>

namespace lc
{
    enum COMMAND
    {
        EXCLUDE     = 0,
        SEARCH      = 1
    };

    enum PARSE_STAT
    {
        PARSE_OKAY              = 0,
        PARSE_INVALID_COMMAND   = 1,
        PARSE_INVALID_DIRECTORY = 2,
        PARSE_UNKOWN_ERROR      = 3
    };

    class ArgumentParser
    {
    public:
        ArgumentParser();
        ~ArgumentParser();

        std::string getDirectory();
        std::vector<std::string> getCommandArguments(COMMAND cmd);
        PARSE_STAT parseArgs(int argc, char** argv);

    private:
        bool isCommand(const std::string& arg);

        std::string                                 _directory;
        std::map<std::string, COMMAND>              _commands;
        std::map<COMMAND, std::vector<std::string>> _cmdArgs;
    };
}

#endif // ARGUMENTPARSER_H
