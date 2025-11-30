#pragma once

#include <string>
#include <memory>
#include "sqlitedb.h"

class StocksDB
{
private:
    const std::string dbname;
    std::unique_ptr<SQLiteDB> db;
    // Internal helper function implemented in .cpp
    static std::string generateTodayDate();

public:
    StocksDB();
    bool checkEntryExists(const std::string &symbol);
    bool addEntry(std::string &symbol, std::string &p_e, double &wcp);
    std::string getDBName() const;
};
