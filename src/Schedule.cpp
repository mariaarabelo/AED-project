//
// Created by alexandre on 19-10-2023.
//

#include "Schedule.h"

Schedule::Schedule(const Student &student, const std::vector<Lecture> &lectures) {
    for (const auto &c : student.enrolled_classes()) {
        for (const auto &l : lectures) {
            if (l.uc_code() == c.first && l.class_code() == c.second) {
                lectures_.push_back(l);
            }
        }
    }
}

Schedule::Schedule(const Class &c) {

}

const std::vector<Lecture> &Schedule::get_lectures() const {
    return lectures_;
}