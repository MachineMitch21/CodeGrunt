#include "ArgumentParser.h"

namespace codegrunt
{
    ArgumentParser::ArgumentParser()
    {
        _commands.emplace("--search",   SEARCH);
        _commands.emplace("--exclude",  EXCLUDE);

        _cmdArgs.emplace(SEARCH,    std::vector<std::string> {});
        _cmdArgs.emplace(EXCLUDE,   std::vector<std::string> {});
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

        // There should at least be a directory specified as the first arguments
        // If not, we return with a PARSE_INVALID_DIRECTORY error code
        if (argc > 1)
        {
            _directory = argv[1];

            // If there are more than two arguments ([program-name] [directory])
            // Then we start parsing the extra arguments, looking for commands
            if (argc > 2)
            {
                for (int i = 2; i < argc; i++)
                {
                    std::string arg(argv[i]);

                    if (isCommand(arg))
                    {
                        command = arg;

                        // If we have found a command, then we want to start looping
                        // over the following arguments until we hit another command
                        // or we run out of arguments
                        for (int j = i + 1; j < argc; j++)
                        {
                            std::string arg(argv[j]);

                            if (!isCommand(arg))
                            {
                                // If this argument isn't a command we need to push
                                // it onto the argument list of the current command
                                // that we previously found
                                _cmdArgs[_commands[command]].push_back(arg);
                                i = j;
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
