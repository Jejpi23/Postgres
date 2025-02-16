#include <iostream>
#include <libpq-fe.h>
#include "database.h"



int main() {
    std::string conninfo = "dbname=mydb user=admin password=admin hostaddr=127.0.0.1 port=5432";

    DatabaseConnection dbConn(conninfo);

    if (!dbConn.isConnected()) {
        return 1;
    }


    database dbManager(dbConn);


    dbManager.createtab();


    dbManager.fillrandom();

    
    const char* query = "SELECT * FROM items;";
    PGresult* res = PQexec(dbConn.getConnection(), query);

    // Sprawdzenie wyniku zapytania
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Failed to fetch records: " << PQerrorMessage(dbConn.getConnection()) << std::endl;
        PQclear(res);
        return 1;
    }

    // Przetworzenie wyników
    QueryResult result(res);
    if (result.isValid()) {
        int rowCount = result.getRowCount();
        int colCount = result.getColumnCount();

        // Wyświetlenie nagłówków kolumn
        for (int col = 0; col < colCount; ++col) {
            std::cout << PQfname(res, col) << "\t";
        }
        std::cout << std::endl;

        // Wyświetlenie danych
        for (int row = 0; row < rowCount; ++row) {
            for (int col = 0; col < colCount; ++col) {
                std::cout << result.getValue(row, col) << "\t";
            }
            std::cout << std::endl;
        }
    }

    // Zwolnienie pamięci
    PQclear(res);

    // Usunięcie tabeli items (opcjonalne)
    // dbManager.deletetab();

    return 0;
}
