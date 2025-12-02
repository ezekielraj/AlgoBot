#include "boughtdbc.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <string>

BoughtDBC::BoughtDBC()
    : dbname("bought.db")
    , db(std::make_unique<SQLiteDB>(dbname))
{
    db->execute("CREATE TABLE IF NOT EXISTS boughtStocks (id INTEGER PRIMARY KEY AUTOINCREMENT, symbol TEXT NOT NULL, boughtvalue REAL, mtype text not null, series text not null);");
}


std::string BoughtDBC::getDBName() const
{
    return dbname;
}

std::vector<std::string> BoughtDBC::checkEntryExists(const std::string &symbol)
{
    auto rows = db->query("SELECT * FROM boughtStocks where symbol = '" + symbol + "' limit 1;");
    std::vector<std::string> result;
    for( auto& row : rows)
    {
        result.push_back(row[0]);
        result.push_back(row[1]);
        result.push_back(row[2]);
        result.push_back(row[3]);
        result.push_back(row[4]);
        break;
    }
    return result;
}

bool BoughtDBC::addEntry(std::string &symbol, std::string &boughtvalue, std::string &mtype, std::string &series)
{
    db->executePrepared("INSERT INTO boughtStocks (symbol, boughtvalue, mtype, series) VALUES (?, ?, ?, ?);", {symbol, boughtvalue, mtype, series});
      
    return true;
}

std::vector<std::string> BoughtDBC::getAllBoughtStocks()
{
    std::vector<std::string> boughtStocks;
    auto rows = db->query("SELECT distinct(symbol) FROM boughtStocks;");
    for (const auto& row : rows) {
        boughtStocks.push_back(row[0]);
    }
    return boughtStocks;
}
