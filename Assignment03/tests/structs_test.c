#include <stdio.h>
#include <string.h>

static const char NEWLINE = '\n';

/*
 * struct [structure tag] {
 *
 *     member definition;
 *     member definition;
 *     ...
 * } [struct variables]
 *
 *
 * structure tag - optional
 * member definition - normal variable type
 */
struct Books {
    char title[50];
    char author[50];
    char subject[100];
    int book_id;
}; 

struct Movies {
    char title[50];
    char director[50];
    char genre[50];
    int movie_id;
} movie; /* We can assign one or more variables here immediate declaration &  assignment */

struct Paintings {
    char title[50];
    char artist[50];
    char period[50];
    int painting_id;
};

/* 
 * Printing out a struct 
 */
void printMovie(struct Movies movie) {
    printf("Movie Title: %s\n", movie.title);
    printf("Movie Director: %s\n", movie.director);
    printf("Movie Genre: %s\n", movie.genre);
    printf("Movie ID: %d\n", movie.movie_id);
    printf("%c", NEWLINE);
}

/*
 * Printing out a struct using pointers 
 */
void printPainting(struct Paintings * painting) {
    printf("Painting Title: %s\n", painting->title);
    printf("Painting Artist: %s\n", painting->artist);
    printf("Painting Period: %s\n", painting->period);
    printf("Painting ID: %d\n", painting->painting_id);
    printf("%c", NEWLINE);
}

/* Main Procedure */
int main(int argc, char * argv[]) {
    
    /* Type declaration */
    struct Books book;
    struct Paintings painting;

    /* Specifications */
    strcpy(book.title, "C Programming");
    strcpy(book.author, "Nuha Ali");
    strcpy(book.subject, "C Programming Tutorial");
    book.book_id = 64954407;

    strcpy(movie.title, "Twilight");
    strcpy(movie.director, "Catherine Hardwicke");
    strcpy(movie.genre, "Vampire Fantasy Romance");
    movie.movie_id = 59482938;

    strcpy(painting.title, "The Starry Night");
    strcpy(painting.artist, "Vincent van Gogh");
    strcpy(painting.period, "Post-Impressionism");
    painting.painting_id = 985768939;
    /* END SPEC */

    /* Accessing - Basic Example */
    printf("Book Title: %s\n", book.title);
    printf("Book Author: %s\n", book.author);
    printf("Book Subject: %s\n", book.subject);
    printf("Book Book ID: %d\n", book.book_id);
    printf("%c", NEWLINE);

    /* pass struct as function argument */
    printMovie(movie);

    /* pass struct as a pointer */
    printPainting(&painting);
}
