//
// Created by alexandre on 10-10-2023.
//

#include "UC.h"

#include <string>
#include <vector>


UC::UC(const std::string &uc_code, const std::list<std::shared_ptr<Class>> &classes,
       const std::list<std::shared_ptr<Student>> &enrolled_students) {
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

const std::list<std::shared_ptr<Student>> &UC::enrolled_students() const {
    return enrolled_students_;
}

void UC::printEnrolledStudents() {
    for (const auto &s : enrolled_students_) {
        s->printStudent();
    }
}

unsigned UC::countEnrolledStudents() const {
    return (unsigned)enrolled_students_.size();
}
