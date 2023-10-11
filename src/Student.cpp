//
// Created by alexandre on 10-10-2023.
//

#include "Student.h"

Student::Student(const std::string& student_name, const std::string& student_code){
    this->s_name = student_name;
    this->s_code = student_code;
}

std::string Student::student_code() const {
    return s_code;
}

std::string Student::student_name() const {
    return s_name;
}

std::vector<Class> Student::enrolled_classes() const {
    return e_classes;
}

std::string  &Student::student_name() {
    auto &s = this->s_name;
    return s;
}

std::string &Student::student_code() {
    auto &s = this->s_code;
    return s;
}

std::vector<Class> &Student::enrolled_classes() {
    auto &e = this->e_classes;
    return e;
}
