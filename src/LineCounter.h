
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
    public:
        static void         countNumberLines(const std::string& file);
        static void         setBiggestFile(BiggestFile file);
        static BiggestFile  getBiggestFile();
        static int          getTotalLines();

    private:
        LineCounter();
        ~LineCounter();

    private:
        static int          _totalLinesFound;
        static BiggestFile  _biggestFile;
    };
}

#endif // LINECOUNTER_H
