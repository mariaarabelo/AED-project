//
// Created by alexandre on 09-10-2023.
//

#include <iostream>
#include "File_Reader.h"
#include "Class.h"
#include "Student.h"
#include "Schedule.h"
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
    File_Reader f1("../dataset/classes.csv");
    std::vector<Lecture> l = f1.instatiateLectures();
    File_Reader f2("../dataset/students_classes.csv");
    std::vector<Student> students = f2.instantiateStudents();
    std::cout << students.at(0).student_name() << "\n";
    Schedule s(students.at(0), l);
    s.get_lectures().at(0).printLecture();
    return 0;
}