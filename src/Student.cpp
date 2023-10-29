//
// Created by alexandre on 10-10-2023.
//

#include "Student.h"

Student::Student(const std::string& student_name, const std::string& student_code,
        const std::vector<std::pair<std::string, std::string>> &codes){
    this->student_name_ = student_name;
    this->student_code_ = student_code;
    if (codes.size() <= 7) {
        for (const auto &p : codes) {
            enrolled_classes_.push(p);
        }
    }
}

std::string Student::student_code() const {
    return student_code_;
}

std::string Student::student_name() const {
    return student_name_;
}

std::vector<std::pair<std::string, std::string>> Student::enrolled_classes() const {
    auto copy_stack = enrolled_classes_;
    std::vector<std::pair<std::string, std::string>> v;
    while (!copy_stack.empty()) {
        v.push_back(copy_stack.top());
        copy_stack.pop();
    }
    return v;
}

void Student::enrollInUC(const std::pair<std::string, std::string> &c) {
    if (enrolled_classes_.size() < 7) {
        enrolled_classes_.push(c);
    } else {
        //TODO: Implement a try and catch system and throw error in situations like this
        std::cout << "Max number of students reached\n";
    }
}

void Student::printStudent() const {
    std::cout << student_name_ << "||" << student_code_ << "\n";
}

bool Student::operator==(const Student& other) const {
    return student_code_ == other.student_code_;
}

bool Student::changeUCClass(const std::string &uc, const std::string &c) {
    bool flag = false;
    std::stack<std::pair<std::string, std::string>> temp_stack;
    while (!enrolled_classes_.empty()) {
        if (enrolled_classes_.top().first == uc) {
            auto top = enrolled_classes_.top();
            enrolled_classes_.pop();
            top.second = c;
            enrolled_classes_.push(top);
            flag = true;
            break;
        }
        temp_stack.push(enrolled_classes_.top());
        enrolled_classes_.pop();
    }
    while (!temp_stack.empty()) {
        enrolled_classes_.push(temp_stack.top());
        temp_stack.pop();
    }
    return flag;
}

bool Student::undo_recent_enrollment() {
    if (enrolled_classes_.empty()) return false;
    enrolled_classes_.pop();
    return true;
}

bool Student::removeFromUC(const std::string &uc) {
    if (enrolled_classes_.empty()) return false;
    bool flag = false;
    std::stack<std::pair<std::string, std::string>> temp;
    while (!enrolled_classes_.empty()) {
        if (enrolled_classes_.top().first == uc) {
            recently_removed_classes_.push(enrolled_classes_.top());
            enrolled_classes_.pop();
            flag = true;
            break;
        }
        temp.push(enrolled_classes_.top());
        enrolled_classes_.pop();
    }
    while (!temp.empty()) {
        enrolled_classes_.push(temp.top());
        temp.pop();
    }
    return flag;
}
