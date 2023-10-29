//
// Created by alexandre on 10-10-2023.
//

#ifndef AED_PROJECT_STUDENT_H
#define AED_PROJECT_STUDENT_H

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <stack>

class Student {
    private:
    std::string student_code_;
    std::string student_name_;
    std::stack<std::pair<std::string, std::string>> enrolled_classes_; //<uc_code, class_code>
    std::stack<std::pair<std::string, std::string>> recently_removed_classes_;

    public:
    Student(const std::string& student_name, const std::string& student_code, const std::vector<std::pair<std::string, std::string>>
            &codes);
    std::string student_code() const;
    std::string student_name() const;
    bool operator==(const Student& other) const;
    bool enrollInUC(const std::pair<std::string, std::string> &c);
    bool changeUCClass(const std::string &uc, const std::string &c);
    bool changeUC(const std::string &old_uc, const std::string &new_uc, const std::string &new_c);
    bool removeFromUC(const std::string &uc);
    bool undo_recent_enrollment();
    bool undo_recent_class_removal();
    std::vector<std::pair<std::string, std::string>> enrolled_classes() const;
    void printStudent() const;
};


#endif //AED_PROJECT_STUDENT_H
