//
// Created by alexandre on 11-10-2023.
//

#ifndef AED_PROJECT_FILE_READER_H
#define AED_PROJECT_FILE_READER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <list>
#include <set>
#include <map>
#include <iostream>
#include "Class.h"
#include "UC.h"
#include "Student.h"

class File_Reader {
private:
    std::ifstream file_;
    std::vector<std::vector<std::string>> data_;
public:
    explicit File_Reader(const std::string &file_name);
    std::vector<Lecture> instatiateLectures();
    void instantiateStudents(std::set<Student> *students);
    void classListing(std::map<std::string, std::list<std::string>> *c);
    void writeToFile(std::string line);
};

#endif //AED_PROJECT_FILE_READER_H
