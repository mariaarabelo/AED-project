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

/**
 * @brief The Student class
 */
class Student {
private:
    std::string student_code_;
    std::string student_name_;
    std::vector<std::pair<std::string, std::string>> enrolled_classes_; //<uc_code, class_code>

public:
    /**
     * @brief Student constructor
     * @param student_name name of student
     * @param student_code student code
     * @param codes a vector of pairs of uc and class codes
     */
    Student(const std::string& student_name, const std::string& student_code, const std::vector<std::pair<std::string, std::string>>
    &codes);

    std::string student_code() const;
    std::string student_name() const;
    bool operator==(const Student& other) const;
    bool operator<(const Student &other) const;
    /**
     * @brief enrolls student in UC
     * @param c pair of uc and class
     * @return true if able to enroll
     */
    bool enrollInUC(const std::pair<std::string, std::string> &c);
    const std::vector<std::pair<std::string, std::string>> &enrolled_classes() const;
    std::vector<std::string> enrolled_classes_id() const;
    std::vector<std::string> enrolled_ucs_id() const;
    /**
     * @brief removes student from UC
     * @param uc
     * @return true if able to remove
     */
    bool removeFromUC(const std::string &uc);

};


#endif //AED_PROJECT_STUDENT_H