
#ifndef LINECOUNTER_H
#define LINECOUNTER_H

#include "FileManager.h"
#include <string>
#include <fstream>

namespace codegrunt
{
    typedef struct
    {
        std::string Name;
        int Lines;
        int Size;
    }   BiggestFile;

    class LineCounter
    {

        friend class FileManager;

    public:
        LineCounter();
        ~LineCounter();
        static BiggestFile  getBiggestFile();
        static int          getTotalLines();

    private:
        static int          _totalLinesFound;
        static BiggestFile  _biggestFile;

    private:
        void         setBiggestFile(BiggestFile file);
        void         updateCount(const std::string& file, int numberOfLines);
    };
}

#endif // LINECOUNTER_H
