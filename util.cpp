#include <sstream>
#include "util.hpp"

using namespace std;

string shorten_size(int bytes) {
    ostringstream ss;
    float q;
    int n = 0;
    char letters[6] = {'B', 'K', 'M', 'G', 'T', 'P'};
    for (q = bytes; q > 1000; q /= 1024) n++;
    ss.setf(ios_base::fixed);
    if (q - static_cast<int>(q) < .01) {
        ss.precision(0);
    } else {
        ss.precision(2);
    }
    ss << q << letters[n];
    return ss.str();
}