#ifndef SCROLLWIN_HPP
#define SCROLLWIN_HPP

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

class ScrollWin: public IWin {
public:
    ScrollWin(): IWin() {
        display_start = 0;
        display_length = get_display_height();
    }
    ScrollWin(int nlines, int ncols, int begin_y, int begin_x, bool is_bordered):
    IWin(nlines, ncols, begin_y, begin_x, is_bordered) {
        display_start = 0;
        display_length = get_display_height();
    }
    ScrollWin(const ScrollWin &win): IWin(win) {
        lines = win.lines;
        display_start = win.display_start;
        display_length = win.display_length;
    }
    string get_line(int l) {
        return lines[l];
    }
    void load_lines(vector<string> l) {
        lines = l;
        update();
    }
    void scroll_lines(int l) {
        if (display_length < lines.size()) {
            display_start = clamp<int>(display_start + l, 0 , lines.size() - display_length);
            update();
        }
    }
    virtual void update() {
        offset = (get_bordered()) ? 1 : 0;
        /*if (get_bordered()) {
            wmove(window, 1, 1);
        } else {
            wmove(window, 0, 0);
        }*/
        wclear(window);
        winrefresh();
        wmove(window, offset, offset);
        //cerr << display_start << " " << display_length << " " << lines.size() << endl;
        for (int i = display_start; i < display_start + display_length && i < lines.size(); i++) {
        //    cerr << "Display start: " << display_start << " Display length: " << display_length << "Content: " << lines[i] << endl;
            wprintw(window, lines[i].c_str());
            wrefresh(window);
            wmove(window, get_cur_y() + 1, offset);
        }
        wrefresh(window);
        //cerr << "Updating something" << endl;
    }
    // TODO: string get_line_content(int l)
protected:
    vector<string> lines;
    int display_start;
    int display_length;
    char offset;
};

#endif