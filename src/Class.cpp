//
// Created by alexandre on 10-10-2023.
//

#include "Class.h"

Class::Class(const std::string &class_code, const std::vector<Lecture> &lectures) {
    class_code_ = class_code;
    for (const auto &l : lectures) {
        if (l.class_code() == class_code_) {
            lectures_.push_back(l);
        }
    }
}
