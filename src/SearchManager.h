
#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <cstddef>
#include <iostream>

namespace codegrunt
{

    typedef struct
    {
        int NumOccurences;
    }   SearchData;

    class SearchManager
    {
        friend class FileManager;

    public:
        SearchManager();
        ~SearchManager();

        static void addSearchCriteria(const std::string& criteria);
        static void addAllCriteria(const std::vector<std::string>& criteria);
        static SearchData getSearchData(const std::string& criteria);
        static std::map<std::string, SearchData> getAllSearchData();

    private:
        static std::map<std::string, SearchData>   _searchCriteria;

    private:
        void searchLine(const std::string& file, const std::string& line);
        int findCriteria(const std::string& criteria, const std::string& line);
    };
}

#endif // SEARCHMANAGER_H
