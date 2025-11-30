#pragma once
#include <string>
#include "RequestTask.h"
#include "JsonParser.h"

using json = nlohmann::json;

class IndexLists {
private:
    std::string url = "https://www.nseindia.com/api/equity-master";
    RequestTask task;
    JsonParser jsonParser;
    std::vector<std::vector<std::string>> indexListsresult;
public:
    IndexLists();

    // Download JSON response
    std::vector<std::string> fetchIndexList();

    std::vector<std::vector<std::string>> getList();
    
    // Get URL (optional)
    std::string getUrl() const;


};
