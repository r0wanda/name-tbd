#ifndef FILEIO_H
#define FILEIO_H

#include <map>
#include <string>
#include <sys/stat.h>
#include <vector>

using namespace std;

map<string, struct stat> dirinfo(string dirname);
char copy_file(string src, string dst);
vector<string> dirlist(map<string, struct stat> info);
map<string, string> dirmap(map<string, struct stat> info);

#endif