//
// Created by alexandre on 10-10-2023.
//

#ifndef AED_PROJECT_CLASS_H
#define AED_PROJECT_CLASS_H

#include <string>
#include <vector>
#include <memory>
#include <list>
#include "Lecture.h"
#include "Student.h"

class Class {
private:
    std::string class_code_;
    std::vector<Lecture> lectures_;
    std::vector<std::pair<std::shared_ptr<Student>,std::list<std::string>>> enrolled_students_;
public:
    Class(const std::string &class_code, const std::vector<Lecture> &lectures, const std::vector<Student>  &students);
    std::string class_code() const;
    void printLectures() const;
    void printEnrolledStudents() const;
    Lecture getLecture(const std::string &code) const;
    const std::vector<Lecture> &lectures() const;
};




#endif //AED_PROJECT_CLASS_H
