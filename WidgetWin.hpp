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
#include "Widget.hpp"
#include "Win.hpp"
#include "IWin.hpp"
#include "Observer.hpp"

using namespace std;

class WidgetWin : public IWin, public Observer {
public:
    WidgetWin() : IWin(), Observer() {
        active_widget = -1;
    }
    WidgetWin(int nlines, int ncols, int begin_y, int begin_x, bool is_bordered):
    IWin(nlines, ncols, begin_y, begin_x, is_bordered), Observer() {
        active_widget = -1;
    }
    WidgetWin(const WidgetWin &win) : IWin(win), Observer() {
        active_widget = win.active_widget;
    }

    ~WidgetWin() {
        for (Widget *w : widgets) {
            delete w;
        }
    }

    virtual void update() {
        werase(window);
        for (Widget *w : widgets) {
            cerr << "Drawing widget" << endl;
            w->draw(window);
        }
    }

    int get_active_widget() {
        return active_widget;
    }
    void set_active_widget(int new_active_widget) {
        if (active_widget > -1) widgets[active_widget]->set_active(false);
        active_widget = new_active_widget;
        widgets[active_widget]->set_active(true);
    }

    void add_widget(Widget *w) {
        widgets.push_back(w);
    }

    virtual void process_input(int c) {
        switch (c) {
        case '\t':
            set_active_widget((active_widget + 1) % widgets.size());
            break;
        default:
            widgets[active_widget]->process_input(c);
        }
        update();
    }

private:
    vector<Widget*> widgets;
    int active_widget;
};
