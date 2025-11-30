#include "StockQuoteData.h"
#include <stdexcept>
#include <JsonParser.h>
#include "StringCleaner.h"

using json = nlohmann::json;

StockQuoteData::StockQuoteData(const std::string &type, const std::string &series, const std::string &symbol) {
    StringCleaner sc(type);
    std::string _type = sc.url_encode(type);
    
    StringCleaner sc1(series);
    std::string _series = sc1.url_encode(series);
    
    StringCleaner sc2(symbol);
    std::string _symbol = sc2.url_encode(symbol);
    
    requestData = "marketType=" + _type + "&series=" + _series + "&symbol=" + _symbol;
    task.setUrl(url + requestData);
}

std::vector<std::string> StockQuoteData::fetchStockQuoteData() {
    std::string response = task.fetch();
    std::vector<std::string> output;
    //StringCleaner sc(response);
    //sc.setToRemove("Indices List Response: ");
    jsonParser.fromQuotetoArray(response, stockQuoteData);
    return output;
}

std::string StockQuoteData::getData()
{
    return stockQuoteData;
}

std::string StockQuoteData::getUrl() const {
    return url;
}


