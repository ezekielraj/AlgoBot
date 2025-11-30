#include "IndexLists.h"
#include <stdexcept>
#include <JsonParser.h>
#include "StringCleaner.h"

using json = nlohmann::json;

IndexLists::IndexLists() {
    task.setUrl(url);
}

std::vector<std::string> IndexLists::fetchIndexList() {
    std::string response = task.fetch();
    //StringCleaner sc(response);
    //sc.setToRemove("Indices List Response: ");
    return jsonParser.toArray(response, indexListsresult);

}

std::vector<std::vector<std::string>> IndexLists::getList()
{
    return indexListsresult;
}

std::string IndexLists::getUrl() const {
    return url;
}


