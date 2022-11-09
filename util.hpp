#ifndef UTIL_HPP
#define UTIL_HPP

using namespace std;

template<class T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi) {
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

string shorten_size(int bytes);

#endif