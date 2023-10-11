//
// Created by alexandre on 09-10-2023.
//

#include <iostream>
#include "File_Reader.h"
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
    std::vector<std::vector<std::string>> d;
    File_Reader f("../dataset/classes_per_uc.csv");
    f.read_file(d);
    for (const auto& a : d) {
        for (auto b : a) {
            std::cout << b;
        }
        std::cout << "\n";
    }

    return 0;
}