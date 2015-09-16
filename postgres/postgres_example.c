/*
Compile -> gcc postgres_example.c -o postgres_example -I/usr/include/postgresql/ -lpq

It uses testdb database for this example with the following table schema:
users:
- id (Pk_autoincrement)
- username (Text)
- password (Text)
*/

#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

int main(int argc, char *argv[])
{
    PGconn *dbConn;
    PGresult *res;
    char *sql;

    /* Open the connection to the database */
    dbConn = PQconnectdb("hostaddr='127.0.0.1' port='5432' dbname='testdb' user='postgres' password='root'");

    /* Check to see that the connection was successfully opened */
    if (PQstatus(dbConn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(dbConn));
        PQfinish(dbConn);
        exit(1);
    } else {
        printf("Connected to the database successfully\n");
    }

    /* Create SQL statement */
    sql = "INSERT INTO users (username, password) VALUES ('john', '123456')";

    /* Execute SQL statement and check if it was successfully executed */
    res = PQexec(dbConn, sql);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Query execution failed: %s", PQresultErrorMessage(res));
        PQfinish(dbConn);
        exit(1);
    } else {
        printf("Query executed successfully\n");
    }

    /* close the connection to the database and cleanup */
    PQclear(res);
    PQfinish(dbConn);

    return 0;
}
