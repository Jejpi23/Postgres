#include <iostream>
#include <libpq-fe.h>

class DatabaseConnection {
public:
    DatabaseConnection(const std::string& conninfo) {
        conn = PQconnectdb(conninfo.c_str());
        if (PQstatus(conn) != CONNECTION_OK) {
            std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
            PQfinish(conn);
            conn = nullptr;
        }
    }

    ~DatabaseConnection() {
        if (conn) {
            PQfinish(conn);
        }
    }

    PGconn* getConnection() const {
        return conn;
    }

    bool isConnected() const {
        return conn != nullptr;
    }

private:
    PGconn* conn;
};

class QueryResult {
public:
    QueryResult(PGresult* res) : res(res) {}

    ~QueryResult() {
        if (res) {
            PQclear(res);
        }
    }

    bool isValid() const {
        return res != nullptr;
    }

    int getRowCount() const {
        return PQntuples(res);
    }

    int getColumnCount() const {
        return PQnfields(res);
    }

    std::string getValue(int row, int col) const {
        return PQgetvalue(res, row, col);
    }

private:
    PGresult* res;
};

int main() {
    std::string conninfo = "dbname=mydb user=admin password=admin hostaddr=127.0.0.1 port=5432";
    DatabaseConnection db(conninfo);

    if (!db.isConnected()) {
        return 1;
    }

    std::cout<<"Connected"<<std::endl;
    return 0;
}