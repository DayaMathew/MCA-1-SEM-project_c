#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Book
typedef struct book 

{
    int id;
    char title[100];
    char author[100];
    int available;  // 1 = available, 0 = issued
    struct book *next;
} Book;

Book *head = NULL;

// Function to create a new book
Book* createBook(int id, char title[], char author[])
 {
    Book *newBook = (Book*)malloc(sizeof(Book));
    newBook->id = id;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->available = 1;
    newBook->next = NULL;
    return newBook;
}

// Add a new book to the list
void addBook() {
    int id;
    char title[100], author[100];
    printf("\nEnter Book ID: ");
    scanf("%d", &id);

    //  Check for duplicate ID before adding
    Book *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("A book with this ID already exists!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Enter Title: ");
    scanf(" %[^\n]", title);
    printf("Enter Author: ");
    scanf(" %[^\n]", author);

    Book *newBook = createBook(id, title, author);
    newBook->next = head;
    head = newBook;

    printf("Book added successfully\n");
}

// Display all books
void displayBooks() {
    if (head == NULL) {
        printf("\nNo books in the library\n");
        return;
    }
    Book *temp = head;
    printf("\n Library Books\n");
    printf("---------------------------------------------\n");
    while (temp != NULL) {
        printf("ID: %d\nTitle: %s\nAuthor: %s\nStatus: %s\n\n",
               temp->id, temp->title, temp->author,
               temp->available ? "Available" : "Issued");
        temp = temp->next;
    }
}

// Display only available books
void showAvailableBooks() {
    if (head == NULL) {
        printf("\nNo books in the library\n");
        return;
    }

    int found = 0;
    Book *temp = head;
    printf("\n Available Books\n");
    printf("---------------------------------------------\n");

    while (temp != NULL) {
        if (temp->available == 1) {
            printf("ID: %d\nTitle: %s\nAuthor: %s\nStatus: Available\n\n",
                   temp->id, temp->title, temp->author);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found)
        printf(" No books are currently available\n");
}

// Count total, available, and issued books
void countBooks() {
    int total = 0, issued = 0;
    Book *temp = head;

    while (temp != NULL) {
        total++;
        if (temp->available == 0)
            issued++;
        temp = temp->next;
    }

    printf("\nLibrary Book Count\n");
    printf("---------------------------------------------\n");
    printf("Total Books: %d\n", total);
    printf("Available Books: %d\n", total - issued);
    printf("Issued Books: %d\n", issued);
}

// Search book by ID
void searchBook() {
    int id;
    printf("\nEnter Book ID to search: ");
    scanf("%d", &id);

    Book *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("\nBook Found\n");
            printf("Title: %s\nAuthor: %s\nStatus: %s\n",
                   temp->title, temp->author,
                   temp->available ? "Available" : "Issued");
            return;
        }
        temp = temp->next;
    }
    printf(" Book not found\n");
}

// Issue a book
void issueBook() {
    int id;
    printf("\nEnter Book ID to issue: ");
    scanf("%d", &id);

    Book *temp = head;
    while (temp != NULL)
	 {
        if (temp->id == id)
		 {
            if (temp->available)
			 {
                temp->available = 0;
                printf(" Book issued successfully\n");
            } else {
                printf(" Book already issued\n");
            }
            return;
        }
        temp = temp->next;
    }
    printf(" Book not found\n");
}

// Return a book
void returnBook() {
    int id;
    printf("\nEnter Book ID to return: ");
    scanf("%d", &id);

    Book *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            if (!temp->available) {
                temp->available = 1;
                printf(" Book returned successfully\n");
            } else {
                printf(" This book was not issued\n");
            }
            return;
        }
        temp = temp->next;
    }
    printf(" Book not found\n");
}

// Delete a book
void deleteBook() {
    int id;
    printf("\nEnter Book ID to delete: ");
    scanf("%d", &id);

    Book *temp = head, *prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf(" Book not found\n");
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf(" Book deleted successfully\n");
}

int main() {
    int choice;
    do {
        printf("\n===== Library Management System =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Delete Book\n");
        printf("7. Show Available Books\n");
        printf("8. Count Books\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
		{
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: deleteBook(); break;
            case 7: showAvailableBooks(); break;
            case 8: countBooks(); break;
            case 9: printf(" Exiting...\n"); break;
            default: printf(" Invalid choice\n");
        }
    } while (choice != 9);

    return 0;
}

