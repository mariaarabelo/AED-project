//
// Created by alexandre on 11-10-2023.
//

#include "Lecture.h"

Lecture::Lecture(std::string class_code, std::string uc_code, std::string weekday, std::string start_hour, std::string duration,
                 std::string type) {
    class_code_ =class_code;
    uc_code_ = uc_code;
    weekday_ = weekday;
    start_hour_ = start_hour;
    duration_ = duration;
    type_ = type;
}

void Lecture::printLecture() {
    std::cout << class_code_ << "\n" <<
    uc_code_ << "\n" << weekday_ << "\n" <<
    start_hour_ << "\n" << duration_ << "\n" <<
    type_ << "\n";
}
