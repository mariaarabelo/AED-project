//
// Created by alexandre on 19-10-2023.
//

#ifndef AED_PROJECT_APPLICATION_H
#define AED_PROJECT_APPLICATION_H

#include <vector>
#include <utility>
#include <list>
#include <algorithm>
#include <memory>
#include <iostream>
#include "Lecture.h"
#include "File_Reader.h"
#include "UC.h"
#include "Student.h"
#include "globals.h"
#include "Schedule.h"


/**
 * @brief The Application class for managing and interacting with university data.
 */
class Application {
public:

    std::vector<std::pair<std::string, std::string>> check_year(const std::string& c);

    std::vector<std::pair<std::string, std::string>> class_id_student_number();

    std::vector<std::pair<std::string, std::string>> enrolled_students_in_ucs();

    /**
     * @brief Default constructor for the Application class.
     */
    Application();

    /**
     * @brief Destructor for the Application class.
     */
    ~Application();

    const std::set<Student> &students();

    const std::vector<Lecture> &lectures();

    /**
     * @brief returns a vector of pairs, holding student code and name
     * @return vector of pairs holding student code and name
     */
    std::vector<std::pair<std::string, std::string>> students_name_id();
    std::vector<std::string> class_codes();
    std::vector<std::string> ucs_codes();
    /**
     * @brief Get students enrolled in UC
     * @param uc_code code of the UC
     * @return vector of pairs that holds student's code and name
     */
    std::vector<std::pair<std::string, std::string>> students_from_uc(const std::string& uc_code);
    std::vector<std::string> classes_from_uc(const std::string &uc_code);
    /**
     * @brief Add a student to an uc. Complexity is O(n + m + p).
     * @param student the student
     * @param uc the uc
     * @param c the class
     * @param no_write optional, true if no write into students_classes file
     * @return string holding the result of the operation
     */
    std::string add_student_to_uc(const std::string &student, const std::string &uc, const std::string &c,
                                  const bool &no_write = false);
    /**
     * @brief Remove a student from an uc. Complexity is O(n + m + p).
     * @param student_code the student
     * @param uc the uc
     * @param c the class
     * @param no_write optional, true if no write into students_classes file
     * @return string holding the result of the operation
     */
    std::string remove_student_from_uc(const std::string &student_code, const std::string &uc, const std::string &c,
                                       const bool &no_write = false);

    /**
     * @brief Switch a student from one class no another. Complexity is O(n + m + p).
     * @param student_code student
     * @param uc uc
     * @param old_class the old class
     * @param new_class the new class
     * @param no_write optional, true if no write into students_classes file
     * @return string holding the result of the operation
     */
    std::string switch_student_class(const std::string &student_code, const std::string &uc,
                                     const std::string &old_class, const std::string &new_class, const bool &no_write = false);

    std::string students_class_from_uc(const std::string &uc_code, const Student &student);
    std::string reverse_change();
    std::vector<std::string> get_latest_change();
    std::vector<std::pair<std::string, std::string>> students_in_n_ucs(int n);

private:
    std::vector<Lecture> *lectures_;
    std::set<Student> *students_;
    std::vector<Class> *classes_;
    std::vector<UC> *ucs_;
    std::stack<std::vector<std::string>> changes_;
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
     * @brief Getter for a given UC.
     * @param code Code of the UC.
     * @return The UC.
     */
    UC getUC(const std::string &uc_code) const;

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

    /**
     * @brief Check if classes in a certain UC will be balanced when we add a student to c
     * @param uc the uc
     * @param c the class where student will be added
     * @return true if classes are balanced
     */
    bool will_classes_be_balanced(const std::string &uc, const std::string &c) const;

    /**
     * @brief Check if a student's schedule conflicts with a lecture
     * @param student
     * @param lecture
     * @return true if there is conflict
     */
    bool schedule_is_conflicting(const Student &student, const Lecture &lecture)const;

};


#endif //AED_PROJECT_APPLICATION_H
