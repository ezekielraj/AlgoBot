#include "IndexLists.h"
#include <stdexcept>

IndexLists::IndexLists() {
    task.setUrl(url);
}

std::string IndexLists::fetchIndexList() {
    return task.fetch();
}

std::string IndexLists::getUrl() const {
    return url;
}
