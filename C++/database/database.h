// database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <libpq-fe.h>
#include <string>
#include <iostream>

//DatabaseConnection
class DatabaseConnection {
public:
    DatabaseConnection(const std::string& conninfo);
    ~DatabaseConnection();

    PGconn* getConnection() const;
    bool isConnected() const;

private:
    PGconn* conn;
};

//QueryResult
class QueryResult {
public:
    QueryResult(PGresult* res);
    ~QueryResult();

    bool isValid() const;
    int getRowCount() const;
    int getColumnCount() const;
    std::string getValue(int row, int col) const;

private:
    PGresult* res;
};

//database hard control
class database {
public:
    database(DatabaseConnection& dbConn);  // Konstruktor z parametrem
    ~database();

    void createtab();
    void deletetab();
    void fillrandom();

private:
    DatabaseConnection& dbConn;  // Referencja do połączenia z bazą danych
};


#endif // DATABASE_H