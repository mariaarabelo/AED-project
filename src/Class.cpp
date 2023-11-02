//
// Created by alexandre on 10-10-2023.
//

#include "Class.h"

Class::Class(const std::string &class_code, const std::set<Lecture> &lectures, const std::set<Student>  &students) {
    class_code_ = class_code;
    for (const auto &l : lectures) {
        if (l.class_code() == class_code_) {
            lectures_.insert(l);
        }
    }
    for (const auto &s : students) {
        for (const auto &c : s.enrolled_classes()) {
            if (c.second  == class_code) {
                auto uc = c.first;
                auto it = std::find_if(enrolled_students_.begin(), enrolled_students_.end(),
                                       [uc](const std::pair<std::string, std::list<Student>> &obj) {
                   return  obj.first == uc;
                });
                auto itt = std::find_if(student_count_.begin(), student_count_.end(),
                                        [uc](const std::pair<std::string, int> &other) {
                                            return other.first == uc;
                                        });
                if (it != enrolled_students_.end()) {
                    it->second.push_back(s);
                    itt->second++;
                }
                else {
                    std::list<Student> l;
                    l.push_back(s);
                    enrolled_students_.emplace_back(uc, l);
                    student_count_.emplace_back(uc, 1);
                }
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

const std::set<Lecture> &Class::lectures() const {
    return lectures_;
}

size_t Class::countEnrolledStudents() const {
    return enrolled_students_.size();
}

bool Class::add_student_to_class(const Student &student, const std::string &uc) {
    auto it = std::find_if(enrolled_students_.begin(), enrolled_students_.end(), [uc]
    (const std::pair<std::string, std::list<Student>> &obj) {
       return obj.first == uc;
    });
    if (it == enrolled_students_.end()) return false;
    auto itt = std::find(it->second.begin(), it->second.end(), student);
    if (itt != it->second.end()) return false;
    it->second.push_back(student);
    return true;
}

bool Class::operator<(const Class &other) const{
    return class_code_ < other.class_code();
}

int Class::get_student_count(const std::string &uc) const{
    auto it = std::find_if(student_count_.begin(), student_count_.end(), [uc](const std::pair<std::string, int> &other) {
        return other.first == uc;
    });
    if (it != student_count_.end()) {
        return it->second;
    }
    return -1;
}

bool Class::remove_student_from_class(const Student &student, const std::string &uc) {
    auto it = std::find_if(enrolled_students_.begin(),enrolled_students_.end(),
                           [uc](const std::pair<std::string, std::list<Student>> &obj) {
        return obj.first == uc;
    });
    if (it == enrolled_students_.end()) return false;
    it->second.remove(student);
    auto itt = std::find_if(student_count_.begin(), student_count_.end(),
                            [uc](const std::pair<std::string, int> &other) {
                                return other.first == uc;
                            });
    itt->second--;
    return true;
}
