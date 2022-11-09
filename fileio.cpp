#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <vector>
#include <filesystem>
#include "dbg.hpp"
#include "util.hpp"

using namespace std;
namespace fs = std::filesystem;

char copy_file(string src, string dst)
{
    FILE *srcfile;
    FILE *dstfile;
    unsigned char cbuf[8192];
    size_t chr, chw;

    srcfile = fopen(src.c_str(), "r");
    check_debug(srcfile != NULL, "Failed to open source file");
    dstfile = fopen(dst.c_str(), "w");
    check_debug(dstfile != NULL, "Failed to open destination file");

    do
    {
        chr = fread(cbuf, 1, sizeof(cbuf), srcfile);
        if (chr)
        {
            chw = fwrite(cbuf, 1, chr, dstfile);
        }
        else
        {
            chw = 0;
        }
    } while (chr > 0 && chr == chw);

    fclose(srcfile);
    fclose(dstfile);

    return 0;

    error:
    exit(1);
}

map<string, struct stat> dirinfo(string dirname)
{
    map<string, struct stat> dirmap;
    DIR *d;
    struct dirent *entry;
    struct stat filestat;
    d = opendir(dirname.c_str());
    if (d)
    {
        while ((entry = readdir(d)) != NULL)
        {
            if (stat((fs::path{dirname} / entry->d_name).c_str(), &filestat) < 0)
            {
                //cerr << "Error: Could not stat file: " << entry->d_name << endl;
                fprintf(stderr, "could not stat file %s: %s", entry->d_name, strerror(errno));
                continue;
            }
            dirmap[string{entry->d_name}] = filestat;
        }
    }
    return dirmap;
}

string fileinfo(string fname, struct stat info) {
    mode_t mode = info.st_mode;
    off_t size = info.st_size;
    string r;
    r = r + "-" +
        ((mode & S_IRUSR) ? "r" : "-") +
        ((mode & S_IWUSR) ? "w" : "-") +
        ((mode & S_IXUSR) ? "x" : "-") +
        ((mode & S_IRGRP) ? "r" : "-") +
        ((mode & S_IWGRP) ? "w" : "-") +
        ((mode & S_IXGRP) ? "x" : "-") +
        ((mode & S_IROTH) ? "r" : "-") +
        ((mode & S_IWOTH) ? "w" : "-") +
        ((mode & S_IXOTH) ? "x" : "-") +
        " " + fname + " " +
        shorten_size(size);
    return r;
}

vector<string> dirlist(map<string, struct stat> info) {
    vector<string> results;
    map<string, struct stat>::iterator it = info.begin();
    while (++it != info.end())
        results.push_back(fileinfo(it->first, it->second));
    return results;
}

map<string, string> dirmap(map<string, struct stat> info) {
    map<string, string> results;
    map<string, struct stat>::iterator it = info.begin();
    while (++it != info.end())
        results[fileinfo(it->first, it->second)] = it->first;
    return results;
}
