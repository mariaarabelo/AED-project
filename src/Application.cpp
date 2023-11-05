//
// Created by alexandre on 19-10-2023.
//

#include "Application.h"

extern int CAP;

void write_to_students_file(const std::string &line) {
    std::ofstream file;
    file.open("../dataset/students_classes.csv", std::ios::app);
    file << line << std::endl;
    file.close();
}

void log_changes(const std::string &line) {
    std::ofstream file;
    file.open("../dataset/changes.csv", std::ios::app);
    file << line << std::endl;
    file.close();
}

void remove_line_from_file(const std::string& lineToRemove, const std::string &file_name="../dataset/students_classes.csv") {
    std::ifstream inputFile(file_name);

    std::stringstream updatedContent;
    std::string line;

    while (std::getline(inputFile, line)) {
        if (line != lineToRemove) {
            updatedContent << line << std::endl;
        }
    }

    inputFile.close();

    std::ofstream outputFile(file_name);


    outputFile << updatedContent.str();
    outputFile.close();
}

Application::Application() {
    //instantiate lectures
    File_Reader f1("../dataset/classes.csv");
    lectures_ = new std::vector<Lecture>;
    *lectures_ = f1.instatiateLectures();

    //instantiate students
    File_Reader f2("../dataset/students_classes.csv");
    students_ = new std::set<Student>;
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

UC Application::getUC(const std::string &uc_code) const {
    for (const auto &uc : *ucs_) {
        if (uc.uc_code() == uc_code) return uc;
    }
}

void Application::printUCsWithEnrolledStudents(int n, bool ascendingOrder){
    // store number of students in each UC
    std::vector<std::pair<std::string, int>> ucEnrollments;

    for (const UC &uc: *ucs_){
        int numStudents = uc.enrolled_students().size();
        ucEnrollments.emplace_back(uc.uc_code(), numStudents);
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

const std::set<Student> &Application::students() {
    return *students_;
}

const std::vector<Lecture> &Application::lectures() {
    return *lectures_;
}

std::vector<std::string> Application::class_codes(){
    std::vector<std::string> v;
    for (const Class& c : *classes_){
        v.emplace_back(c.class_code());
    }
    return v;
}

const std::vector<std::pair<std::string, std::string>> &Application::Students_name_id(){
    std::vector<std::pair<std::string, std::string>> v;
    for (const auto &s : *students_){
        std::pair<std::string, std::string> p = {s.student_name(), s.student_code()};
        v.emplace_back(p);
    }
    return v;
}

std::vector<std::pair<std::string, std::string>> Application::students_name_id() {
    std::vector<std::pair<std::string, std::string>> v;
    for (const auto& s : *students_) {
        std::pair<std::string, std::string> p = {s.student_name(), s.student_code()};
        v.emplace_back(p);
    }
    return v;
}

std::vector<std::string> Application::ucs_codes(){
    std::vector<std::string> v;
    for (const UC& c : *ucs_){
        v.emplace_back(c.uc_code());
    }
    return v;
}

std::vector<std::pair<std::string, std::string>> Application::students_from_uc(const std::string& uc_code){
    std::vector<std::pair<std::string, std::string>> vector;
    for (const UC& UC : *ucs_){
        if ((UC.uc_code()) == uc_code){
            for (const Student& s : UC.enrolled_students()){
                vector.emplace_back(s.student_name(), s.student_code());
            }
            return vector;
        }
    }
}

std::vector<std::pair<std::string, std::string>> Application::enrolled_students_in_ucs() {
    std::vector<std::pair<std::string, std::string>> ucEnrollments;
    for (const UC &uc: *ucs_) {
        int numStudents = uc.enrolled_students().size();
        ucEnrollments.emplace_back(uc.uc_code(), std::to_string(numStudents));
    }
    return ucEnrollments;
}


std::vector<std::string> Application::classes_from_uc(const std::string& uc_code){
    std::vector<std::string> vector;
    for (const UC& UC : *ucs_) {
        if ((UC.uc_code()) == uc_code) {
            for (const std::shared_ptr<Class> &c: UC.classes()) {
                vector.emplace_back(c->class_code());
            }
            return vector;
        }
    }
}

bool Application::will_classes_be_balanced(const std::string &uc, const std::string &c) const {
    std::vector<int> counts;
    for (const auto &cc : *classes_) {
        if (cc.class_code() == c) {
            if (cc.get_student_count(uc) != -1) {
                if (cc.get_student_count(uc) + 1 > CAP) return false;
                counts.push_back(cc.get_student_count(uc) + 1);
            }
        } else {
            if (cc.get_student_count(uc) != -1) {
                counts.push_back(cc.get_student_count(uc));
            }
        }
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

std::string Application::students_class_from_uc(const std::string& uc_code, const Student& student){
    std::vector<std::string> vector = classes_from_uc(uc_code);
    for (std::string s1 : vector){
        for (const std::string& s2 : student.enrolled_classes_id()){
            if (s1 == s2){
                return s1;
            }
        }
    }

}

bool Application::schedule_is_conflicting(const Student &student, const Lecture &lecture) const {
    Schedule schedule(student, *lectures_);
    return schedule.conflicts(lecture);
}

std::vector<std::pair<std::string, std::string>> Application::class_id_student_number(){
    std::vector<std::pair<std::string, std::string>> v;
    for (const Class& c : *classes_){
        v.emplace_back(c.class_code(), std::to_string(c.countEnrolledStudents()));
    }
    return v;
}


std::string Application::add_student_to_uc(const std::string &student_code, const std::string &uc, const std::string &c,
                                           const bool &no_write) {
    auto class_it = std::find_if(classes_->begin(), classes_->end(), [c](const Class &obj) {
        return obj.class_code() == c;
    });
    if (class_it == classes_->end()) return "Class Not Found";
    Class c_to_modify = *class_it;

    auto uc_it = std::find_if(ucs_->begin(), ucs_->end(), [uc](const UC &obj) {
        return obj.uc_code() == uc;
    });
    if (uc_it == ucs_->end()) return "UC Not Found";
    UC uc_to_modify = *uc_it;

    auto student_it = std::find_if(students_->begin(), students_->end(), [student_code](const Student &obj) {
        return student_code == obj.student_code();
    });
    if (student_it == students_->end()) return "Student Not Found";
    Student student_to_modify = *student_it;

    Lecture lecture = c_to_modify.getLecture(uc);

    if (!schedule_is_conflicting(student_to_modify, lecture)) {
        if (will_classes_be_balanced(uc, c)) {
            if (student_to_modify.enrollInUC(std::make_pair(uc, c))) {
                if (c_to_modify.add_student_to_class(student_to_modify, uc)) {
                    if (uc_to_modify.enroll_student(student_to_modify)) {
                        classes_->erase(class_it);
                        ucs_->erase(uc_it);
                        students_->erase(student_it);
                        students_->insert(student_to_modify);
                        classes_->push_back(c_to_modify);
                        ucs_->push_back(uc_to_modify);
                        std::ostringstream oss;
                        oss << student_to_modify.student_code() << "," << student_to_modify.student_name()
                            << "," <<
                            uc << "," << c_to_modify.class_code();
                        std::string s = oss.str();
                        write_to_students_file(s);
                        if (!no_write) {
                            std::ostringstream oss2;
                            oss2 << "ADDTOUC," << student_to_modify.student_code() << ","
                                 << student_to_modify.student_name() << "," <<
                                 uc << "," << c_to_modify.class_code();
                            s = oss2.str();
                            log_changes(s);
                        }
                        return "Sucess";
                    } else return "Student already in UC";
                } else return "Student already in class";

            } else return "Student is in too many UCs";

        } else return "Class will not be balanced.";

    } else return "There is a schedule conflict";
}

std::string
Application::remove_student_from_uc(const std::string &student_code, const std::string &uc, const std::string &c,
                                    const bool &no_write) {
    auto class_it = std::find_if(classes_->begin(), classes_->end(), [c](const Class &obj) {
        return obj.class_code() == c;
    });
    if (class_it ==classes_->end()) return "Class Not Found";
    Class c_to_modify = *class_it;

    auto uc_it = std::find_if(ucs_->begin(), ucs_->end(), [uc](const UC &obj) {
        return obj.uc_code() == uc;
    });
    if (uc_it == ucs_->end()) return "UC Not Found";
    UC uc_to_modify = *uc_it;

    auto student_it = std::find_if(students_->begin(), students_->end(), [student_code](const Student &obj) {
        return student_code == obj.student_code();
    });
    if (student_it == students_->end()) return "Student Not Found";
    Student student_to_modify = *student_it;

    if (c_to_modify.remove_student_from_class(student_to_modify, uc)) {
        if (uc_to_modify.remove_student(student_to_modify)) {
            if (student_to_modify.removeFromUC(uc)) {
                classes_->erase(class_it);
                ucs_->erase(uc_it);
                students_->erase(student_it);
                students_->insert(student_to_modify);
                classes_->push_back(c_to_modify);
                ucs_->push_back(uc_to_modify);
                std::ostringstream oss;
                oss << student_to_modify.student_code() << "," << student_to_modify.student_name() << "," <<
                    uc << "," << c_to_modify.class_code();
                std::string s = oss.str();
                remove_line_from_file(s);
                if (!no_write) {
                    std::ostringstream oss2;
                    oss2 << "REMOVEFROMUC," << student_to_modify.student_code() << ","
                         << student_to_modify.student_name() << "," <<
                         uc << "," << c_to_modify.class_code();
                    s = oss2.str();
                    log_changes(s);
                }
                return "Sucess";
            } else  return "Student not enrolled";
        } else return "Student not in UC";
    } else return "Student not in class";
}

std::string
Application::switch_student_class(const std::string &student_code, const std::string &uc, const std::string &old_class,
                                  const std::string &new_class, const bool &no_write) {
    std::string s = remove_student_from_uc(student_code, uc, old_class, true);
    if (s == "Sucess") {
        std::string ss = add_student_to_uc(student_code, uc, new_class, true);
        if (ss == "Sucess" && !no_write) {
            std::ostringstream oss;
            oss << "SWITCH" << "," << student_code << "," << uc << "," << old_class << "," << new_class;
            std::string s = oss.str();
            log_changes(s);
        }
        return ss;
    } else return s;
}

std::string Application::reverse_change() {
    File_Reader f("../dataset/changes.csv");
    changes_ = f.read_changes();
    std::string s = "NULL";
    if (!changes_.empty()) {
        std::string line_to_remove;
        for (const auto &a: changes_.top()) {
            line_to_remove += a;
            line_to_remove.push_back(',');
        }
        line_to_remove.pop_back();
        remove_line_from_file(line_to_remove, "../dataset/changes.csv");
        if (changes_.top().at(0) == "SWITCH") {
            s = switch_student_class(changes_.top().at(1), changes_.top().at(2), changes_.top().at(4),
                                     changes_.top().at(3), true);
        } else if (changes_.top().at(0) == "ADDTOUC") {
            s = remove_student_from_uc(changes_.top().at(1), changes_.top().at(3), changes_.top().at(4), true);
        } else if (changes_.top().at(0) == "REMOVEFROMUC") {
            s = add_student_to_uc(changes_.top().at(1), changes_.top().at(3), changes_.top().at(4), true);
        }
        changes_.pop();
    }
    return s;
}

std::vector<std::string> Application::get_latest_change() {
    File_Reader f("../dataset/changes.csv");
    changes_ = f.read_changes();
    if (changes_.empty()) return {"No changes"};
    return changes_.top();
}

std::vector<std::pair<std::string, std::string>> Application::check_year(const std::string& c){
    std::vector<std::pair<std::string, std::string>> v;
    for (const Student& s : *students_){
        for (const std::string& str : s.enrolled_classes_id()){
            std::pair<std::string, std::string> p = {s.student_name(), s.student_code()};
            if (str.substr(0,1) == c && find(v.begin(), v.end(), p) == v.end()){

                v.emplace_back(p);
            }
        }
    }
    return v;
}

std::vector<std::pair<std::string, std::string>> Application::students_in_n_ucs(int n) {
    std::vector<std::pair<std::string, std::string>> res;
    for (const auto &s : *students_) {
        if (s.enrolled_classes().size() >= n) {
            res.emplace_back(s.student_code(), s.student_name());
        }
    }
    return res;
}
