//
// Created by alexandre on 19-10-2023.
//

#include "Application.h"

Application::Application() {
    //instantiate lectures
    File_Reader f1("../dataset/classes.csv");
    lectures_ = new std::set<Lecture>;
    for (const auto &a : f1.instatiateLectures()) {
        lectures_->insert(a);
    }
    //instantiate students
    File_Reader f2("../dataset/students_classes.csv");
    students_ = new std::set<Student>;
    f2.instantiateStudents(students_);

    //instantiate classes and ucs
    classes_ = new std::set<Class>;
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

    for (const auto &classCode : allClassCodes) {
        Class c(classCode, *lectures_, *students_);
        classes_->insert(c);
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
        std::list<Student> studs;
        for (const auto &s : *students_) {
            for (const auto  &c : s.enrolled_classes()) {
                if  (c.first == p.first &&
                std::find(p.second.begin(), p.second.end(), c.second) != p.second.end()) {
                    studs.push_back(s);
                }
            }
        }
        UC u(p.first, classPtrs, studs);
        ucs_->push_back(u);
    }
}

void Application::printStudentsEnrolledInYear(const int &year) {
    if (yearStudentsMap.find(year) != yearStudentsMap.end()) {
        std::vector<Student>& studentsInYear = yearStudentsMap[year];
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
            int year = std::stoi(c.second.substr(0, 1));
            auto it = std::find(yearStudentsMap[year].begin(), yearStudentsMap[year].end(), s);
            if (it == yearStudentsMap[year].end())
                yearStudentsMap[year].push_back(s);
        }
    }
}

UC Application::getUC(const std::string &uc_code) const {
    for (const auto &uc : *ucs_) {
        if (uc.uc_code() == uc_code) return uc;
    }
}

void Application::printStudentsPerYear(bool ascendingOrder){
    // store number of students in each year
    std::vector<std::pair<int, int>> yearEnrollments;
    for (const auto &entry : yearStudentsMap){
        yearEnrollments.push_back(std::make_pair(entry.first, entry.second.size()));
    }
    //sort in specified order
    std::sort(yearEnrollments.begin(), yearEnrollments.end(), [ascendingOrder](const auto &a, const auto &b){
        if (ascendingOrder) {
            return a.second < b.second;
        } else {
            return a.second > b.second;
        }
    });
    //show year's number of students
    for (const auto &entry: yearEnrollments){
        std::cout << "Year " << entry.first << " - " << entry.second << " students" << std::endl;
    };
}

void Application::printUCsWithEnrolledStudents(int n, bool ascendingOrder){
    // store number of students in each UC
    std::vector<std::pair<std::string, int>> ucEnrollments;

    for (const UC &uc: *ucs_){
        int numStudents = uc.enrolled_students().size();
        ucEnrollments.push_back(std::make_pair(uc.uc_code(), numStudents));
    }

    //sort in specified order
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

void Application::printUcClassesStudents(const std::string &uc_code, const int &n_classes, bool ascendingOrder){
    UC uc = getUC(uc_code);

    // store number of students in each class
    std::vector<std::pair<std::string, int>> classEnrollments;

    for (const std::shared_ptr<Class> &classPtr: uc.classes()){
        int numStudents = classPtr->countEnrolledStudents();
        classEnrollments.push_back(std::make_pair(classPtr->class_code(), numStudents));
    }

    //sort in specified order
    std::sort(classEnrollments.begin(), classEnrollments.end(), [ascendingOrder](const auto &a, const auto &b){
        if (ascendingOrder) {
            return a.second < b.second;
        } else {
            return a.second > b.second;
        }
    });

    std::cout << "Showing number of students for classes of UC "<< uc_code << std::endl;

    //show results for n Classes
    for (int i=0; i < n_classes && i<classEnrollments.size(); i++){
        std::cout << i+1 << ". " << classEnrollments[i].first << " - " << classEnrollments[i].second << " students" << std::endl;
    };
}

void Application::test() {
    printUcClassesStudents("L.EIC001", 30, 0);
    printUcClassesStudents("L.EIC001", 3, 1);
    printUcClassesStudents("L.EIC002", 15, 1);
}

const std::set<Student> &Application::students() {
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

std::string Application::add_student_to_uc(const std::string &student_code, const std::string &uc, const std::string &c) {
    auto class_it = std::find_if(classes_->begin(), classes_->end(), [c](const Class &obj) {
        return obj.class_code() == c;
    });
    if (class_it ==classes_->end()) return "Class Not Found";
    Class c_to_modify = *class_it;
    classes_->erase(class_it);

    auto uc_it = std::find_if(ucs_->begin(), ucs_->end(), [uc](const UC &obj) {
        return obj.uc_code() == uc;
    });
    if (uc_it == ucs_->end()) return "UC Not Found";
    UC uc_to_modify = *uc_it;
    ucs_->erase(uc_it);

    auto student_it = std::find_if(students_->begin(), students_->end(), [student_code](const Student &obj) {
        return student_code == obj.student_code();
    });
    if (student_it == students_->end()) return "Student Not Found";
    Student student_to_modify = *student_it;
    students_->erase(student_it);

    Lecture lecture = c_to_modify.getLecture(uc);

    if (student_to_modify.enrollInUC(std::make_pair(uc, c))) {
        if (will_classes_be_balanced(uc, c)) {
            if (!schedule_is_conflicting(student_to_modify, lecture)) {
                if(c_to_modify.add_student_to_class(student_to_modify, uc)) {
                    if (uc_to_modify.enroll_student(student_to_modify)) {
                        students_->insert(student_to_modify);
                        classes_->insert(c_to_modify);
                        ucs_->push_back(uc_to_modify);
                    } else return "Student already in UC";
                } else return "Student already in class";

            } else return "There is a schedule conflict.";

        }  else return "Class will not be balanced.";

    } else return "Student is in too many UCs";

}

bool Application::will_classes_be_balanced(const std::string &uc, const std::string &c) const {
    std::vector<int> counts;
    for (const auto &cc : *classes_) {
        if (cc.class_code() == c) {
            counts.push_back(cc.get_student_count(uc)+1);
        } else
        counts.push_back(cc.get_student_count(uc));
    }
    for (std::size_t i = 0; i < counts.size(); ++i) {
        for (std::size_t j = 0; j < counts.size(); ++j) {
            if (i != j && std::abs(counts[i] - counts[j]) > 4) {
                return false; // A number differs from others by more than 4 units
            }
        }
    }
    return true;
}

bool Application::schedule_is_conflicting(const Student &student, const Lecture &lecture) const {
    Schedule schedule(student, *lectures_);
    return schedule.conflicts(lecture);
}
