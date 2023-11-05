//
// Created by alexandre on 10-10-2023.
//

#include "UC.h"

#include <string>
#include <vector>


UC::UC(const std::string &uc_code, const std::list<std::shared_ptr<Class>> &classes,
       const std::list<Student> &enrolled_students) {
    this->uc_code_ = uc_code;
    this->classes_ = classes;
    this->enrolled_students_ = enrolled_students;
}

std::string UC::uc_code()  const{
    return uc_code_;
}

const std::list<std::shared_ptr<Class>> &UC::classes() const {
    return classes_;
}

void UC::removeClass(const std::shared_ptr<Class> &c) {
    classes_.remove(c);
}

void UC::printClasses() {
    for (const auto &c : classes_) {
        std::cout << c->class_code() << "\n";
    }
}

const std::list<Student> &UC::enrolled_students() const {
    return enrolled_students_;
}

unsigned UC::countEnrolledStudents() const {
    return (unsigned)enrolled_students_.size();
}

bool UC::enroll_student(const Student &student) {
    auto it = std::find(enrolled_students_.begin(), enrolled_students_.end(), student);
    if (it != enrolled_students_.end()) return false;
    enrolled_students_.push_back(student);
    return true;
}

bool UC::remove_student(const Student &student) {
    auto it = std::find(enrolled_students_.begin(), enrolled_students_.end(), student);
    if (it == enrolled_students_.end()) return false;
    enrolled_students_.remove(student);
    return true;
}
