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

class Schedule {
private:
    std::vector<Lecture> lectures_;
public:
    Schedule(const Student &student, const std::vector<Lecture> &lectures);
    explicit Schedule(const Class &c);
    //explicit Schedule(const UC &uc);
    const std::vector<Lecture> &get_lectures() const;
    void printSchedule() const;

};


#endif //AED_PROJECT_SCHEDULE_H
