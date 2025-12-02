#pragma once

#include <string>
#include <memory>
#include "sqlitedb.h"

class BoughtDBC
{
private:
    const std::string dbname;
    std::unique_ptr<SQLiteDB> db;
    // Internal helper function implemented in .cpp

public:
    BoughtDBC();
    std::vector<std::string> checkEntryExists(const std::string &symbol);
    bool addEntry(std::string &symbol, std::string &p_e, std::string &mtype, std::string &series);
    std::string getDBName() const;
    std::vector<std::string> getAllBoughtStocks();
};
