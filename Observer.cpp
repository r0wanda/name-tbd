#include <iostream>
#include "Observer.hpp"

using namespace std;

void Observer::on_notify(Subject *the_subject, string the_event) {
    cout << "Recieved event: " << the_event << endl;
}

Observer::~Observer() {};
