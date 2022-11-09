#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Observer.hpp"


class Observer;

class Subject {
public:
    Subject();
    void add_observer(Observer *observer, std::string event);
    void remove_observer(Observer *observer, std::string event);
//protected:
    void notify(std::string event);
private:
    std::unordered_map<std::string, std::vector<Observer*>> observers;
};