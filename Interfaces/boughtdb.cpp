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
    db->execute("CREATE TABLE IF NOT EXISTS boughtStocks (id INTEGER PRIMARY KEY AUTOINCREMENT, symbol TEXT NOT NULL, boughtvalue REAL);");
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

bool BoughtDB::addEntry(std::string &symbol, std::string &boughtvalue)
{
    db->executePrepared("INSERT INTO boughtStocks (symbol, boughtvalue) VALUES (?, ?);", {symbol, boughtvalue});
      
    return true;
}
