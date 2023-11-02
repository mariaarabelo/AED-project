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

void Lecture::printLecture() const{
    std::cout << class_code_ << " || " <<
    uc_code_ << "\n " << weekday_ << "\n" << "Starts at " <<
    start_hour_ << " and ends at " << std::stof(start_hour_) + std::stof(duration_) << " (duration of "<< duration_ << "h)\n" <<
    type_ << "\n";
}

const std::string &Lecture::class_code() const{
    return class_code_;
}

const std::string &Lecture::uc_code() const {
    return uc_code_;
}

const std::string &Lecture::weekday() const {
    return weekday_;
}

const std::string &Lecture::start_hour() const {
    return start_hour_;
}

const std::string &Lecture::duration() const {
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
const std::string &Lecture::type() const {
    return type_;
}

bool Lecture::operator<(const Lecture &other) const{
    if (this->uc_code_ == other.uc_code()) return this->class_code_ < other.class_code();
    return this->uc_code_ < other.class_code();
}

bool Lecture::conflicts(const Lecture& other) const {
    // Check if the lectures have the same weekday
    if (weekday_ != other.weekday_)
        return false;

    // Parse start hours and durations as integers (HH:MM format)
    int thisStartHour = std::stoi(start_hour_.substr(0, 2));
    int otherStartHour = std::stoi(other.start_hour_.substr(0, 2));
    int thisStartMinute = std::stoi(start_hour_.substr(3, 2));
    int otherStartMinute = std::stoi(other.start_hour_.substr(3, 2));
    int thisDuration = std::stoi(duration_);
    int otherDuration = std::stoi(other.duration_);

    // Calculate end times
    int thisEndMinute = thisStartMinute + thisDuration;
    int otherEndMinute = otherStartMinute + otherDuration;
    int thisEndHour = thisStartHour + (thisEndMinute / 60);
    int otherEndHour = otherStartHour + (otherEndMinute / 60);
    thisEndMinute %= 60;
    otherEndMinute %= 60;

    // Check for time overlap
    if ((thisStartHour < otherEndHour || (thisStartHour == otherEndHour && thisStartMinute <= otherEndMinute)) &&
        (thisEndHour > otherStartHour || (thisEndHour == otherStartHour && thisEndMinute >= otherStartMinute))) {
        return true;  // Conflict found
    }

    return false;  // No conflict
}
