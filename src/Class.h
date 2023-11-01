//
// Created by alexandre on 10-10-2023.
//

#ifndef AED_PROJECT_CLASS_H
#define AED_PROJECT_CLASS_H

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <list>
#include <set>
#include <stack>
#include "Lecture.h"
#include "Student.h"

class Class {
private:
    std::string class_code_;
    std::set<Lecture> lectures_;
    std::list<std::pair<std::shared_ptr<Student>,std::list<std::string>>> enrolled_students_;
    std::stack<std::pair<std::shared_ptr<Student>,std::list<std::string>>> recently_removed_students_;
public:

    /**
     * @brief Constructor for Class class
     * @param class_code The code of the class
     * @param lectures Vector with all existing lectures
     * @param students Vector with all existing students
     */
    Class(const std::string &class_code, const std::set<Lecture> &lectures, const std::set<Student>  &students);

    /**
     * @brief Getter for class_code field
     * @return A string with the class code
     */
    std::string class_code() const;

    /**
     * @brief Prints all lectures in class
     */
    void printLectures() const;

    /**
     * @brief Prints all students enrolled in class
     */
    void printEnrolledStudents() const;

    /**
     * @brief Getter for a given Lecture
     * @param code Code of the lecture
     * @return The Lecture
     */
    Lecture getLecture(const std::string &code) const;

    /**
     * @brief Getter of all lectures
     * @return const reference to all lectures
     */
    const std::set<Lecture> &lectures() const;

    /**
     * @brief Number of enrolled students in class
     * @return size_t with enrolled students
     */
    size_t countEnrolledStudents() const;

    /**
     * @brief Removes student from class
     * @param student student to be removed
     * @return true if student can be removed, false if he cannot
     */
    bool remove_student_from_class(const std::shared_ptr<Student> &student);

    /**
     * Add student to the class. If he already exists, enroll him in the ucs
     * @brief Adds a student to the class
     * @param student student to be added
     * @param uc ucs where he will be enrolled
     * @return true if student not in class, false if he is
     */
    bool add_student_to_class(const std::shared_ptr<Student> &student, const std::list<std::string> &ucs);

    bool operator<(const Class &other) const;
};




#endif //AED_PROJECT_CLASS_H
