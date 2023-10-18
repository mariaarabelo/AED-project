//
// Created by alexandre on 10-10-2023.
//

#include "Class.h"

Class::Class(const std::string &class_code, const std::vector<Lecture> &lectures) {
    class_code_ = class_code;
    lectures_ = new std::vector<Lecture>;
    for (const auto &l : lectures) {
        if (l.class_code() == class_code_) {
            lectures_->push_back(l);
        }
    }
}

std::string Class::class_code() const {
    return class_code_;
}

Class::~Class() {
    delete(lectures_);
}

void Class::printLectures() const{
    for (const auto &l : *lectures_) {
        l.printLecture();
    }
}
