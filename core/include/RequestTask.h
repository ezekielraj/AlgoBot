#pragma once
#include <string>
#include "HttpClient.h"

class RequestTask {
private:
    std::string url;
    HttpClient http;

public:
    RequestTask() = default;
    explicit RequestTask(const std::string& u);

    void setUrl(const std::string& u);
    std::string getUrl() const;

    std::string fetch();  // download JSON response
};
