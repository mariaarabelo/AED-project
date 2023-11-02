//
// Created by alexandre on 19-10-2023.
//

#ifndef AED_PROJECT_APPLICATION_H
#define AED_PROJECT_APPLICATION_H

#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
#include <memory>
#include <set>
#include <iostream>
#include "Lecture.h"
#include "File_Reader.h"
#include "UC.h"
#include "Student.h"
#include "Schedule.h"


/**
 * @brief The Application class for managing and interacting with university data.
 */
class Application {
public:

    /**
     * @brief Default constructor for the Application class.
     */
    Application();

    /**
     * @brief Destructor for the Application class.
     */
    ~Application();

    void test();

    /**
     * @brief Getter for the students.
     * @return A const reference to the vector of students.
     */
    const std::set<Student> &students();

    std::string add_student_to_uc(const std::string &student, const std::string &uc, const std::string &c);

    std::string remove_student_from_uc(const std::string &student_code, const std::string &uc, const std::string &c);

    std::string switch_student_class(const std::string &student_code, const std::string &uc,
                                     const std::string &old_class, const std::string &new_class);

    std::vector<std::pair<std::string, std::string>> students_name_id();

private:
    std::set<Lecture> *lectures_;
    std::set<Student> *students_;
    std::set<Class> *classes_;
    std::vector<UC> *ucs_;
    std::map<int, std::vector<Student>> yearStudentsMap;

    /**
     * @brief Helper function to instantiate classes.
     * @param classes A map of classes.
     */
    void instantiateClasses(std::map<std::string, std::list<std::string>> * classes);

    /**
     * @brief Helper function to instantiate UCs.
     * @param classes A map of classes.
     */
    void instantiateUCs(std::map<std::string, std::list<std::string>> * classes);

    /**
     * @brief Helper function to fill the yearStudentsMap.
     */
    void fillYearStudentsMap();

    /**
     * @brief Getter for a given UC.
     * @param code Code of the UC.
     * @return The UC.
     */
    UC getUC(const std::string &uc_code) const;

    /**
     * @brief Prints students enrolled in a specific year.
     * @param year The year of interest.
     */
    void printStudentsEnrolledInYear(const int &year);

    /**
     * @brief Counts students enrolled in a specific year.
     * @param year The year of interest.
     * @return The count of students.
     */
    unsigned countStudentsEnrolledInYear(const int &year);

    /**
     * @brief Prints the number of students per year
     * @param ascendingOrder 0 for decreasing order, 1 for ascending order.
     */
    void printStudentsPerYear(bool ascendingOrder);

    /**
     * @brief Prints the UCs with the most or least enrolled students.
     * @param n The number of UCs to print.
     * @param ascendingOrder 0 for decreasing order, 1 for ascending order.
     */
    void printUCsWithEnrolledStudents(int n, bool ascendingOrder);

    /**
     * @brief Prints the number of students in a specific UC's classes.
     * @param uc_code Code of the UC.
     * @param n_classes Number of classes to be printed.
     * @param ascendingOrder 0 for decreasing order, 1 for ascending order.
     */
    void printUcClassesStudents(const std::string &uc_code, const int &n_classes, bool ascendingOrder);

    /**
     * @brief Getter for a vector of pairs containing student names and IDs.
     * @return A const reference to the vector of pairs.
     */
    const std::vector<std::pair<std::string, std::string>> &Students_name_id();

    bool will_classes_be_balanced(const std::string &uc, const std::string &c) const;

    bool schedule_is_conflicting(const Student &student, const Lecture &lecture)const;
};


#endif //AED_PROJECT_APPLICATION_H
