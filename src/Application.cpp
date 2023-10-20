//
// Created by alexandre on 19-10-2023.
//

#include "Application.h"

Application::Application() {
    //instantiate lectures
    File_Reader f1("../dataset/classes.csv");
    lectures_ = new std::vector<Lecture>;
    *lectures_ = f1.instatiateLectures();

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
    delete ucs_;
    delete classes_;
    delete students_;
    delete lectures_;
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
    //PROBLEM HAPPENS WITH THIS FOR LOOP
    for (const auto &classCode : allClassCodes) {
        classes_->emplace_back(classCode, *lectures_);
    }
}

void Application::instantiateUCs(std::map<std::string, std::list<std::string>> *classes) {
    for (const auto &p : *classes) {
        std::list<std::shared_ptr<Class>> classPtrs;
        for (auto &a : *classes_) {
            auto it = std::find(p.second.begin(), p.second.end(), a.class_code());
            if (it != p.second.end()) {
                classPtrs.push_back(std::make_shared<Class>(a));
            }
        }
        std::list<std::shared_ptr<Student>> studs;
        for (const auto &s : *students_) {
            for (const auto  &c : s.enrolled_classes()) {
                if  (c.first == p.first &&
                std::find(p.second.begin(), p.second.end(), c.second) != p.second.end()) {
                    studs.push_back(std::make_shared<Student>(s));
                }
            }
        }
        UC u(p.first, classPtrs, studs);
        ucs_->push_back(u);
    }
}

void Application::test() {
    UC *u = &ucs_->at(1);
    Schedule s(*u);
    s.printSchedule();
}
