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

void Lecture::printLecture() const{
    std::cout << class_code_ << "\n" <<
    uc_code_ << "\n" << weekday_ << "\n" <<
    start_hour_ << "\n" << duration_ << "\n" <<
    type_ << "\n";
}

std::string Lecture::class_code() const{
    return class_code_;
}

std::string Lecture::uc_code() const {
    return uc_code_;
}

std::string Lecture::weekday() const {
    return weekday_;
}

std::string Lecture::start_hour() const {
    return start_hour_;
}

std::string Lecture::duration() const {
    return duration_;
}

std::string Lecture::type() const {
    return type_;
}
