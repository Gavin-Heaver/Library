// libstruct.h
// Author: Gavin Heaver
// Date: 11/22/24
// Class: COP 3223, Professor Parra
// Purpose: The purpose of this program is to understand structs, header files, and string more by working with them
//          to make a library
// Input: Nothing
// Output: All details of a book, being name, author, and year, and whether it was added, found, already in, or checked out

//Make the size for future use
#define SIZE 1024
#define maxBooks 100

//Creation of the library and book struct
typedef struct Book{
    //Contents of Book
    char *title;
    char *author;
    int year;
    int is_available;
} Book;

typedef struct Library{
    //Contents of library
    Book **library;
    int count;
} Library;

//Function Prototypes
void addBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear);
void removeBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear);
void printLibrary(Library *library);
Book *findBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear);
void checkoutBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear);
void returnBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear);