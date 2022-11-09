#ifndef MOVEDIALOG_HPP
#define MOVEDIALOG_HPP

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
#include "IWin.hpp"
#include "fileio.hpp"
#include "util.hpp"
using namespace std;

class MoveDialog : public IWin {
public:
    MoveDialog() : IWin() {

    }
    MoveDialog(int nlines, int ncols, int begin_y, int begin_x, bool is_bordered) : 
    IWin(nlines, ncols, begin_y, begin_x, is_bordered) {

    }
    MoveDialog(const MoveDialog &dialog) : IWin(dialog) {

    }
private:
};

#endif