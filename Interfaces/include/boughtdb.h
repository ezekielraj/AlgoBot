#pragma once

#include <string>
#include <memory>
#include "sqlitedb.h"

class BoughtDB
{
private:
    const std::string dbname;
    std::unique_ptr<SQLiteDB> db;
    // Internal helper function implemented in .cpp

public:
    BoughtDB();
    bool checkEntryExists(const std::string &symbol);
    bool addEntry(std::string &symbol, std::string &p_e);
    std::string getDBName() const;
};
