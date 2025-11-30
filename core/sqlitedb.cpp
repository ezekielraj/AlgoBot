#include "sqlitedb.h"
#include <iostream>

SQLiteDB::SQLiteDB(const std::string& filename) {
    int rc = sqlite3_open(filename.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::string err = sqlite3_errmsg(db);
        sqlite3_close(db);
        db = nullptr;
        throw std::runtime_error("Can't open database: " + err);
    }
}

SQLiteDB::~SQLiteDB() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

void SQLiteDB::execute(const std::string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::string err = errMsg ? errMsg : "unknown error";
        sqlite3_free(errMsg);
        throw std::runtime_error("SQL error: " + err);
    }
}

void SQLiteDB::bindParams(sqlite3_stmt* stmt, const std::vector<std::string>& params) {
    for (int i = 0; i < (int)params.size(); ++i) {
        // SQLite parameters are 1-based
        sqlite3_bind_text(stmt, i + 1, params[i].c_str(), -1, SQLITE_TRANSIENT);
    }
}

void SQLiteDB::executePrepared(const std::string& sql, const std::vector<std::string>& params) {
    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
    }

    bindParams(stmt, params);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Execution failed: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_finalize(stmt);
}

std::vector<std::vector<std::string>> SQLiteDB::query(const std::string& sql) {
    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
    }

    std::vector<std::vector<std::string>> rows;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int cols = sqlite3_column_count(stmt);
        std::vector<std::string> row;
        row.reserve(cols);
        for (int c = 0; c < cols; ++c) {
            const unsigned char* text = sqlite3_column_text(stmt, c);
            row.emplace_back(text ? reinterpret_cast<const char*>(text) : "");
        }
        rows.push_back(std::move(row));
    }

    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Query failed: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_finalize(stmt);
    return rows;
}

std::vector<std::vector<std::string>> SQLiteDB::queryPrepared(const std::string& sql, const std::vector<std::string>& params) {
    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
    }

    bindParams(stmt, params);

    std::vector<std::vector<std::string>> rows;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int cols = sqlite3_column_count(stmt);
        std::vector<std::string> row;
        row.reserve(cols);
        for (int c = 0; c < cols; ++c) {
            const unsigned char* text = sqlite3_column_text(stmt, c);
            row.emplace_back(text ? reinterpret_cast<const char*>(text) : "");
        }
        rows.push_back(std::move(row));
    }

    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Query failed: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_finalize(stmt);
    return rows;
}
