/*
Notes:
Add pkg-config path: Linked the .pc files from /usr/lib64/pkgconfig to /usr/lib/pkgconfig/
Add library path: LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64

Compile:
gcc -o mongodb_example mongodb_example.c $(pkg-config --cflags --libs libmongoc-1.0)

It uses testdb database for this example with the following collection:
users:
- _id
- username
- password
*/

#include <stdio.h>
#include <stdlib.h>
#include <bson.h>
#include <mongoc.h>


int main (int argc, char *argv[])
{
    mongoc_client_t *client;
    mongoc_collection_t *collection;
    bson_error_t error;
    bson_oid_t oid;
    bson_t *doc;

    /* Init mongo C driver */
    mongoc_init ();

    /* Create a new connection to the database a get the specified collection  */
    client = mongoc_client_new ("mongodb://localhost:27017/");
    if (!client) {
        fprintf(stderr, "Connection to database failed!");
        mongoc_cleanup();
        return 0;
    } else {
        printf("Connected to the database successfully\n");
    }
    collection = mongoc_client_get_collection (client, "testdb", "users");

    /* Create a new document (All the documents must have the _id field to be used as primary key) */
    doc = bson_new ();
    bson_oid_init (&oid, NULL);
    BSON_APPEND_OID (doc, "_id", &oid);
    BSON_APPEND_UTF8 (doc, "username", "John");
    BSON_APPEND_UTF8 (doc, "password", "123456");

    /* Insert the document into the collection */
    if (!mongoc_collection_insert (collection, MONGOC_INSERT_NONE, doc, NULL, &error)) {
        printf ("Error inserting the document. - %s\n", error.message);
    } else {
        printf ("Document successfully inserted!\n");
    }

    /* Clean the doc, colletion and client allocations */
    bson_destroy (doc);
    mongoc_collection_destroy (collection);
    mongoc_client_destroy (client);

    /* Cleanup after mongo C driver */
    mongoc_cleanup();

    return 0;
}
