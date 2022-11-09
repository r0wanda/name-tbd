#include "Subject.hpp"

using namespace std;

Subject::Subject() {

}

void Subject::add_observer(Observer *observer, string event) {
    observers[event].push_back(observer);
}
void Subject::remove_observer(Observer *observer, string event) {
    vector<Observer*>::iterator i;
    vector<Observer*> *event_observers = &observers[event];
    for (i = event_observers->begin(); i != event_observers->end(); i++) {
        if (*i == observer) {
            event_observers->erase(i);
            break;
        }
    }
}

void Subject::notify(string event) {
    for (auto o : observers[event]) {
        o->on_notify(this, event);
    }
}
