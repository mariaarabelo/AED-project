//
// Created by alexandre on 11-10-2023.
//

#include <map>
#include "File_Reader.h"

File_Reader::File_Reader(const std::string &file_name) {
    file_.open(file_name);
}

bool File_Reader::read_file(std::vector<std::vector<std::string>> &data) {
    if (!file_.is_open()) return false;
    std::string line;
    while(std::getline(file_, line)) {
        std::istringstream iss(line);
        std::vector<std::string> row;
        std::string cell;
        while (std::getline(iss, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    file_.close();
    return true;
}

std::vector<Lecture> File_Reader::instatiateLectures() {
    //TODO
    //need to improve the error thrown
    if (!file_.is_open()) throw std::runtime_error("File does not exist");
    std::string line;
    std::vector<Lecture> res;
    while(std::getline(file_, line)) {
        std::istringstream iss(line);
        std::string value;
        std::vector<std::string> v;
        while (std::getline(iss, value, ',')) {
            v.push_back(value);
        }
        Lecture l(v.at(0), v.at(1), v.at(2),v.at(3),
                  v.at(4), v.at(5));
        res.push_back(l);
    }
    file_.close();
    return res;
}

std::vector<Student> File_Reader::instantiateStudents() {
    if (!file_.is_open()) throw std::runtime_error("File does not exist");
    std::string line;
    std::vector<Student> res;
    std::map<std::pair<std::string, std::string>, std::vector<std::pair<std::string, std::string>>> student_classes;
    std::map<std::string, std::string> student_name;
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
        res.push_back(s);
    }
    file_.close();
    return res;
}
