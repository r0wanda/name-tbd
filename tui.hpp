#ifndef TUI_HPP
#define TUI_HPP

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

using namespace std;

void init();
void scrollFiles();
void update();
void interact();

#endif