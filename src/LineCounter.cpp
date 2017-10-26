
#include "LineCounter.h"

namespace lc
{
    BiggestFile LineCounter::_biggestFile;
    int         LineCounter::_totalLinesFound;

    void LineCounter::setBiggestFile(BiggestFile file)
    {
        _biggestFile = file;
    }

    BiggestFile LineCounter::getBiggestFile()
    {
        return _biggestFile;
    }

    int LineCounter::getTotalLines()
    {
        return _totalLinesFound;
    }

    void LineCounter::countNumberLines(const std::string& path)
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

        if (numberOfLines > _biggestFile.Lines)
        {
            _biggestFile.Name = path;
            _biggestFile.Lines = numberOfLines;
        }

        _totalLinesFound += numberOfLines;
    }
}
