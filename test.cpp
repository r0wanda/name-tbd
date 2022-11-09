#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <sys/types.h>
#include <bitset>
#include <curses.h>
#include "Observer.hpp"
#include "Subject.hpp"
#include "fileio.hpp"
#include "util.hpp"

using namespace std;

int main(int argc, char** argv) {
    // copy_file(argv[1], argv[2]);

    cout << boolalpha;

    map<string, struct stat> fileinfo = dirinfo(".");
    for (auto i:fileinfo)
    {
        mode_t mode = i.second.st_mode;
        cout << '-'
             << ((mode & S_IRUSR) ? 'r' : '-')
             << ((mode & S_IWUSR) ? 'w' : '-')
             << ((mode & S_IXUSR) ? 'x' : '-')
             << ((mode & S_IRGRP) ? 'r' : '-')
             << ((mode & S_IWGRP) ? 'w' : '-')
             << ((mode & S_IXGRP) ? 'x' : '-')
             << ((mode & S_IROTH) ? 'r' : '-')
             << ((mode & S_IWOTH) ? 'w' : '-')
             << ((mode & S_IXOTH) ? 'x' : '-')
             << ' ' << i.first << endl;
        //cout << bitset<8 * sizeof (mode_t)>(mode) << endl << (mode & S_IWGRP) << endl;
    }
    for (auto i:dirlist(fileinfo)) {
        cout << i << endl;
    }
    cout << "Testing clamp" << endl;
    cout << (clamp(0, -1, 1) == 0) << endl;
    cout << (clamp(-2, -1, 1) == -1) << endl;
    cout << (clamp(2, -1, 1) == 1) << endl;

    // Event handling

    cout << "Testing event handling" << endl;
    Subject s;
    Observer o;
    s.add_observer(&o, "hello");
    s.notify("hello");

    return 0;
}