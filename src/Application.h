//
// Created by alexandre on 19-10-2023.
//

#ifndef AED_PROJECT_APPLICATION_H
#define AED_PROJECT_APPLICATION_H

#include <vector>
#include "Lecture.h"
#include "File_Reader.h"


class Application {
public:
    Application();
    ~Application();
private:
    std::vector<Lecture> *lectures_;
    std::vector<Student> *students_;
};


#endif //AED_PROJECT_APPLICATION_H
