#include "lab9.h"

Node *head = NULL, *tail = NULL;
pthread_t autosave_thread;
pthread_mutex_t lock;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ./lab9 textfile.txt binaryfile.bin\n");
        return 1;
    }

    pthread_mutex_init(&lock, NULL);
    pthread_create(&autosave_thread, NULL, autosave_function, argv[2]);

    read_file(argv[1]);

    int option;
    char animal[NAME_LEN];
    int hour, minute;

    while (1) {
        printf("Enter option (1: Insert, 2: Delete, 3: Show all, 4: Change, 5: Show backwards, 6: Show binary file, 0: Exit):\n");
        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (option) {
            case 1:
                printf("Enter animal name, hour, and minute:\n");
                scanf("%s %d %d", animal, &hour, &minute);
                insert(animal, hour, minute);
                break;
            case 2:
                printf("Enter animal name to delete:\n");
                scanf("%s", animal);
                delete(animal);
                break;
            case 3:
                showall();
                break;
            case 4:
                printf("Enter animal name, new hour, and new minute:\n");
                scanf("%s %d %d", animal, &hour, &minute);
                change(animal, hour, minute);
                break;
            case 5:
                show_backwards(head);
                break;
            case 6:
                read_binary_file(argv[2]);
                break;
            case 0:
                pthread_cancel(autosave_thread);
                pthread_mutex_destroy(&lock);
                save_file(argv[1]);
                delete_all(head);
                head = tail = NULL;
                printf("All nodes deleted. Exiting...\n");
                return 0;
            default:
                printf("Invalid option. Try again.\n");
        }
    }
}


