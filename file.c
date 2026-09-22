#include "lab9.h"

void* autosave_function(void *filename) {
    char *binary_filename = (char*) filename;
    while (1) {
        sleep(15);
        pthread_mutex_lock(&lock);
        save_binary_file(binary_filename);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void save_binary_file(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening binary file for writing.\n");
        return;
    }

    Node *curr = head;
    while (curr) {
        fwrite(curr, sizeof(Node), 1, file);
        curr = curr->next;
    }

    fclose(file);
}

void read_binary_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening binary file for reading.\n");
        return;
    }

    Node temp;
    while (fread(&temp, sizeof(Node), 1, file)) {
        printf("%s\t%02d:%02d\n", temp.name, temp.hour, temp.minute);
    }

    fclose(file);
}

void read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File not found. Starting with an empty list.\n");
        return;
    }

    char animal[NAME_LEN];
    int hour, minute;
    
    while (fscanf(file, "%s %d %d", animal, &hour, &minute) == 3) {
        insert_tail(animal, hour, minute);
    }

    fclose(file);
}

void save_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    if (!head) {
        fclose(file);
        return;
    }

    Node *curr = head;
    while (curr) {
        fprintf(file, "%s %02d %02d\n", curr->name, curr->hour, curr->minute);
        curr = curr->next;
    }

    fclose(file);
}

