#include "lab9.h"

void insert(char *animal, int hour, int minute) {
    pthread_mutex_lock(&lock);
    
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, animal);
    newNode->hour = hour;
    newNode->minute = minute;
    newNode->next = newNode->prev = NULL;

    if (!head) {
        head = tail = newNode;
    } else {
        Node *curr = head;
        
        while (curr && (hour > curr->hour || (hour == curr->hour && minute > curr->minute))) {
            curr = curr->next;
        }

        if (!curr) {
            insert_tail(animal, hour, minute);
        } else {
            newNode->next = curr;
            newNode->prev = curr->prev;
            if (curr->prev) 
                curr->prev->next = newNode;
            else 
                head = newNode;
            curr->prev = newNode;
        }
    }
    pthread_mutex_unlock(&lock);
}

void insert_tail(char *animal, int hour, int minute) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, animal);
    newNode->hour = hour;
    newNode->minute = minute;
    newNode->next = NULL;
    newNode->prev = tail;

    if (tail) 
        tail->next = newNode;
    else head = newNode;

    tail = newNode;
}

void delete(char *animal) {
    
    pthread_mutex_lock(&lock);
    Node *node = find(animal);
    if (!node) {
        printf("Animal not found.\n");
        pthread_mutex_unlock(&lock);
        return;
    }

    if (node->prev) 
        node->prev->next = node->next;
    else head = node->next;

    if (node->next) 
        node->next->prev = node->prev;
    else tail = node->prev;

    free(node);
    pthread_mutex_unlock(&lock);
}

void showall(void) {
    Node *curr = head;
    if (!curr) {
        printf("Feeding schedule is empty.\n");
        return;
    }
    while (curr) {
        printf("%s\t%02d:%02d\n", curr->name, curr->hour, curr->minute);
        curr = curr->next;
    }
}

void show_backwards(Node *current) {
    if (current == NULL) 
        return;
    show_backwards(current->next);
    printf("%s\t%02d:%02d\n", current->name, current->hour, current->minute);
}

void delete_all(Node *current) {
    if (current == NULL)
        return;
    pthread_mutex_lock(&lock);
    delete_all(current->next);
    free(current);
    pthread_mutex_unlock(&lock);
}

Node* find(char *animal) {
    Node *curr = head;
    while (curr) {
        if (strcmp(curr->name, animal) == 0) 
            return curr;
        curr = curr->next;
    }
    return NULL;
}

void change(char *animal, int new_hour, int new_minute) {
    pthread_mutex_lock(&lock);
    Node *node = find(animal);
    if (!node) {
        printf("Animal not found.\n");
        pthread_mutex_unlock(&lock);
        return;
    }
}

