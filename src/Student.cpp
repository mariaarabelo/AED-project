//
// Created by alexandre on 10-10-2023.
//

#include "Student.h"

Student::Student(const std::string& student_name, const std::string& student_code){
    this->student_name_ = student_name;
    this->student_code_ = student_code;
}

std::string Student::student_code() const {
    return student_code_;
}

std::string Student::student_name() const {
    return student_name_;
}

std::vector<Class> Student::enrolled_classes() const {
    return enrolled_classes_;
}

std::string  &Student::student_name() {
    auto &s = this->student_name_;
    return s;
}

std::string &Student::student_code() {
    auto &s = this->student_code_;
    return s;
}

std::vector<Class> &Student::enrolled_classes() {
    auto &e = this->enrolled_classes_;
    return e;
}
