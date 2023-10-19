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

    //instantiate classes and ucs
    classes_ = new std::vector<Class>;
    ucs_ = new std::vector<UC>;
    auto *classes = new std::map<std::string, std::list<std::string>>;
    File_Reader f("../dataset/classes_per_uc.csv");
    f.classListing(classes);
    instantiateClasses(classes);
    instantiateUCs(classes);
    delete classes;
}

Application::~Application() {
    delete lectures_;
    delete students_;
    delete classes_;
    delete ucs_;
}

void Application::instantiateClasses(std::map<std::string, std::list<std::string>> * classes) {
    std::list<std::string> allClassCodes;

    for (const auto &p : *classes) {
        for (const auto &c : p.second) {
            auto it = std::find(allClassCodes.begin(), allClassCodes.end(), c);
            if (it == allClassCodes.end()) {
                allClassCodes.push_back(c);
            }
        }

    }

    for (const auto &classCode : allClassCodes) {
        Class c(classCode, lectures_);
        classes_->push_back(c);
    }
}

void Application::instantiateUCs(std::map<std::string, std::list<std::string>> *classes) {
    for (const auto &p : *classes) {
        std::list<Class *> classPtrs;
        for (auto &a : *classes_) {
            auto it = std::find(p.second.begin(), p.second.end(), a.class_code());
            if (it != p.second.end()) {
                classPtrs.push_back(&a);
            }
        }
        UC u(p.first, classPtrs);
    }
}

void Application::test() {
    UC *u = &ucs_->at(0);
    u->printClasses();
}
