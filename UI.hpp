#ifndef UI_HPP
#define UI_HPP

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
#include <filesystem>
#include "Win.hpp"
#include "IWin.hpp"
#include "fileio.hpp"
#include "util.hpp"
#include "ScrollWin.hpp"
#include "SelectionList.hpp"
#include "FileBrowser.hpp"
#include "Widget.hpp"
#include "WidgetWin.hpp"
#include "LabelWidget.hpp"
#include "ButtonWidget.hpp"
#include "WinMan.hpp"

using namespace std;
namespace fs = filesystem;

class UI : public Observer {
public:
    UI() {
        left_win = nullptr;
        right_win = nullptr;
        left_dir = fs::current_path();
        right_dir = fs::current_path();
        current = left_win;
    }
    int run() {
        WinMan winman;
        
        vector<string> files = dirlist(dirinfo("."));

        initscr();
        noecho();
        int screen_height = getmaxy(stdscr);
        int screen_width = getmaxx(stdscr);
        left_win = new FileBrowser(screen_height, screen_width / 2, 0, 0, false, ".");
        winman.add_win(left_win);
        left_win->set_active(true);
        right_win = new FileBrowser(screen_height, screen_width / 2, 0, screen_width / 2, false, ".");
        winman.add_win(right_win);
        //left_win->load_lines(files);
        //right_win->load_lines(files);
        right_win->set_working_directory("/home/rowan/code/name-tbd/testfolder");
        WidgetWin* welcome_dialog = new WidgetWin(3, 20, 0, 0, true);
        winman.add_win(welcome_dialog);
        ButtonWidget *welcome_button = new ButtonWidget(0, 0, "Welcome"); // TODO: Get widget window displaying and fix double free
        
        welcome_dialog->add_widget(welcome_button);
        welcome_button->add_observer(this, "pressed");
        welcome_dialog->set_active_widget(0);
        welcome_dialog->set_z(1);

        current = welcome_dialog;

        welcome_dialog->update();

        nodelay(current->get_window(), false);
        bool keep_running = true;
        while (keep_running) {
            winman.draw();
            keep_running = handle_input(getch());
        }

        endwin();

        return 0;
    }
    virtual void on_notify(Subject *subject, string event) {
        if (event == "pressed") {
            cerr << "Button Pressed" << endl;
            current = left_win;
        }
    }
private:
    FileBrowser *left_win;
    FileBrowser *right_win;
    IWin *current;
    bool handle_input(int c) {
        switch (c) {
        case '\t':
            if (current == static_cast<IWin*>(left_win)) {
                current = right_win;
                left_win->set_active(false);
                right_win->set_active(true);
            } else if (current == static_cast<IWin*>(right_win)) {
                current = left_win;
                left_win->set_active(true);
                right_win->set_active(false);
            } else {
                current->process_input(c);
            }
            break;
        case KEY_F(5):
        case 'c':
            copy_selected_file();
            break;
        case ERR:
            cerr << "error" << endl;
            break;
        case 'q':
            return false;
            break;
        default:
            cerr << "UI handle_input calling process_input" << endl;
            current->process_input(c);
        }

        return true;
    }
    void copy_selected_file() {
        FileBrowser *to_panel = (current == right_win) ? left_win : right_win;
        fs::copy(static_cast<FileBrowser*>(current)->get_selected_file(), to_panel->get_working_directory());
    }
    string left_dir;
    string right_dir;
};

#endif