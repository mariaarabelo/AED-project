//
// Created by alexandre on 11-10-2023.
//

#ifndef AED_PROJECT_LECTURE_H
#define AED_PROJECT_LECTURE_H

#include <string>
#include <iostream>
/**
 * @brief class for a Lecture
 */
class Lecture {
private:
    std::string class_code_;
    std::string uc_code_;
    std::string weekday_;
    std::string start_hour_;
    std::string duration_;
    std::string type_;
public:
    Lecture(const std::string &class_code, const std::string &uc_code, const std::string &weekday,
            const std::string &start_hour, const std::string &duration,
            const std::string &type);
    const std::string &class_code() const;
    const std::string &uc_code() const;
    std::string weekday() const;
    std::string start_hour() const;
    std::string duration() const;
    std::string type() const;
    std::string end_hour() const;
    bool operator<(const Lecture &other) const;
    bool conflicts(const Lecture& other) const;
};


#endif //AED_PROJECT_LECTURE_H
