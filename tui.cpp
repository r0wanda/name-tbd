#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <sys/types.h>
#include <bitset>
#include <curses.h>
#include <unistd.h>
#include "fileio.hpp"
#include "tui.hpp"
#include "util.hpp"

using namespace std;

vector<string> files = dirlist(dirinfo("."));
int files_start;
int files_len;
WINDOW* box_insides;

void init() {
    initscr();

    box_insides = subwin(stdscr, getmaxy(stdscr) - 2, getmaxx(stdscr) - 2, 1, 1);

    files = dirlist(dirinfo("."));
    
    update();
    
    noecho();
    //scrollok(stdscr, true);
}

void update() {
    clear();
    box(stdscr, ACS_VLINE, ACS_HLINE);
    int y = getbegy(box_insides);
    files_len = getmaxy(box_insides);
    for (int i = files_start; i < files_start + files_len; i++) {
        move(y, 0);
        printw(files[i].c_str());
        y++;
    }
    refresh();
}

void scrollFiles(int lines) {
    files_start = clamp<int>(files_start + lines, 0 , files.size() - files_len);
    update();
}

void interact() {
    chtype c;
    while (true) {
        c = getch();
        if (c == 'k') {
            scrollFiles(1);
        } else if (c == 'j') {
            scrollFiles(-1);
        } else if (c == 'q') {
            break;
        }
    }
}
