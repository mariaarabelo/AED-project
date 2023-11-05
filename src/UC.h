//
// Created by alexandre on 10-10-2023.
//

#ifndef AED_PROJECT_UC_H
#define AED_PROJECT_UC_H

#include <string>
#include <vector>
#include <list>
#include <memory>
#include "Class.h"
#include "Student.h"

class UC {
private:
    std::string uc_code_;
    std::list<std::shared_ptr<Class>> classes_;
    std::list<Student> enrolled_students_;
public:

    /**
     * @brief Constructor for UC class
     * This function instantiates an UC
     * @param uc_code the code for the uc
     * @param classes a list of classes in UC
     * @param enrolled_students a list of students enrolled in the UC
     */
    UC(const std::string &uc_code, const std::list<std::shared_ptr<Class>> &classes,
       const std::list<Student> &enrolled_students);

    /**
     * @brief Getter for classes field
     * @return a const reference to the classes field
     */
    const std::list<std::shared_ptr<Class>> &classes() const;

    /**
     * @brief Removes a class from UC
     * @param c a pointer to the class to be removed
     */
    void removeClass(const std::shared_ptr<Class> &c);

    /**
     * @brief Prints classes in UC
     */
    void printClasses();

    /**
     * @brief Getter for enrolled_students field
     * @return const reference to enrolled students field
     */
    const std::list<Student> &enrolled_students() const;

    /**
     * @brief Getter for the UC code
     * @return
     */
    std::string uc_code() const;

    /**
     * @brief Number of students enrolled in UC
     * @return unsigned int of number of students
     */
    unsigned countEnrolledStudents() const;

    bool enroll_student(const Student &student);

    bool remove_student(const Student &student);
};


#endif //AED_PROJECT_UC_H
