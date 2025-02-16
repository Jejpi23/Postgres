// database.cpp
#include "database.h"

// Implementacja klasy DatabaseConnection
DatabaseConnection::DatabaseConnection(const std::string& conninfo) {
  conn = PQconnectdb(conninfo.c_str());
  if (PQstatus(conn) != CONNECTION_OK) {
    std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
    PQfinish(conn);
    conn = nullptr;
  }
}

DatabaseConnection::~DatabaseConnection() {
  if (conn) {
    PQfinish(conn);
  }
}

PGconn* DatabaseConnection::getConnection() const {
  return conn;
}

bool DatabaseConnection::isConnected() const {
  return conn != nullptr;
}

// Implementacja klasy QueryResult
QueryResult::QueryResult(PGresult* res) : res(res) {}

QueryResult::~QueryResult() {
  if (res) {
    PQclear(res);
  }
}

bool QueryResult::isValid() const {
  return res != nullptr;
}

int QueryResult::getRowCount() const {
  return PQntuples(res);
}

int QueryResult::getColumnCount() const {
  return PQnfields(res);
}

std::string QueryResult::getValue(int row, int col) const {
  return PQgetvalue(res, row, col);
}

// Implementacja klasy database
database::database() {
  // Konstruktor (można dodać inicjalizację)
}

database::~database() {
  // Destruktor (można dodać sprzątanie)
}

void database::createtab() {
  // Implementacja metody createtab
  // np. wykonanie zapytania SQL do tworzenia tabel
}

void database::deletetab() {
  // Implementacja metody deletetab
  // np. wykonanie zapytania SQL do usuwania tabel
}