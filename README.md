Zoo Feeding Schedule Manager

A command-line zoo feeding management system written in C.

The application allows users to create and manage animal feeding schedules while keeping entries ordered by feeding time. It uses a doubly linked list for schedule management, supports text and binary file storage, and uses POSIX threads for automatic background saving.

Features

Add animals and feeding times

Delete scheduled feedings

Update existing feeding schedules

Keep feeding times ordered automatically

Display the full feeding schedule

Display the schedule in reverse order

Manage data using a doubly linked list

Load schedule data from a text file

Save schedule data back to a text file

Save schedule data to a binary file

Read previously saved binary data

Automatically save data in the background

Use mutex synchronization for thread-safe access

Handle dynamically allocated memory

Technologies and Concepts

C

POSIX Threads (pthread)

Doubly Linked Lists

Dynamic Memory Allocation

File I/O

Binary File Handling

Mutex Synchronization

Structs

Pointers

Makefile

Command-Line Arguments

Project Structure

.
├── main.c
├── list.c
├── file.c
├── lab9.h
├── Makefile
├── test.txt
└── README.md

File Breakdown

main.c

Contains the main program loop and user menu.

It handles:

Program startup

Command-line arguments

Mutex initialization

Background autosave thread creation

User input

Menu selection

Program shutdown

Saving data before exit

Cleaning up dynamically allocated nodes

list.c

Contains the doubly linked list operations used to manage the feeding schedule.

It handles:

Inserting a feeding schedule

Inserting at the end of the list

Deleting an animal

Finding an animal

Updating feeding times

Displaying all feeding schedules

Displaying the schedule backwards

Deleting all nodes from memory

file.c

Handles file storage and automatic saving.

It includes:

Reading schedule data from a text file

Saving schedule data to a text file

Writing schedule data to a binary file

Reading schedule data from a binary file

Background autosaving using a POSIX thread

lab9.h

Contains:

Required libraries

The Node structure

Global linked list pointers

Thread and mutex declarations

Function prototypes

Makefile

Used to compile and run the project.

test.txt

Contains example animal feeding schedule data used by the program.

Data Structure

Each feeding schedule entry is stored in a node:

typedef struct Node {
    char name[20];
    int hour;
    int minute;
    struct Node *next;
    struct Node *prev;
} Node;

Each node stores:

Animal name

Feeding hour

Feeding minute

Pointer to the next node

Pointer to the previous node

Using both next and prev pointers allows the feeding schedule to be traversed in both directions.

Menu Options

When the program runs, the following options are available:

1 - Insert
2 - Delete
3 - Show all
4 - Change
5 - Show backwards
6 - Show binary file
0 - Exit

How It Works

When the program starts, it loads animal feeding schedule data from the provided text file.

The user can then add, delete, update, and display schedule entries.

Feeding schedule entries are stored in a doubly linked list and kept ordered by feeding time.

The program also creates a background thread that periodically saves the current schedule to a binary file.

When the user exits, the updated schedule is saved back to the text file and dynamically allocated memory is released.

Multithreading

The project uses POSIX threads to perform automatic background saving.

A separate thread periodically saves the current linked list to a binary file.

A mutex is used to synchronize access to shared data so the autosave thread and the main program do not modify the same data at the same time.

File Persistence

The project supports two forms of data storage.

Text File

The program loads its initial feeding schedule from a text file.

Example:

panda 02 30
lion 10 30
cat 11 30
dog 12 30

When the program exits, the current schedule is written back to the text file.

Binary File

The program also stores schedule information in a binary file.

This binary file is updated automatically by the background autosave thread and can also be displayed from the program menu.

Compile and Run

Compile using the Makefile:

make lab9

You can also compile manually:

gcc -o lab9 main.c list.c file.c -pthread

Run the program using:

./lab9 test.txt xyz.bin

The program expects two command-line arguments:

./lab9 <text-file> <binary-file>

For example:

./lab9 test.txt xyz.bin

Example Usage

Start the program:

./lab9 test.txt xyz.bin

The program displays:

Enter option
1: Insert
2: Delete
3: Show all
4: Change
5: Show backwards
6: Show binary file
0: Exit

An animal and feeding time can then be entered, such as:

tiger 14 30

The program inserts the animal into the appropriate location in the schedule based on its feeding time.

Memory Management

The program dynamically allocates memory for linked list nodes using malloc.

When an animal is deleted, its node is freed.

Before the program exits, all remaining nodes are deleted and their memory is released.

What I Learned

This project helped me practice:

Programming in C

Building command-line applications

Working with structs and pointers

Creating and managing doubly linked lists

Dynamic memory allocation

Organizing code across multiple source files

Reading and writing text files

Reading and writing binary files

Using command-line arguments

Creating background threads with pthread

Synchronizing shared data with mutexes

Using Makefiles to build C programs

Managing program memory and cleanup
