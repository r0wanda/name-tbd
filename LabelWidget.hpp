#pragma once
#include "Widget.hpp"

class LabelWidget : public Widget {
public:
    LabelWidget() : Widget() {
        text = "Label";
    }
    LabelWidget(string the_text) : Widget() {
        text = the_text;
    }
    virtual void draw(WINDOW *w) {
        wmove(w, y, x);
        wprintw(w, text.c_str());
    }
private:
    string text;
};