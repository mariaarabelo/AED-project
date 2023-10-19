//
// Created by alexandre on 10-10-2023.
//

#ifndef AED_PROJECT_CLASS_H
#define AED_PROJECT_CLASS_H

#include <string>
#include <vector>
#include "Lecture.h"

class Class {
private:
    std::string class_code_;
    std::vector<Lecture> *lectures_;
public:
    Class(const std::string &class_code, const std::vector<Lecture> &lectures);
    std::string class_code() const;
    void printLectures() const;
    Lecture getLecture(const std::string &code) const;
    ~Class();
};




#endif //AED_PROJECT_CLASS_H
