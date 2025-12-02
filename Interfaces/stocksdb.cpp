#include "stocksdb.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <string>

StocksDB::StocksDB()
    : dbname(generateTodayDate())
    , db(std::make_unique<SQLiteDB>(dbname))
{
    db->execute("CREATE TABLE IF NOT EXISTS stocks (id INTEGER PRIMARY KEY AUTOINCREMENT, symbol TEXT NOT NULL, p_e REAL, week_change_per REAL);");
}

std::string StocksDB::generateTodayDate()
{
    using namespace std::chrono;

    auto now = system_clock::now();
    std::time_t t = system_clock::to_time_t(now);

    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d") << ".db";  
    return oss.str();
}

std::string StocksDB::generateYesterdayDate()
{
    using namespace std::chrono;

    // subtract 1 day
    auto now = system_clock::now() - hours(24);

    std::time_t t = system_clock::to_time_t(now);

    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d") << ".db";
    return oss.str();
}


std::string StocksDB::getDBName() const
{
    return dbname;
}

bool StocksDB::checkEntryExists(const std::string &symbol)
{
    auto rows = db->query("SELECT * FROM stocks where symbol = '" + symbol + "';");
    if(rows.size())
    {
        return true;
    }
    return false;
}

bool StocksDB::addEntry(std::string &symbol, std::string &p_e, double &wcp, std::string &mtype, std::string &series)
{
    db->executePrepared("INSERT INTO stocks (symbol, p_e, week_change_per, mtype, series) VALUES (?, ?, ?, ?, ?);", {symbol, p_e, std::to_string(wcp), mtype, series});
      
    return true;
}

void StocksDB::changeDBNameToYesterday(){ 
    dbname = generateYesterdayDate(); 
    db = std::make_unique<SQLiteDB>(dbname);
}

std::vector<std::vector<std::string>> StocksDB::searchStock()
{
    auto rows = db->query("select * from stocks where P_E < 30 and week_change_per < -5;");
    return rows;
}