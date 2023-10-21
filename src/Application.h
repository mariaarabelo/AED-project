//
// Created by alexandre on 19-10-2023.
//

#ifndef AED_PROJECT_APPLICATION_H
#define AED_PROJECT_APPLICATION_H

#include <vector>
#include <utility>
#include <list>
#include <algorithm>
#include <memory>
#include <iostream>
#include "Lecture.h"
#include "File_Reader.h"
#include "UC.h"
#include "Student.h"
#include "Schedule.h"


class Application {
public:
    Application();
    ~Application();
    void test();
private:
    std::vector<Lecture> *lectures_;
    std::vector<Student> *students_;
    std::vector<Class> *classes_;
    std::vector<UC> *ucs_;
    std::map<int, std::vector<Student>> yearStudentsMap;
    void instantiateClasses(std::map<std::string, std::list<std::string>> * classes);
    void instantiateUCs(std::map<std::string, std::list<std::string>> * classes);
    void fillYearStudentsMap();
    void printStudentsEnrolledInYear(int year);
    void printStudentsPerYear();
    void printUCsWithEnrolledStudents(int n, bool ascendingOrder);
};


#endif //AED_PROJECT_APPLICATION_H
