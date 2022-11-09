#ifndef IWIN_HPP
#define IWIN_HPP

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
#include "Win.hpp"
#include "fileio.hpp"

using namespace std;

class IWin: public Win {
public:
    IWin(): Win() {
        next = nullptr;
        keypad(window, true);
    }
    IWin(int nlines, int ncols, int begin_y, int begin_x, bool is_bordered): Win(nlines, ncols, begin_y, begin_x, is_bordered) {
        next = nullptr;
        keypad(window, true);
    }
    IWin(const IWin &win): Win(win) {
        next = win.next;
        keypad(window, true);
    }
    virtual void process_input(int c) {
        cerr << "IWin processsing input" << endl;
    }
private:
    IWin* next; // Next IWin to be cycled to
    static IWin focused;
};

#endif