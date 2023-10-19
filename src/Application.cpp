//
// Created by alexandre on 19-10-2023.
//

#include "Application.h"

Application::Application() {
    //instantiate lectures
    File_Reader f1("../dataset/classes.csv");
    lectures_ = new std::vector<Lecture>;
    f1.instatiateLectures(lectures_);

    //instantiate students
    File_Reader f2("../dataset/students_classes.csv");
    students_ = new std::vector<Student>;
    f2.instantiateStudents(students_);
}

Application::~Application() {
    delete lectures_;
    delete students_;
}
