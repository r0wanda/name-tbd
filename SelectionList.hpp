#ifndef SELECTIONLIST_HPP
#define SELECTIONLIST_HPP

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
#include <set>
#include "Win.hpp"
#include "IWin.hpp"
#include "fileio.hpp"
#include "util.hpp"
#include "ScrollWin.hpp"

using namespace std;

class SelectionList: public ScrollWin {
public:
    SelectionList(): ScrollWin() {
        selected = -1;
        active = false;
    }
    SelectionList(int nlines, int ncols, int begin_y, int begin_x, bool is_bordered):
    ScrollWin(nlines, ncols, begin_y, begin_x, is_bordered) {
        selected = -1;
        active = false;
    }
    SelectionList(const SelectionList &source): ScrollWin(source) {
        selected = source.selected;
        active = source.active;
    }
    void update() {
        ScrollWin::update();
        if (active && selected >= 0) {
            wmove(window, selected - display_start + offset, offset);
            wattron(window, A_STANDOUT);
            wprintw(window, "%s", lines[selected].c_str());
            wattroff(window, A_STANDOUT);
            wrefresh(window);
        }
    }
    void load_lines(vector<string> l) {
        lines = l;
        if (lines.size() > 0) {
            selected = 0;
        } else {
            selected = - 1;
        }
        update();
    }
    void move_lines(int l) {
        selected = clamp<int>(selected + l, 0 , lines.size() - 1);
        if (selected - display_start >= display_length - 1) {
            scroll_lines(selected - display_start - display_length + 1);
        } else if (selected < display_start) {
            scroll_lines(selected - display_start);
        } else {
            update();
        }
    }
    void set_selected(int l) {
        move_lines(l - selected);
    }
    void set_active(bool new_active_value) {
        active = new_active_value;
        update();
    }
    int get_selected() {
        return selected;
    }
    bool get_active() {
        return active;
    }
    string get_selected_content() {
        return lines[selected];
    }
protected:
private:
    int selected;
    bool active;
};

#endif