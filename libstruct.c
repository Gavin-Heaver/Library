// libstruct.c
// Author: Gavin Heaver
// Date: 11/22/24
// Class: COP 3223, Professor Parra
// Purpose: The purpose of this program is to understand structs, header files, and string more by working with them
//          to make a library
// Input: Nothing
// Output: All details of a book, being name, author, and year, and whether it was added, found, already in, or checked out

//Make #includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libstruct.h"

//Add book function
void addBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear){   
    //Make sure that the library limit hasn't been reached
    if(library->count < maxBooks){
        //Create a timer
        int timer = 0;

        //Create the dynamic space for the book and its title and author
        library->library[library->count] = malloc(sizeof(Book));
        library->library[library->count]->title = malloc(SIZE * sizeof(char));
        library->library[library->count]->author = malloc(SIZE * sizeof(char));

        //Go through the entire library
        for(int i = 0; i < library->count; i++){
            //Make conditional to see if the book exists or not in the library
            if(strcmp(library->library[i]->title, bookTitle) == 0 && strcmp(library->library[i]->author, bookAuthor) == 0 && library->library[i]->year == bookYear){
                //Call find book function
                findBook(library, bookTitle, bookAuthor, bookYear);
                  
                //print that the book is already in the 
                printf("Book with title %s, author %s, and year %d is already in the library.\n", bookTitle, bookAuthor, bookYear);

            } else {
                //Add one to the timer
                timer++;
            }
        }

        //Make conditional if it goes through the entire array and doesn't find a match
        if(timer == library->count){
            //Add the book title, author, year, and availablility to the library array
            strcpy(library->library[library->count]->title, bookTitle);
            strcpy(library->library[library->count]->author, bookAuthor);
            library->library[library->count]->year = bookYear;
            library->library[library->count]->is_available = 1;

            //Increase the library count
            library->count++;

            //Print out that everything got added to the library
            printf("Book with title %s, author %s, and year %d added to the library\n", bookTitle, bookAuthor, bookYear);

        }
    } else if (library->count >= maxBooks) {
        //print that the limit has been reached
        printf("The library is full. Cannot add more books.\n");
    }
}

//Remove book function
void removeBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear){
    //Make a timer
    int timer = 0;

    //Go through the entire library
    for(int i = 0; i < library->count; i++){
        //Make conditional to see if the book exists or not in the library
        if(strcmp(library->library[i]->title, bookTitle) == 0 && strcmp(library->library[i]->author, bookAuthor) == 0 && library->library[i]->year == bookYear){
            //Call find book function
            findBook(library, bookTitle, bookAuthor, bookYear);

            //Free the space for future use of other books
            free(library->library[i]->title);
            free(library->library[i]->author);
            free(library->library[i]);

            //Shift everything down (I know we shouldn't, but setting to NULL wouldn't work and this does. I apologize)
            for(int j = i; j < library->count - 1; j++){
                library->library[j] = library->library[j+1];
            }

            //Decrease the library count
            library->count--;

            //Print out that everything got removed from the library
            printf("Book with title %s, author %s, and year %d has been removed from the library\n", bookTitle, bookAuthor, bookYear);

        } else {
            //Add 1 to the count down
            timer++;
        } 

        //If the timer gets reached with no book found
        if(timer == library->count){
            //Print that the book wasn't found
            printf("Book not found\n");
        }
    }
}

//Print library function
void printLibrary(Library *library){
    //Loop for all of the library
    for(int i = 0; i < library->count; i++){
        //Make conditional to see if the book is in or not
        if(library->library[i]->is_available == 0){
            //Print the book details and that it is checked out
            printf("Book with title %s, author %s, and year %d is in the library and is checked out.\n", library->library[i]->title, library->library[i]->author, library->library[i]->year);

        } else if (library->library[i]->is_available == 1){
            //Print the book details and that is isn't checked out
            printf("Book with title %s, author %s, and year %d is in the library and isn't checked out.\n", library->library[i]->title, library->library[i]->author, library->library[i]->year);

        }
    }
}

//Find book function
Book *findBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear){
    //Make timer
    int timer = 0;

    //Loop for all of the library
    for(int i = 0; i < library->count; i++){
        //Make conditional to see if the book is in or not
        if(strcmp(library->library[i]->title, bookTitle) == 0 && strcmp(library->library[i]->author, bookAuthor) == 0 && library->library[i]->year == bookYear){
            //Print that the book was found
            printf("Book with title %s, author %s, and year %d is found!\n", library->library[i]->title, library->library[i]->author, library->library[i]->year);
            
            //Return the book found
            return library->library[i];

        } else {
            //Add one to the timer
            timer++;
        }

        //Make conditional if no book is found
        if(timer == library->count){
            //return null
            return NULL;

        }
    }
}

