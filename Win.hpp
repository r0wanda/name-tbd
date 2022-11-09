#ifndef WIN_HPP
#define WIN_HPP

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

class Win: public Subject {
public:
    Win() {
        window = newwin(getmaxy(stdscr), getmaxx(stdscr), getbegy(stdscr), getbegx(stdscr));
        bordered = false;
        content_area = subwin(window, getmaxy(stdscr), getmaxx(stdscr), getbegy(stdscr), getbegx(stdscr));
    }
    Win(int nlines, int ncols, int begin_y, int begin_x, bool is_bordered) {
        window = newwin(nlines, ncols, begin_y, begin_x);
        content_area = nullptr;
        set_bordered(is_bordered);
    }
    Win(const Win &w) {
        window = dupwin(w.window);
        set_bordered(w.bordered);
    }
    int get_y() {
        return getbegy(window);
    }
    int get_x() {
        return getbegx(window);
    }
    int get_max_y() {
        return getmaxy(window);
    }
    int get_max_x() {
        return getmaxx(window);
    }
    int get_cur_y() {
        return getcury(window);
    }
    int get_cur_x() {
        return getcurx(window);
    }
    int get_height() {
        return getmaxy(window) - getbegy(window);
    }
    int get_width() {
        return getmaxx(window) - getbegx(window);
    }
    int get_display_height() {
        return getmaxy(window) - getbegy(window) - (get_bordered() ? 2 : 0);
    }
    int get_display_width() {
        return getmaxx(window) - getbegx(window) - (get_bordered() ? 2 : 0);
    }
    bool get_bordered() {
        return bordered;
    }
    WINDOW* get_window() {
        return window;
    }
    int get_z() {
        return z;
    }

    void set_z(int new_z) {
        z = new_z;
        notify("set_z");
    }
    void set_y(int y) {
        mvwin(window, y, get_x());
    }
    void set_x(int x) {
        mvwin(window, get_y(), x);
    }
    void set_yx(int y, int x) {
        mvwin(window, y, x);
    }
    void set_bordered(bool newvalue) {
        bordered = newvalue;
        if (content_area)
            delwin(content_area);
            content_area = NULL;
        if (bordered) {
            content_area = subwin(window, get_height() - 2, get_width() - 2, get_y() + 1, get_x() + 1);
        } else {
            content_area = subwin(window, get_height(), get_width(), get_y(), get_x());
        }
    }

    void resize(int height, int width) {
        wresize(window, height, width);
    }
    virtual void update() {
    }
    void winrefresh() {
        if (bordered) box(window, ACS_VLINE, ACS_HLINE);
    }
    friend void swap(Win a, Win b) {
        using std::swap;
        swap(a.window, b.window);
        swap(a.content_area, b.content_area);
        swap(a.bordered, b.bordered);
    }
    Win& operator=(Win other) {
        swap(*this, other);
        return *this;
    }
protected:
    WINDOW* window;
    WINDOW* content_area;
private:
    bool bordered;
    int z;
    void drawbox() {
        box(window, ACS_VLINE, ACS_HLINE);
    }
};

#endif
