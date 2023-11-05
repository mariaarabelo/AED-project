//
// Created by alexandre on 11-10-2023.
//

#include "Lecture.h"

Lecture::Lecture(const std::string &class_code, const  std::string &uc_code, const std::string &weekday,
                 const std::string &start_hour, const std::string &duration, const std::string &type) {
    class_code_ =class_code;
    uc_code_ = uc_code;
    weekday_ = weekday;
    start_hour_ = start_hour;
    duration_ = duration;
    type_ = type;
}

const std::string &Lecture::class_code() const{
    return class_code_;
}

const std::string &Lecture::uc_code() const {
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

std::string Lecture::end_hour() const {
    std::string s = std::to_string(std::stof(start_hour_) + std::stof(duration_));
    int idx = 0;
    for (char c : s){
        idx ++;
        if (c == '.'){
            break;
        }
    }
    s = s.substr(0, idx + 1);
    if (s[s.size() - 1] == '0'){
        s = s.substr(0, s.size() - 2);
    }
    return s;
}

std::string Lecture::type() const {
    return type_;
}

bool Lecture::operator<(const Lecture &other) const{
    if (this->uc_code_ == other.uc_code()) return this->class_code_ < other.class_code();
    return this->uc_code_ < other.class_code();
}

bool Lecture::conflicts(const Lecture &other) const {
    // Convert the start hours and durations to double values for comparison
    double this_start_hour = std::stod(start_hour_);
    double this_duration = std::stod(duration_);
    double other_start_hour = std::stod(other.start_hour_);
    double other_duration = std::stod(other.duration_);

    // Check if the lectures have the same weekday
    if (weekday_ == other.weekday_) {
        // Check if there is an overlap in time
        if ((this_start_hour >= other_start_hour && this_start_hour < other_start_hour + other_duration) ||
            (other_start_hour >= this_start_hour && other_start_hour < this_start_hour + this_duration)) {
            return true;  // Conflicts
        }
    }

    return false;  // No conflicts
}
