/*
Compile -> gcc mysql_example.c -o mysql_example `mysql_config --cflags --libs`

It uses testdb database for this example with the following table schema:
users:
- id (Pk_autoincrement)
- username (Text)
- password (Text)
*/

#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

int main (int argc, char *argv[])
{
    int error;
    char *sql;
    MYSQL *dbConn;

    /* Trys to connect to the database and check if the connection was successfull */
    dbConn = mysql_init(NULL);

    if (dbConn == NULL) {
        fprintf(stderr, "Failed to allocate memory for MySQL object! Error: %s\n", mysql_error(dbConn));
        return 0;
    }

    if (!mysql_real_connect(dbConn, "localhost", "root", "root", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "Failed to connect to database! Error: %s\n", mysql_error(dbConn));
        return 0;
    } else {
        printf("Connected to the database successfully\n");
    }

    /* Create SQL statement */
    sql = "INSERT INTO users (username, password) VALUES ('john', '123456')";

    /* Execute SQL statement and check if it was successfully executed */
    if (mysql_query(dbConn, sql) != 0) {
        fprintf(stderr, "Failed to query the database! Error: %s\n", mysql_error(dbConn));
        return 0;
    } else {
        printf("Query executed successfully\n");
    }

    /* Close the database connection */
    mysql_close(dbConn);

    return 0;
}
