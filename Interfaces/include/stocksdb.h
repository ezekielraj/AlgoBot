#pragma once

#include <string>
#include <memory>
#include "sqlitedb.h"

class StocksDB
{
private:
    std::string dbname;
    std::unique_ptr<SQLiteDB> db;
    // Internal helper function implemented in .cpp
    static std::string generateTodayDate();
    static std::string generateYesterdayDate();
public:
    StocksDB();
    bool checkEntryExists(const std::string &symbol);
    bool addEntry(std::string &symbol, std::string &p_e, double &wcp);
    std::string getDBName() const;
    std::vector<std::vector<std::string>> searchStock();
    void setDBName(const std::string &name) { dbname = name; }
    void changeDBNameToYesterday();// { dbname = generateYesterdayDate(); db = std::make_unique<SQLiteDB>(dbname);
};
