//
// Created by alexandre on 11-10-2023.
//

#ifndef AED_PROJECT_FILE_READER_H
#define AED_PROJECT_FILE_READER_H

#include <vector>
#include <string>
#include <fstream>
#include <stack>
#include <sstream>
#include <utility>
#include <list>
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
    /**
     * @brief used to instantiate the Lectures
     * @return vector of all lectures
     */
    std::vector<Lecture> instatiateLectures();
    /**
     * @brief used to instantiate students
     * @param students vector where students will be stored
     */
    void instantiateStudents(std::set<Student> *students);
    void classListing(std::map<std::string, std::list<std::string>> *c);
    /**
     * @brief scans shcanges.csv for recent changes
     * @return stack with the most recent changes in the form of a vector of strings
     */
    std::stack<std::vector<std::string>> read_changes();
};

#endif //AED_PROJECT_FILE_READER_H
