#include <stdexcept>
#include "RequestTask.h"

RequestTask::RequestTask(const std::string& u)
    : url(u)
{}

void RequestTask::setUrl(const std::string& u) {
    url = u;
}

std::string RequestTask::getUrl() const {
    return url;
}

std::string RequestTask::fetch() {
    if (url.empty()) {
        throw std::runtime_error("URL is empty");
    }
    return http.get(url);   // call HttpClient
}
