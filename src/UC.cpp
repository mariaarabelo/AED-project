//
// Created by alexandre on 10-10-2023.
//

#include "UC.h"

#include <string>
#include <vector>


UC::UC(const std::string &uc_code, const std::vector<Class> &classes) {
    this->uc_code_ = uc_code;
    classes_ = new std::vector<Class>{classes};
}

std::string UC::uc_code()  const{
    return uc_code_;
}

std::vector<Class> *UC::classes() const {
    return classes_;
}


Class *UC::get_class(const std::string &class_) const {
    for (const auto &c : *classes_) {
        if (class_ == c.class_code()) return c;
    }
}

UC::~UC() {
    delete(classes_);
}
