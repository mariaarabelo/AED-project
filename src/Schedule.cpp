//
// Created by alexandre on 19-10-2023.
//

#include "Schedule.h"

int getWeekDayNum(std::string weekDay) {
    for (char &c : weekDay) {
        c = (char)tolower(c);
    }

    int dayNumber;

    switch (weekDay[0]) {
        case 'm':
            dayNumber = 1; // Monday
            break;
        case 't':
            if (weekDay == "tuesday") {
                dayNumber = 2; // Tuesday
            } else if (weekDay == "thursday") {
                dayNumber = 4; // Thursday
            }
            break;
        case 'w':
            dayNumber = 3; // Wednesday
            break;
        case 'f':
            dayNumber = 5; // Friday
            break;
        case 's':
            if (weekDay == "saturday") {
                dayNumber = 6; // Saturday
            } else if (weekDay == "sunday") {
                dayNumber = 7; // Sunday
            }
            break;
        default:
            dayNumber = 0; // Invalid day
    }

    return dayNumber;
}

bool compareLecture(const Lecture &a, const Lecture &b) {
    if (getWeekDayNum(a.weekday()) < getWeekDayNum(b.weekday()) ||
        (getWeekDayNum(a.weekday()) == getWeekDayNum(b.weekday()) &&
         a.start_hour() > b.start_hour())) {
        return true;
    }
    return false;
}

Schedule::Schedule(const Student &student, const std::set<Lecture> &lectures) {
    for (const auto &c : student.enrolled_classes()) {
        for (const  auto &l : lectures) {
            if (l.uc_code() == c.first && l.class_code() == c.second) {
                lectures_.insert(l);
            }
        }
    }
}

Schedule::Schedule(const Class &c) {
    this->lectures_ = c.lectures();
}

const std::set<Lecture> &Schedule::get_lectures() const {
    return lectures_;
}

void Schedule::printSchedule() const {
    std::cout << "Printing schedule..." << "\n";
    for (const auto &lec : lectures_) {
        lec.printLecture();
    }
}

Schedule::Schedule(const UC &uc) {
    for (const auto &c : uc.classes()) {
        lectures_.insert(c->getLecture(uc.uc_code()));
    }
}

bool Schedule::conflicts(const Lecture &lecture) {
    for (const auto &l : lectures_) {
        if (lecture.conflicts(l)) return true;
    }
    return false;
}


//TODO: reimplement this constructor
/*
Schedule::Schedule(const UC &uc) {
    for (const auto &c : *uc.classes()) {
        lectures_.push_back(c.getLecture(uc.uc_code()));
    }
}*/
