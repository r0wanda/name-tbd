#ifndef FILEBROWSER_HPP
#define FILEBROWSER_HPP

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
#include <map>
#include <filesystem>
#include "Win.hpp"
#include "IWin.hpp"
#include "fileio.hpp"
#include "util.hpp"
#include "ScrollWin.hpp"
#include "SelectionList.hpp"

using namespace std;
namespace fs = std::filesystem;

class FileBrowser: public SelectionList {
public:
    FileBrowser(): SelectionList() {

    }
    FileBrowser(int nlines, int ncols, int begin_y, int begin_x, bool is_bordered, string working_directory):
    SelectionList(nlines, ncols, begin_y, begin_x, is_bordered) {
        set_working_directory(working_directory);
    }
    FileBrowser(const FileBrowser &filebrowser): SelectionList(filebrowser) {
        set_working_directory(filebrowser.get_working_directory());
    }

    string get_selected_file() { // TODO: Return absolute path or add an option to do so
        return file_names[get_selected_content()];
    }
    string get_working_directory() const {
        return working_directory;
    }

    void set_working_directory(string directory) {
        display_start = 0;
        fs::path new_path(directory);
        //cerr << new_path << endl;
        new_path = new_path.lexically_normal();
        directory = new_path.string();
        //cerr << directory << endl;
        if (fs::is_directory(new_path)) {
            contents = dirinfo(directory);
            working_directory = directory;
            file_names = dirmap(contents);
            /*for (pair<string, string> thepair : file_names) {
                cerr << thepair.first << " ";
            }
            cerr << endl;*/
            load_lines(dirlist(contents));
            for (string i : lines) {
                cerr << i;
            }
            cerr << endl;
            update();
        }
    }
    void open_selected_file() {
        fs::path selected_path(get_selected_file());
        fs::path working_path(working_directory);
        if (fs::is_directory(working_path / selected_path)) {
            set_working_directory((working_path / selected_path).string());
            //cerr << (working_path / selected_path).string() << endl;
        }
    }

    virtual void process_input(int c) {
        cerr << "FileBrowser Processing input" << endl;
        switch (c) {
        case 'j':
            move_lines(1);
            break;
        case 'k':
            move_lines(-1);
            break;
        case 'l':
            open_selected_file();
            break;
        }
    }
private:
    string working_directory;
    map<string, struct stat> contents;
    map<string, string> file_names; // line -> file name
};

#endif
