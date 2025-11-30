#include "StockMetaData.h"
#include <stdexcept>
#include <JsonParser.h>
#include "StringCleaner.h"

using json = nlohmann::json;

StockMetaData::StockMetaData(const std::string &rqData) {
    StringCleaner sc(rqData);
    requestData = sc.url_encode(rqData);
    
    task.setUrl(url + requestData);
}

std::vector<std::string> StockMetaData::fetchStockMetaData() {
    std::string response = task.fetch();
    std::vector<std::string> output;
    //StringCleaner sc(response);
    //sc.setToRemove("Indices List Response: ");
    jsonParser.toArray(response, stockMetaData);
    return output;
}

std::string StockMetaData::getData()
{
    return stockMetaData;
}

std::string StockMetaData::getUrl() const {
    return url;
}


