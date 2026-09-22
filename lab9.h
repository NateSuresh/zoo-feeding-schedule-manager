#ifndef LAB9_H
#define LAB9_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>  // For multithreading
#include <unistd.h>   // For sleep()

#define NAME_LEN 20

// Struct for a doubly linked list node
typedef struct Node {
    char name[NAME_LEN];
    int hour, minute;
    struct Node *next, *prev;
} Node;

// Global pointers
extern Node *head, *tail;

// Global thread and mutex
extern pthread_t autosave_thread;  // THread for auto-saving
extern pthread_mutex_t lock;       // Mutex for synchronization

// Function declarations
void insert(char *animal, int hour, int minute);
void insert_tail(char *animal, int hour, int minute);
void delete(char *animal);
void showall(void);
void show_backwards(Node *current);
void change(char *animal, int new_hour, int new_minute);
Node* find(char *animal);
void delete_all(Node *current);
void read_file(const char *filename);
void save_file(const char *filename);
void* autosave_function(void *filename);
void save_binary_file(const char *filename);
void read_binary_file(const char *filename);

#endif

