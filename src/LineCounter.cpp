
#include "LineCounter.h"

namespace codegrunt
{
    BiggestFile LineCounter::_biggestFile;
    int         LineCounter::_totalLinesFound;

    LineCounter::LineCounter()
    {

    }

    LineCounter::~LineCounter()
    {

    }

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

    void LineCounter::updateCount(const std::string& file, int numberOfLines)
    {
        if (numberOfLines > _biggestFile.Lines)
        {
            FileManager fileManager;
            _biggestFile.Name = file;
            _biggestFile.Lines = numberOfLines;
            _biggestFile.Size = fileManager.fileSize(file);
        }

        _totalLinesFound += numberOfLines;
    }
}
