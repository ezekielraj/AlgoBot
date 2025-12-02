#include "boughtdb.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <string>

BoughtDB::BoughtDB()
    : dbname("bought.db")
    , db(std::make_unique<SQLiteDB>(dbname))
{
    db->execute("CREATE TABLE IF NOT EXISTS boughtStocks (id INTEGER PRIMARY KEY AUTOINCREMENT, symbol TEXT NOT NULL, boughtvalue REAL, mtype text not null, series text not null);");
}


std::string BoughtDB::getDBName() const
{
    return dbname;
}

bool BoughtDB::checkEntryExists(const std::string &symbol)
{
    auto rows = db->query("SELECT * FROM boughtStocks where symbol = '" + symbol + "';");
    if(rows.size())
    {
        return true;
    }
    return false;
}

bool BoughtDB::addEntry(std::string &symbol, std::string &boughtvalue, std::string &mtype, std::string &series)
{
    db->executePrepared("INSERT INTO boughtStocks (symbol, boughtvalue, mtype, series) VALUES (?, ?, ?, ?);", {symbol, boughtvalue, mtype, series});
      
    return true;
}

std::vector<std::string> BoughtDB::getAllBoughtStocks()
{
    std::vector<std::string> boughtStocks;
    auto rows = db->query("SELECT distinct(symbol) FROM boughtStocks;");
    for (const auto& row : rows) {
        boughtStocks.push_back(row[0]);
    }
    return boughtStocks;
}
