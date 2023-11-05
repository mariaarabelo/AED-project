//
// Created by alexandre on 10-10-2023.
//

#include "Student.h"

Student::Student(const std::string& student_name, const std::string& student_code,
                 const std::vector<std::pair<std::string, std::string>> &codes){
    this->student_name_ = student_name;
    this->student_code_ = student_code;
    if (codes.size() <= 7) {
        this->enrolled_classes_ = codes;
    }
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

std::vector<std::string> Student::enrolled_classes_id() const {
    std::vector<std::string> v;
    for (const std::pair<std::string, std::string>& p : enrolled_classes_){
        if (find(v.begin(), v.end(), p.second) == v.end()) {
            v.push_back(p.second);
        }
    }
    return v;
}

std::vector<std::string> Student::enrolled_ucs_id() const {
    std::vector<std::string> v;
    for (const std::pair<std::string, std::string>& p : enrolled_classes_){
        if (find(v.begin(), v.end(), p.second) == v.end()) {
            v.push_back(p.first);
        }
    }
    return v;
}

bool Student::enrollInUC(const std::pair<std::string, std::string> &c) {
    if (enrolled_classes_.size() < 7) {
        enrolled_classes_.push_back(c);
        return true;
    }
    return false;
}

bool Student::operator==(const Student& other) const {
    return student_code_ == other.student_code_;
}

bool Student::operator<(const Student &other) const {
    return this->student_code_ < other.student_code();
}

bool Student::removeFromUC(const std::string &uc) {
    auto it = std::find_if(enrolled_classes_.begin(), enrolled_classes_.end(),
                           [uc](const std::pair<std::string, std::string> &obj) {
                               return uc == obj.first;
                           });
    if (it != enrolled_classes_.end()) {
        enrolled_classes_.erase(it);
        return true;
    }

    return false;
}