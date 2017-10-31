#include "SearchManager.h"

namespace codegrunt
{
    std::map<std::string, SearchData> SearchManager::_searchCriteria;

    SearchManager::SearchManager()
    {

    }

    SearchManager::~SearchManager()
    {

    }

    void SearchManager::addSearchCriteria(const std::string& criteria)
    {
        SearchData data;
        data.NumOccurences = 0;
        _searchCriteria.emplace(criteria, data);
    }

    void SearchManager::addAllCriteria(const std::vector<std::string>& criteria)
    {
        for (unsigned int i = 0; i < criteria.size(); i++)
        {
            SearchData data;
            data.NumOccurences = 0;
            _searchCriteria.emplace(criteria[i], data);
        }
    }

    SearchData SearchManager::getSearchData(const std::string& criteria)
    {
        return _searchCriteria[criteria];
    }

    std::map<std::string, SearchData> SearchManager::getAllSearchData()
    {
        return _searchCriteria;
    }

    void SearchManager::searchLine(const std::string& file, const std::string& line)
    {
        for (std::map<std::string, SearchData>::iterator it = _searchCriteria.begin(); it != _searchCriteria.end(); ++it)
        {
            int occurencesThisLine = 0;

            occurencesThisLine += findCriteria(it->first, line);

            SearchData* data = &it->second;
            data->NumOccurences += occurencesThisLine;
        }
    }

    int SearchManager::findCriteria(const std::string& criteria, const std::string& line)
    {
        int occurencesThisLine = 0;

        std::size_t found = line.find(criteria);
        if (found != std::string::npos)
        {
            occurencesThisLine++;
            std::string tempLine = line;

            tempLine.erase(found, criteria.length());

            occurencesThisLine += findCriteria(criteria, tempLine);
        }

        return occurencesThisLine;
    }
}
