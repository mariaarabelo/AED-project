//
// Created by alexandre on 10-10-2023.
//

#ifndef AED_PROJECT_STUDENT_H
#define AED_PROJECT_STUDENT_H

#include <string>
#include <vector>
#include "UC.h"

class Student {
    private:
    std::string s_code;
    std::string s_name;
    std::vector<Class> e_classes;

    public:
    Student(const std::string& student_name, const std::string& student_code);
    std::string student_code() const;
    std::string student_name() const;
    std::vector<Class> enrolled_classes() const;
    std::string &student_code();
    std::string &student_name();
    std::vector<Class> &enrolled_classes();

};


#endif //AED_PROJECT_STUDENT_H
