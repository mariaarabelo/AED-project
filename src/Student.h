//
// Created by alexandre on 10-10-2023.
//

#ifndef AED_PROJECT_STUDENT_H
#define AED_PROJECT_STUDENT_H

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <set>

class Student {
    private:
    std::string student_code_;
    std::string student_name_;
    std::vector<std::pair<std::string, std::string>> enrolled_classes_; //<uc_code, class_code>

    public:
    Student(const std::string& student_name, const std::string& student_code, const std::vector<std::pair<std::string, std::string>>
            &codes);
    std::string student_code() const;
    std::string student_name() const;
    bool operator==(const Student& other) const;
    void enrollInUC(const std::pair<std::string, std::string> &c);
    const std::vector<std::pair<std::string, std::string>> &enrolled_classes() const;
    void printStudent() const;

    std::vector<std::string> enrolled_classes_id() const;

    std::vector<std::string> enrolled_ucs_id() const;
};


#endif //AED_PROJECT_STUDENT_H