//Checkout book function
void checkoutBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear){
    //Make timer
    int timer = 0;
    
    //Loop for all of the library
    for(int i = 0; i < library->count; i++){
        //Make conditional to see if the book is in or not
        if(strcmp(library->library[i]->title, bookTitle) == 0 && strcmp(library->library[i]->author, bookAuthor) == 0 && library->library[i]->year == bookYear){
            //Make conditional if the book is checked out or not
            if(library->library[i]->is_available == 1){

                //Set availability to 0, or checked out
                library->library[i]->is_available = 0;

                //Call find book function
                findBook(library, bookTitle, bookAuthor, bookYear);

                //Say that it is checked out now
                printf("Book with title %s, author %s, and year %d is checked out\n", library->library[i]->title, library->library[i]->author, library->library[i]->year);
            
            } else if (library->library[i]->is_available == 0){
                //Call find book function
                findBook(library, bookTitle, bookAuthor, bookYear);

                //Say that it was already checked out
                printf("Book with title %s, author %s, and year %d is already checked out.\n", library->library[i]->title, library->library[i]->author, library->library[i]->year);
            
            }
        } else {
            //Add one to the timer
            timer++;
        }

        //Make conditional if timer reaches the count threshold
        if(timer == library->count){
            //Print no book was found
            printf("Book not found\n");
        }
    }
}

//Return book Function
void returnBook(Library *library, char *bookTitle, char *bookAuthor, int bookYear){
    //Make timer
    int timer = 0;
    
    //Loop for all of the library
    for(int i = 0; i < library->count; i++){
        //Make conditional to see if the book is in or not
        if(strcmp(library->library[i]->title, bookTitle) == 0 && strcmp(library->library[i]->author, bookAuthor) == 0 && library->library[i]->year == bookYear){;
            //Make conditional if the book is checked out or not
            if(library->library[i]->is_available == 0){
                
                //Set availability to 0, or checked out
                library->library[i]->is_available = 1;

                //Call find book function
                findBook(library, bookTitle, bookAuthor, bookYear);

                //Say that it is checked out now
                printf("Book with title %s, author %s, and year %d is returned.\n", library->library[i]->title, library->library[i]->author, library->library[i]->year);
            
            } else if (library->library[i]->is_available == 1){
                //Call find book function
                findBook(library, bookTitle, bookAuthor, bookYear);

                //Say that it was already checked out
                printf("Book with title %s, author %s, and year %d is not checked out.\n", library->library[i]->title, library->library[i]->author, library->library[i]->year);
            
            }

        } else {
            //Add one to the timer
            timer++;

        }

        //Make conditional if timer reaches the count threshold
        if(timer == library->count){
            //Print no book was found
            printf("Book not found\n");
        }
    }
}

//Make main function
int main(int argc, char **argv){
    //Open the file input from the terminal
    FILE *inp = fopen(argv[1], "r");

    //Create string for the action along with int for year
    char action[SIZE];
    char fileLine[SIZE];
    char fileTitle[SIZE];
    char fileAuthor[SIZE];
    int fileYear;

    //Open the structs
    Book books;
    Library *library = (Library *) malloc (sizeof(Library)); 
    library->library = malloc(maxBooks * sizeof(Book *)); 

    //Set library count to 0
    library->count = 0;

    //Make conditional if the file doesn't exist
    if(inp == NULL){
        //Print that nothing was available
        printf("No file was opened");
        
        //return 0
        return 0;
    }
    else{
        //Make loop until contents of the file are fully read
        while(fgets(action, sizeof(action), inp) != NULL){
            //removing the new line character
            action[strcspn(action, "\n")] = 0;

            //Set the size of the dynamic arrays
            books.title = malloc(SIZE * sizeof(char));
            books.author = malloc(SIZE * sizeof(char));

            //Make sure to not read further into file when just printing
            if (strcmp(action, "print") != 0){
                //Read in the full line of the file
                fgets(fileLine, sizeof(fileLine), inp);

                //Separate the details of the line into the title, author, and year
                sscanf(fileLine, "%[^,], %[^,], %d", fileTitle, fileAuthor, &fileYear);
            }

            //Set the title, author, and year into the struct based on the line from the file
            strcpy(books.title, fileTitle);
            strcpy(books.author, fileAuthor);
            books.year = fileYear;

            //Make conditional to determine what action is requested, or it there was an issue
            if (strcmp(action, "add") == 0){
                //Call the add book function
                addBook(library, books.title, books.author, books.year);

            } else if (strcmp(action, "remove") == 0){
                //Call the remove book function
                removeBook(library, books.title, books.author, books.year);

            } else if (strcmp(action, "print") == 0){
                //Call print library function
                printLibrary(library);

            } else if (strcmp(action, "checkout") == 0){
                //Call the checkout book function
                checkoutBook(library, books.title, books.author, books.year);

            } else if (strcmp(action, "return") == 0){
                //Call the return book function
                returnBook(library, books.title, books.author, books.year);

            } else {
                //State that nothing occurred
                printf("No action was taken\n");

            }

            //Free the memory for book titles and authors
            free(books.title);
            free(books.author);
        }
    }

    //Free all memory
    for(int i = 0; i < library->count;i++){
        free(library->library[i]->title);
        free(library->library[i]->author);
        free(library->library[i]);

    }
    free(library->library);
    free(library);

    //Close the file
    fclose(inp);

    //return 0
    return 0;
}