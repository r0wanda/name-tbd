#pragma once
#include "Win.hpp"
#include "Observer.hpp"

using namespace std;

class WinMan: public Observer {
public:
    void add_win(Win *win) {
        win->add_observer(this, "set_z");
        insert_win(win);
    }

    void remove_win(Win *win) {
        win->remove_observer(this, "set_z");
        // TODO: Finish this
    }

    virtual void on_notify(Subject *the_subject, string the_event) {
        if (the_event == "set_z") {
            int win_index = find_win((Win*)(the_subject));
            if (win_index == -1)
                cerr << "Subject window not found in window list" << endl;
            Win *tmp = windows[win_index];
            windows.erase(windows.begin()+win_index);
            insert_win(tmp);
        }
    }

    void draw() {
        wnoutrefresh(stdscr);
        for (Win *w : windows) {
            wnoutrefresh(w->get_window());
        }
        doupdate();
    }

private:
    void insert_win(Win *win) {
        if (windows.empty()) {
            windows.push_back(win);
        } else {
            vector<Win*>::iterator it = windows.begin();
            while (it != windows.end() && (*it)->get_z() < win->get_z()) it++;

            if (it == windows.end()) {
                windows.push_back(win);
            } else {
                windows.insert(it, win);
            }
        }
    }

    int find_win(Win *win) {
        vector<Win*>::iterator it;
        for (int i = 0; i < windows.size(); i++) {
            if (static_cast<Win*>(windows[i]) == win) {
                return i;
            }
        }
        return -1;
    }

    vector<Win*> windows;
};
