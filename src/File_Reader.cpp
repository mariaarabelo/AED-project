//
// Created by alexandre on 11-10-2023.
//

#include <map>
#include "File_Reader.h"

File_Reader::File_Reader(const std::string &file_name) {
    file_.open(file_name);
}

std::vector<Lecture> File_Reader::instatiateLectures() {
    //TODO
    //need to improve the error thrown
    std::vector<Lecture> lectures;
    if (!file_.is_open()) throw std::runtime_error("File does not exist");
    std::string line;
    std::getline(file_, line);
    while(std::getline(file_, line)) {
        std::istringstream iss(line);
        std::string value;
        std::vector<std::string> v;
        while (std::getline(iss, value, ',')) {
            v.push_back(value);
        }
        Lecture l(v.at(0), v.at(1), v.at(2),v.at(3),
                  v.at(4), v.at(5));
        lectures.push_back(l);
    }
    file_.close();
    return lectures;
}

void File_Reader::instantiateStudents(std::set<Student> *students) {
    if (!file_.is_open()) throw std::runtime_error("File does not exist");
    std::string line;
    std::map<std::pair<std::string, std::string>, std::vector<std::pair<std::string, std::string>>> student_classes;
    std::map<std::string, std::string> student_name;
    std::getline(file_, line);
    while(std::getline(file_, line)) {
        std::istringstream iss(line);
        std::string value;
        std::vector<std::string> v;
        while (std::getline(iss, value, ',')) {
            v.push_back(value);
        }
        std::pair<std::string, std::string> current;
        current.first = v.at(0);
        current.second = v.at(1);
        auto it = student_classes.find(current);
        if (it == student_classes.end()) {
            student_classes[current] = {{v.at(2), v.at(3)}};
        } else {
            it->second.emplace_back(v.at(2), v.at(3));
        }
    }

    for (const auto &i : student_classes) {
        std::pair<std::string, std::string> code_name = i.first;
        Student s(code_name.second, code_name.first, i.second);
        students->insert(s);
    }
    file_.close();
}

void File_Reader::classListing(std::map<std::string, std::list<std::string>> *c) {
    if (!file_.is_open()) throw std::runtime_error("File does not exist");
    std::string line;
    std::getline(file_, line);
    while(std::getline(file_, line)) {
        std::istringstream iss(line);
        std::string value;
        std::vector<std::string> v;
        while (std::getline(iss, value, ',')) {
            v.push_back(value);
        }
        auto it = c->find(v.at(0));
        if (it == c->end()) {
            c->insert({v.at(0), {v.at(1)}});
        } else {
            it->second.push_back(v.at(1));
        }
    }
    file_.close();
}

std::stack<std::vector<std::string>> File_Reader::read_changes() {
    std::stack<std::vector<std::string>> res;
    if (!file_.is_open()) throw std::runtime_error("File does not exist");
    std::string line;
    while (std::getline(file_, line)) {
        std::istringstream iss(line);
        std::string value;
        std::vector<std::string> v;
        while (std::getline(iss, value, ',')) {
            v.push_back(value);
        }
        res.push(v);
    }
    return res;
}

