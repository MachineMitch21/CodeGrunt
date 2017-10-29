
#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <cstddef>

namespace lc
{

    typedef struct
    {
        int NumOccurences;
    }   SearchData;

    class SearchManager
    {

        friend class FileManager;

    public:

        static void addSearchCriteria(const std::string& criteria);
        static void addAllCriteria(const std::vector<std::string>& criteria);
        static SearchData getSearchData(const std::string& criteria);
        static std::map<std::string, SearchData> getAllSearchData();

    private:
        SearchManager();
        ~SearchManager();

        static void searchLine(const std::string& file, const std::string& line);
        static int findCriteria(const std::string& criteria, const std::string& line);
        static std::map<std::string, SearchData>   _searchCriteria;
    };
}

#endif // SEARCHMANAGER_H
