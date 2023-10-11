//
// Created by alexandre on 11-10-2023.
//

#ifndef AED_PROJECT_FILE_READER_H
#define AED_PROJECT_FILE_READER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Class.h"
#include "UC.h"

class File_Reader {
private:
    std::string file_name_;
    std::vector<std::vector<std::string>> data_;
    bool read_file(std::vector<std::vector<std::string>> &data);
public:
    explicit File_Reader(const std::string &file_name);
};


#endif //AED_PROJECT_FILE_READER_H
