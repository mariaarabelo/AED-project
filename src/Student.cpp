//
// Created by alexandre on 10-10-2023.
//

#include "Student.h"

Student::Student(const std::string& student_name, const std::string& student_code,
        std::vector<std::pair<std::string, std::string>> *codes, std::vector<UC *> *ucs){
    this->student_name_ = student_name;
    this->student_code_ = student_code;
    enrolled_classes_ = new std::vector<std::pair<UC *, Class *>>;
    for (auto &code : *codes) {
        std::string uc_code = code.first;
        std::string class_code = code.second;
        for (auto &uc : *ucs) {
            if (uc_code == uc->uc_code()) {
                std::pair<UC *, Class *> p;
                p.first = uc;
                p.second = &uc->get_class(class_code);
                enrolled_classes_->push_back(p);
            }
        }
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

