//
// Created by alexandre on 11-10-2023.
//

#ifndef AED_PROJECT_LECTURE_H
#define AED_PROJECT_LECTURE_H

#include <string>
#include <iostream>

class Lecture {
private:
    std::string class_code_;
    std::string uc_code_;
    std::string weekday_;
    std::string start_hour_;
    std::string duration_;
    std::string type_;
public:
    Lecture(std::string class_code, std::string uc_code, std::string weekday, std::string start_hour, std::string duration,
            std::string type);
    Lecture(const Lecture &l);
    void printLecture() const;
    std::string class_code() const;
    std::string uc_code() const;
    std::string weekday() const;
    std::string start_hour() const;
    std::string duration() const;
    std::string type() const;
};


#endif //AED_PROJECT_LECTURE_H
