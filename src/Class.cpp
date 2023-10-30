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
                enrolled_students_.emplace_back(std::make_shared<Student>(s), ucs);
            }
        }
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

bool Class::remove_student_from_class(const std::shared_ptr<Student> &student) {
    auto it = enrolled_students_.begin();
    while (it != enrolled_students_.end()) {
        if (it->first == student) {
            auto c = *it;
            enrolled_students_.remove(c);
            recently_removed_students_.push(c);
            return true;
        }
        it++;
    }
}

bool Class::add_student_to_class(const std::shared_ptr<Student> &student, const std::list<std::string> &ucs) {
    for (auto &s : enrolled_students_) {
        if (s.first == student) {
            for (const auto &a : ucs) {
                if (std::find(s.second.begin(), s.second.end(), a) == s.second.end()) {
                    s.second.push_back(a);
                }
            }
            return true;
        }
    }
    std::pair<std::shared_ptr<Student>,std::list<std::string>> p = {student, ucs};
    enrolled_students_.push_back(p);
}
