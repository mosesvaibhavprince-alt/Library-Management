#include <stdio.h>
#include <string.h>

// Max number of books the library can hold
#define MAX 100

// A book has an ID, title, author, and whether it's available
struct Book {
    int id;
    char title[100];
    char author[80];
    int available; // 1 = available, 0 = borrowed
};

// Our library is just an array of books
struct Book books[MAX];
int count = 0; // how many books are currently stored

// -----------------------------------------------
// Show all books
// -----------------------------------------------
void listBooks() {
    if (count == 0) {
        printf("No books in the library.\n");
        return;
    }
    printf("\nID  Status      Title\n");
    printf("----------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d.  %-10s  %s by %s\n",
            books[i].id,
            books[i].available ? "Available" : "Borrowed",
            books[i].title,
            books[i].author);
    }
}

// -----------------------------------------------
// Add a new book
// -----------------------------------------------
void addBook() {
    if (count >= MAX) {
        printf("Library is full!\n");
        return;
    }

    books[count].id = count + 1;
    books[count].available = 1;

    printf("Enter title: ");
    scanf(" %[^\n]", books[count].title);

    printf("Enter author: ");
    scanf(" %[^\n]", books[count].author);

    count++;
    printf("Book added! ID: %d\n", count);
}

// -----------------------------------------------
// Borrow a book (mark as unavailable)
// -----------------------------------------------
void borrowBook() {
    int id;
    printf("Enter book ID to borrow: ");
    scanf("%d", &id);

    // Find the book with this ID
    for (int i = 0; i < count; i++) {
        if (books[i].id == id) {
            if (books[i].available == 0) {
                printf("Sorry, this book is already borrowed.\n");
            } else {
                books[i].available = 0;
                printf("You borrowed: %s\n", books[i].title);
            }
            return;
        }
    }
    printf("Book with ID %d not found.\n", id);
}

// -----------------------------------------------
// Return a book (mark as available again)
// -----------------------------------------------
void returnBook() {
    int id;
    printf("Enter book ID to return: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (books[i].id == id) {
            if (books[i].available == 1) {
                printf("This book was not borrowed.\n");
            } else {
                books[i].available = 1;
                printf("You returned: %s\n", books[i].title);
            }
            return;
        }
    }
    printf("Book with ID %d not found.\n", id);
}

// -----------------------------------------------
// Save books to a file so data isn't lost
// -----------------------------------------------
void saveBooks() {
    FILE *fp = fopen("library.dat", "wb");
    if (fp == NULL) {
        printf("Could not save.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, fp);                    // save how many books
    fwrite(books, sizeof(struct Book), count, fp);         // save all books
    fclose(fp);
    printf("Library saved!\n");
}

// -----------------------------------------------
// Load books from file when program starts
// -----------------------------------------------
void loadBooks() {
    FILE *fp = fopen("library.dat", "rb");
    if (fp == NULL) {
        return; // no saved file yet, that's okay
    }
    fread(&count, sizeof(int), 1, fp);                     // load how many books
    fread(books, sizeof(struct Book), count, fp);          // load all books
    fclose(fp);
    printf("Loaded %d book(s) from save file.\n", count);
}

// -----------------------------------------------
// Main: show menu and handle user input
// -----------------------------------------------
int main() {
    loadBooks();

    int choice;

    do {
        printf("\n--- Library Menu ---\n");
        printf("1. Show all books\n");
        printf("2. Add a book\n");
        printf("3. Borrow a book\n");
        printf("4. Return a book\n");
        printf("0. Save and exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        if      (choice == 1) listBooks();
        else if (choice == 2) addBook();
        else if (choice == 3) borrowBook();
        else if (choice == 4) returnBook();
        else if (choice == 0) { saveBooks(); printf("Goodbye!\n"); }
        else                    printf("Please enter 0-4.\n");

    } while (choice != 0);

    return 0;
}
