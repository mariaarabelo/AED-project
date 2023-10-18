//
// Created by alexandre on 10-10-2023.
//

#include "Student.h"

Student::Student(const std::string& student_name, const std::string& student_code,
                 const std::vector<std::pair<std::string,
                 std::string>> &codes,const std::vector<UC> &ucs){
    this->student_name_ = student_name;
    this->student_code_ = student_code;
    enrolled_classes_ = new std::vector<std::pair<UC *, Class *>>;
    for (const auto &code : codes) {

    }

}

std::string Student::student_code() const {
    return student_code_;
}

std::string Student::student_name() const {
    return student_name_;
}

std::vector<std::pair<UC *, Class *>> *Student::enrolled_classes() const {
    return enrolled_classes_;
}

Student::~Student() {
    delete(enrolled_classes_);
}

