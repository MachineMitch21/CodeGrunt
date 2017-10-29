#include "ArgumentParser.h"

namespace lc
{
    ArgumentParser::ArgumentParser()
    {
        _commands.emplace("--search", SEARCH);
        _commands.emplace("--exclude", EXCLUDE);

        _cmdArgs.emplace(SEARCH, std::vector<std::string> {});
        _cmdArgs.emplace(EXCLUDE, std::vector<std::string> {});
    }

    ArgumentParser::~ArgumentParser()
    {

    }

    std::string ArgumentParser::getDirectory()
    {
        return _directory;
    }

    std::vector<std::string> ArgumentParser::getCommandArguments(COMMAND cmd)
    {
        return _cmdArgs[cmd];
    }

    PARSE_STAT ArgumentParser::parseArgs(int argc, char** argv)
    {
        std::string command;

        if (argc > 1)
        {
            _directory = argv[1];

            if (argc > 2)
            {
                for (int i = 2; i < argc; i++)
                {
                    std::string arg(argv[i]);

                    if (isCommand(arg))
                    {
                        command = arg;

                        for (int j = i + 1; j < argc; j++)
                        {
                            std::string arg(argv[j]);

                            if (!isCommand(arg))
                            {
                                _cmdArgs[_commands[command]].push_back(arg);
                                i++;
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        return PARSE_INVALID_COMMAND;
                    }
                }
            }
        }
        else
        {
            return PARSE_INVALID_DIRECTORY;
        }

        return PARSE_OKAY;
    }

    bool ArgumentParser::isCommand(const std::string& arg)
    {
        for (std::map<std::string, COMMAND>::iterator it = _commands.begin(); it != _commands.end(); ++it)
        {
            if (arg == it->first)
            {
                return true;
            }
        }

        return false;
    }
}
