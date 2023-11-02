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

std::vector<std::pair<std::string, std::string>> Class::getEnrolledStudents() const {
    std::vector<std::pair<std::string, std::string>> v;
    for (const auto &p: enrolled_students_){
        std::pair<std::string, std::string> pair = {(p.first)->student_name(), p.first->student_code()};
        if (find(v.begin(), v.end(), pair) == v.end())
        v.emplace_back(pair);
    }
    return v;
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
