#include <iostream>
#include <libpq-fe.h>
#include "database.h"



int main() {
    std::string conninfo = "dbname=mydb user=admin password=admin hostaddr=127.0.0.1 port=5432";
    DatabaseConnection db(conninfo);

    if (!db.isConnected()) {
        return 1;
    }

    std::cout<<"Connected"<<std::endl;
    return 0;
}