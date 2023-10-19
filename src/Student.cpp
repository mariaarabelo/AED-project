//
// Created by alexandre on 10-10-2023.
//

#include "Student.h"

Student::Student(const std::string& student_name, const std::string& student_code,
        const std::vector<std::pair<std::string, std::string>> &codes){
    this->student_name_ = student_name;
    this->student_code_ = student_code;
    this->enrolled_classes_ = codes;
}

std::string Student::student_code() const {
    return student_code_;
}

std::string Student::student_name() const {
    return student_name_;
}

const std::vector<std::pair<std::string, std::string>> &Student::enrolled_classes() const {
    return enrolled_classes_;
}

