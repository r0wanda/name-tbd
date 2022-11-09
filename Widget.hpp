#pragma once

#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <sys/types.h>
#include <bitset>
#include <curses.h>
#include <unistd.h>
#include "Subject.hpp"

using namespace std;

class Widget : public Subject {
public:
    Widget() {

    }
    Widget(int new_y, int new_x) {
        y = new_y;
        x = new_x;
    }
    Widget(Widget &w) {
        y = w.y;
        x = w.x;
        selectable = w.selectable;
    }
    static Widget* focused;
    int get_width() {
        return 10; // TODO: Have an actual width variable
    }
    int get_height() {
        return 1; // TODO: Have an actual height variable
    }
    int get_x() {
        return x;
    }
    int get_y() {
        return y;
    }
    bool get_active() {
        return active;
    }
    void set_x(int new_x) {
        x = new_x;
    }
    void set_y(int new_y) {
        y = new_y;
    }
    void set_position(int new_x, int new_y) {
        x = new_x;
        y = new_y;
    }
    virtual void process_input(int c) {
        
    }
    virtual void draw(WINDOW *w) {

    }
    virtual void set_active(bool new_active) {
        active = new_active;
    }
protected:
    int x;
    int y;
    bool selectable = false;
    bool active = false;
};
Widget* Widget::focused;
