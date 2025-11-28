#pragma once
#include <string>
#include "RequestTask.h"

class IndexLists {
private:
    std::string url = "https://www.nseindia.com/api/equity-master";
    RequestTask task;

public:
    IndexLists();

    // Download JSON response
    std::string fetchIndexList();

    // Get URL (optional)
    std::string getUrl() const;
};
