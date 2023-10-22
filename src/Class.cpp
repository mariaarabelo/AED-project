//
// Created by alexandre on 10-10-2023.
//

#include "Class.h"

Class::Class(const std::string &class_code, const std::vector<Lecture> &lectures, const std::vector<Student>  &students) {
    class_code_ = class_code;
    for (const auto &l : lectures) {
        if (l.class_code() == class_code_) {
            lectures_.push_back(l);
        }
    }
    for (const auto &s : students) {
        std::list<std::string> ucs;
        for (const auto &c : s.enrolled_classes()) {
            if (c.second  == class_code) {
                ucs.push_back(c.first);
            }
        }
        //PROBLEM RIGHT HERE, WERE  ADDING ALL STUDENTRS
        enrolled_students_.emplace_back(std::make_shared<Student>(s), ucs);
    }
}

std::string Class::class_code() const {
    return class_code_;
}

void Class::printLectures() const{
    for (const auto &l : lectures_) {
        l.printLecture();
    }
}

Lecture Class::getLecture(const std::string &code) const {
    for (const auto &l : lectures_) {
        if (l.uc_code() == code) return l;
    }
}

const std::vector<Lecture> &Class::lectures() const {
    return lectures_;
}

void Class::printEnrolledStudents() const {
    for (const auto &p : enrolled_students_) {
        p.first->printStudent();
    }
}

size_t Class::countEnrolledStudents() const {
    return enrolled_students_.size();
}

