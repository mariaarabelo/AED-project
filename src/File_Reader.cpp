//
// Created by alexandre on 11-10-2023.
//

#include "File_Reader.h"

File_Reader::File_Reader(const std::string &file_name) {
    this->file_name_ = file_name;
    std::vector<std::vector<std::string>> data;
    if (read_file(data)) {
        data_ = data;
    }
}

bool File_Reader::read_file(std::vector<std::vector<std::string>> &data) {
    std::ifstream file(file_name_);
    if (!file.is_open()) return false;
    std::string line;
    while(std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> row;
        std::string cell;
        while (std::getline(iss, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    file.close();
    return true;
}
