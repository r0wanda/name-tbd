#pragma once

#include "Widget.hpp"

class ButtonWidget : public Widget {
public:
    ButtonWidget() : Widget() {
        selectable = true;
    }
    ButtonWidget(int new_y, int new_x, string new_text) : Widget(new_y, new_x) {
        text = new_text;
        selectable = true;
    }

    string get_text() {
        return text;
    }
    void set_text(string _text) {
        text = _text;
    }
    virtual void process_input(int c) {
        switch (c) {
        case '\n':
            notify("pressed");
        default:
            Widget::process_input(c);
        }
    }
    virtual void draw(WINDOW *w) {
        wmove(w, y, x);
        if (active) {
            wattron(w, A_STANDOUT);
            wprintw(w, text.c_str());
            wattron(w, A_STANDOUT);
        } else {
            wprintw(w, text.c_str());
        }
    }
private:
    string text;
};