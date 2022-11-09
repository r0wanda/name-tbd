#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

int main() {
    const char *standout = "HELLO WORLD";
    const char *normal = "hello world";

    initscr();
    move(5, 15);
    attron(A_STANDOUT);
    printw(standout);
    attroff(A_STANDOUT);
    move(10, 20);
    printw(normal);
    refresh();

    return EXIT_SUCCESS;
}