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
    std::vector<std::pair<std::shared_ptr<Student>,std::list<std::string>>> enrolled_students_;
public:

    /**
     * @brief Constructor for Class class
     * @param class_code The code of the class
     * @param lectures Vector with all existing lectures
     * @param students Vector with all existing students
     */
    Class(const std::string &class_code, const std::vector<Lecture> &lectures, const std::vector<Student>  &students);

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
    const Lecture &getLecture(const std::string &code) const;

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
};




#endif //AED_PROJECT_CLASS_H
