#pragma once

#include <string>
#include "Subject.hpp"

class Subject;

class Observer {
public:
    virtual void on_notify(Subject *the_subject, std::string the_event);
    virtual ~Observer();
};