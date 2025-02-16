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
database::database(DatabaseConnection& dbConn) : dbConn(dbConn) {
}

database::~database() {
  // Destruktor (można dodać sprzątanie)
}

void database::createtab() {
  if (!dbConn.isConnected()) {
    std::cerr << "Database is not connected!" << std::endl;
    return;
  }

  // Zapytanie SQL do stworzenia tabeli items
  const char* query = R"(
        CREATE TABLE items (
            item_id SERIAL PRIMARY KEY,
            item_name VARCHAR(100) NOT NULL,
            item_quantity INT NOT NULL
        );
    )";

  // Wykonanie zapytania
  PGresult* res = PQexec(dbConn.getConnection(), query);

  // Sprawdzenie wyniku
  if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    std::cerr << "Failed to create table: " << PQerrorMessage(dbConn.getConnection()) << std::endl;
  } else {
    std::cout << "Table 'items' created successfully!" << std::endl;
  }

  // Zwolnienie pamięci
  PQclear(res);
}

void database::deletetab() {
  if (!dbConn.isConnected()) {
    std::cerr << "Database is not connected!" << std::endl;
    return;
  }

  // Zapytanie SQL do usunięcia tabeli items
  const char* query = "DROP TABLE IF EXISTS items;";

  // Wykonanie zapytania
  PGresult* res = PQexec(dbConn.getConnection(), query);

  // Sprawdzenie wyniku
  if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    std::cerr << "Failed to delete table: " << PQerrorMessage(dbConn.getConnection()) << std::endl;
  } else {
    std::cout << "Table 'items' deleted successfully!" << std::endl;
  }

  // Zwolnienie pamięci
  PQclear(res);
}

void database::fillrandom() {
  if (!dbConn.isConnected()) {
    std::cerr << "Database is not connected!" << std::endl;
    return;
  }

  // Lista przykładowych nazw przedmiotów
  const std::string itemNames[] = {
    "Apple", "Banana", "Orange", "Pineapple", "Grapes",
    "Mango", "Strawberry", "Blueberry", "Raspberry", "Watermelon"
};
  const int numNames = sizeof(itemNames) / sizeof(itemNames[0]);

  // Wstawianie 100 losowych rekordów
  for (int i = 0; i < 100; ++i) {
    // Losowa nazwa przedmiotu
    std::string itemName = itemNames[std::rand() % numNames];

    // Losowa ilość (od 1 do 100)
    int itemQuantity = std::rand() % 100 + 1;

    // Zapytanie SQL do wstawienia rekordu
    std::string query = "INSERT INTO items (item_name, item_quantity) VALUES ('" + itemName + "', " + std::to_string(itemQuantity) + ");";

    // Wykonanie zapytania
    PGresult* res = PQexec(dbConn.getConnection(), query.c_str());

    // Sprawdzenie wyniku
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cerr << "Failed to insert record: " << PQerrorMessage(dbConn.getConnection()) << std::endl;
    }

    // Zwolnienie pamięci
    PQclear(res);
  }

  std::cout << "Inserted 100 random records into 'items' table!" << std::endl;
}