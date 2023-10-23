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
    fillYearStudentsMap();
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
        classes_->emplace_back(classCode, *lectures_, *students_);
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

void Application::printStudentsEnrolledInYear(const int &year) {
    if (yearStudentsMap.find(year) != yearStudentsMap.end()) {
        std::vector<Student> studentsInYear = yearStudentsMap[year];
        std::cout << "Students enrolled in year " << year << ":" << std::endl;

        //print all students of that year
        for (const Student& student : studentsInYear) {
            student.printStudent();
        }

    } else {
        std::cout << "Year not registered " << year << std::endl;
    }
}


unsigned Application::countStudentsEnrolledInYear(const int &year) {
    unsigned count = 0;
    for (const auto &s : *students_) {
        for (const auto &c : s.enrolled_classes()) {
            std::string y = c.second.substr(0,1);
            if (std::stoi(y) == year) {
                count++;
                break;
            }
        }
    }
    return count;
}

void Application::fillYearStudentsMap() {
    for (const auto &s: *students_) {
        for (const auto &c: s.enrolled_classes()) {
            std::string y = c.second.substr(0, 1);
            int year = std::stoi(y);
            auto it = std::find(yearStudentsMap[year].begin(), yearStudentsMap[year].end(), s);
            if (it == yearStudentsMap[year].end())
                yearStudentsMap[year].push_back(s);
        }
    }
}

void Application::printStudentsPerYear(){
    for (const auto &entry : yearStudentsMap){
        std::cout << "Year " << entry.first << ": " << entry.second.size() << " students" << std::endl;
    }
}

void Application::printUCsWithEnrolledStudents(int n, bool ascendingOrder){
    // store number of students in each UC
    std::vector<std::pair<std::string, int>> ucEnrollments;

    for (const UC &uc: *ucs_){
        int numStudents = uc.enrolled_students().size();
        ucEnrollments.push_back(std::make_pair(uc.uc_code(), numStudents));
    }

    //sort in decreasing order
    std::sort(ucEnrollments.begin(), ucEnrollments.end(), [ascendingOrder](const auto &a, const auto &b){
        if (ascendingOrder) {
            return a.second < b.second;
        } else {
            return a.second > b.second;
        }
    });

    //show results for n UCs
    for (int i=0; i < n && i<ucEnrollments.size(); i++){
        std::cout << i+1 << ". " << ucEnrollments[i].first << " - " << ucEnrollments[i].second << " students" << std::endl;
    };
}

void Application::test() {
    printStudentsEnrolledInYear(0);
    printStudentsEnrolledInYear(-1);
    printStudentsEnrolledInYear(4);
    printStudentsPerYear();
    printUCsWithEnrolledStudents(10, 0);
    printUCsWithEnrolledStudents(10, 1);
}

const std::vector<Student> &Application::students() {
    return *students_;
}

const std::vector<std::pair<std::string, std::string>> &Application::Students_name_id(){
    std::vector<std::pair<std::string, std::string>> v;
    for (const auto &s : *students_){
        std::pair<std::string, std::string> p = {s.student_name(), s.student_code()};
        v.emplace_back(p);
    }
    return v;
}
