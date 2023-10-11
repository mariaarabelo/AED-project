//
// Created by alexandre on 11-10-2023.
//

#ifndef AED_PROJECT_LECTURE_H
#define AED_PROJECT_LECTURE_H

#include <string>


class Lecture {
private:
    std::string class_code;
    std::string uc_code;
    std::string weekday;
    std::string start_hour;
    int duration;
    std::string type;
};


#endif //AED_PROJECT_LECTURE_H
