//
// Created by alexandre on 19-10-2023.
//

#ifndef AED_PROJECT_SCHEDULE_H
#define AED_PROJECT_SCHEDULE_H

#include <list>
#include <iostream>
#include <algorithm>
#include "Class.h"
#include "Student.h"
#include "Lecture.h"
#include "UC.h"

/**
 * @brief The class do define a Schedule
 */
class Schedule {
private:
    std::vector<Lecture> lectures_;
public:

    /**
     * @brief Constructor for Schedule class
     * This function instantiates a Schedule for a Student
     * @param student
     * @param lectures Vector of all lectures
     */
    Schedule(const Student &student, const std::vector<Lecture> &lectures);

    /**
     * @brief Constructor for Schedule class
     * This function instantiates a Schedule for a Class
     * @param c
     */
    explicit Schedule(const Class &c);

    /**
     * @brief Constructor for Schedule class
     * This function instantiates a Schedule for a UC
     * @param uc
     */
    explicit Schedule(const UC &uc);

    /**
     * @brief Getter for lectures field
     * @return const reference to lectures field
     */
    const std::vector<Lecture> &get_lectures() const;

    /**
     * @brief Check if there are conflicts with a lecture in the schedule
     * @param lecture the lecture
     * @return true if there is conflict, false if there is not
     */
    bool conflicts(const Lecture &lecture);

};


#endif //AED_PROJECT_SCHEDULE_H
