#include "StockLists.h"
#include <stdexcept>
#include <JsonParser.h>
#include "StringCleaner.h"

using json = nlohmann::json;

StockLists::StockLists(const std::string &rqData) {
    StringCleaner sc(rqData);
    requestData = sc.url_encode(rqData);
    
    task.setUrl(url + "?index=" + requestData);
}

std::vector<std::string> StockLists::fetchStockList() {
    std::string response = task.fetch();
    std::vector<std::string> output;
    //StringCleaner sc(response);
    //sc.setToRemove("Indices List Response: ");
    jsonParser.toArray(response, stockListsresult);
    return output;
}

std::vector<std::pair<std::string, StockData>> StockLists::getList()
{
    return stockListsresult;
}

std::string StockLists::getUrl() const {
    return url;
}


