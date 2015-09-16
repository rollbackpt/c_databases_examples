/*
Compile -> gcc -o sqlite_example sqlite_example.c -l sqlite3

It uses testdbConn file for this example with the following table schema:
users:
- id (Pk_autoincrement)
- username (Text)
- password (Text)
*/

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char* argv[])
{
    sqlite3 *dbConn;
    char *sql, *errorMsg;

    /* Open the database connection and check if it was successfully */
    if(sqlite3_open("test.db", &dbConn)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbConn));
        return 0;
    } else {
        printf("Opened database successfully\n");
    }

    /* Create SQL statement */
    sql = "INSERT INTO users (username, password) VALUES ('john', '123456')";

    /* Execute SQL statement and check if it was successfully executed */
    if(sqlite3_exec(dbConn, sql, NULL, 0, &errorMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errorMsg);
        sqlite3_free(errorMsg);
    } else {
        printf("Query executed successfully\n");
    }

    /* Close the database connection */
    sqlite3_close(dbConn);
}
