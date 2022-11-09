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
#include "ScrollWin.hpp"
#include "UI.hpp"

using namespace std;

int main(int argc, char** argv) {
    UI ui;
    return ui.run();
}
