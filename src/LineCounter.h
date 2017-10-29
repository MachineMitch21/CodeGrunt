
#ifndef LINECOUNTER_H
#define LINECOUNTER_H

#include <string>
#include <fstream>

namespace lc
{
    typedef struct
    {
        int Lines;
        std::string Name;
    }   BiggestFile;

    class LineCounter
    {

        friend class FileManager;

    public:
        static BiggestFile  getBiggestFile();
        static int          getTotalLines();

    private:
        LineCounter();
        ~LineCounter();

    private:
        static void         setBiggestFile(BiggestFile file);
        static void         updateCount(const std::string& file, int numberOfLines);
        static int          _totalLinesFound;
        static BiggestFile  _biggestFile;
    };
}

#endif // LINECOUNTER_H
