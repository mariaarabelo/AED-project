//
// Created by alexandre on 10-10-2023.
//

#include "UC.h"

#include <string>
#include <vector>


UC::UC(const std::string &uc_code, const std::list<Class *> &classes) {
    this->uc_code_ = uc_code;
    this->classes_ = classes;
}

std::string UC::uc_code()  const{
    return uc_code_;
}

const std::list<Class *> &UC::classes() const {
    return classes_;
}

void UC::removeClass(Class *c) {
    classes_.remove(c);
}

void UC::printClasses() {
    for (const auto &c : classes_) {
        std::cout << c->class_code();
    }
}
