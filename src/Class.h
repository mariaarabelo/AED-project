//
// Created by alexandre on 10-10-2023.
//

#ifndef AED_PROJECT_CLASS_H
#define AED_PROJECT_CLASS_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <list>
#include "Lecture.h"
#include "Student.h"

class Class {
private:
    std::string class_code_;
    std::vector<Lecture> lectures_;
    std::vector<std::pair<std::string, std::list<Student>>> enrolled_students_;
    std::list<std::pair<std::string, int>> student_count_;
public:

    /**
     * @brief Constructor for Class class
     * @param class_code The code of the class
     * @param lectures Vector with all existing lectures
     * @param students Vector with all existing students
     */
    Class(const std::string &class_code, const std::vector<Lecture> &lectures, const std::set<Student>  &students);

    /**
     * @brief Getter for class_code field
     * @return A string with the class code
     */
    std::string class_code() const;

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
    const std::vector<Lecture> &lectures() const;

    /**
     * @brief Number of enrolled students in class
     * @return size_t with enrolled students
     */
    size_t countEnrolledStudents() const;

    std::vector<std::pair<std::string, std::string>> getEnrolledStudents() const;

    /**
     * @brief Removes student from class
     * @param student student to be removed
     * @return true if student can be removed, false if he cannot
     */
    bool remove_student_from_class(const Student &student, const std::string &uc);

    /**
     * Add student to the class. If he already exists, enroll him in the ucs
     * @brief Adds a student to the class
     * @param student student to be added
     * @param uc ucs where he will be enrolled
     * @return true if student not in class, false if he is
     */
    bool add_student_to_class(const Student &student, const std::string &uc);

    bool operator<(const Class &other) const;

    /**
     * @brief Get number of students in an UC
     * @param uc
     * @return student count in UC
     */
    int get_student_count(const std::string &uc) const;
};




#endif //AED_PROJECT_CLASS_H
