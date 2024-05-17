#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// fixed sized struct make it easy to write and read
struct Address{
    int id;
    int set;
    char name[0]; // unspecificated array length, will specificed at runtime
    char email[0];
};

struct Database {
    int max_rows;
    int max_data;
    struct Address rows[0]; // unspecificated array length, will specificed at runtime
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) {
        die("Faild to load database.");
    }
}

struct Connection *Database_open(
    const char *filename, char mode, int max_rows, int max_data)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn) { // simply test is a pointer NULL
        die("Memory error");
    }

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) {
        die("Memory error");
    }

    conn->db->max_rows = max_rows;
    conn->db->max_data = max_data;

    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if (conn->file) {
            Database_load(conn);
        }
    }

    if (!conn->file) {
        die("Faild to open the file");
    }

    return conn;
}

void Database_close(struct Connection *conn)
{
    if (conn) {
        if (conn->file) {
            fclose(conn->file);
        }

        if (conn->db) {
            free(conn->db);
        }
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file); //reset file positon indicator to the begin of the file

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file); //write dabase data into file
    if (rc !=1) {
        die("Faild to write database.");
    }

    rc = fflush(conn->file); // flush OS cache into file
    if (rc == -1) {
        die("Cannot flush database.");
    }
}

void Database_create(struct Connection *conn)
{
    int i = 0;

    for (i = 0; i < conn->db->max_rows; i++) {
        //make a prototype to initialize it
        int max_data = conn->db->max_data;
        struct Address addr = {.id = i, .set = 0, .name = char[max_data]{0}};
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    /* &conn->db->rows[id] read as
     * get the id element of rows,
     * which is in db, which is in conn,
     * then get the address of (&) it.
     */
    struct Address *addr = &conn->db->rows[id];
    if(addr->set){
        die("Already set, delete it first");
    }

    int max_data = conn->db->max_data;
    addr->set = 1; // mark the address set flag
    // WARNING: bug, read the "How to break it" and fix this
    char *res = strncpy(addr->name, name, max_data);
    // demonstrate the strncpy bug
    if (!res) {
        die("Name copy failed");
    }

    res = strncpy(addr->email, email, max_data);
    if (!res) {
        die("Email copy failed");
    }
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];
    if(addr->set){
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = {.id = id, .set = 0}; // create a structure on stack
    //copy the struct into rows[id] by assgin
    // this is effect because on stack variable passed as value
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;
    for (i = 0; i<db->max_rows; i++) {
        struct Address *cur = &db->rows[i];

        if (cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    int action_position = 5;
    if (argc < action_position) {
        die("USAGE: ex17 <dbfile> <action> <maxrows> <maxdata> [action params]");
    }

    char *filename = argv[1];
    char action = argv[2][0];
    int max_rows = atoi(argv[3]);
    int max_data = atoi(argv[4]);
    struct Connection *conn = Database_open(filename, action, max_rows, max_data);
    int id = 0;

    if (argc > action_position){
        id = atoi(argv[action_position]);
    }
    if (id > conn->db->max_rows) {
        die("There's not that many records.");
    }

    switch (action) {
    case 'c':
        Database_create(conn);
        Database_write(conn);
        break;

    case 'g':
        if (argc != action_position + 1) {
            die("Need an id to get");
        }
        Database_get(conn, id);
        break;

    case 's':
        if (argc != action_position + 3) {
            die("Need id, name, email to set");
        }
        Database_set(conn, id, argv[action_position + 1], argv[action_position + 2]);
        Database_write(conn);
        break;

    case 'd':
        if (argc != action_position + 1) {
            die("Need id to delete");
        }

        Database_delete(conn, id);
        Database_write(conn);
        break;

    case 'l':
        Database_list(conn);
        break;

    default:
        die("Invalid action: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}
