#ifndef SQLITE_DB_H
#define SQLITE_DB_H

#include <string>
#include <vector>
#include <stdexcept>
#include <sqlite3.h>

class SQLiteDB {
public:
    // open/create db file
    explicit SQLiteDB(const std::string& filename);
    ~SQLiteDB();

    // execute a statement that doesn't return rows (CREATE, INSERT, UPDATE, DELETE)
    void execute(const std::string& sql);

    // execute prepared statement with parameters (simple overload)
    void executePrepared(const std::string& sql, const std::vector<std::string>& params);

    // query and return rows as vector of columns (all values as strings)
    std::vector<std::vector<std::string>> query(const std::string& sql);

    // query with parameters (prepared)
    std::vector<std::vector<std::string>> queryPrepared(const std::string& sql, const std::vector<std::string>& params);

    // convenience: check if open
    bool isOpen() const { return db != nullptr; }

private:
    sqlite3* db = nullptr;

    // helper to bind params to sqlite3_stmt
    static void bindParams(sqlite3_stmt* stmt, const std::vector<std::string>& params);
};

#endif // SQLITE_DB_H
