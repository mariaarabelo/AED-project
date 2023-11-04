//
// Created by alexandre on 09-10-2023.
//

#include <iostream>
#include "File_Reader.h"
#include "Class.h"
#include "Student.h"
#include "Schedule.h"
#include <vector>
#include <string>
#include <stack>
#include "Application.h"
#include "Interface.h"
#include "globals.h"

int CAP = 0;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        CAP = 20;
    }
    else {
        CAP = std::stoi(argv[1]);
    }
    //TODO: ADD EDGE CASE TO WHEN STUDENT IS ALREADY IN CLASS AND YOURE TRYING TO ADD HIM INTO IT
    Application application;
    std::cout << application.add_student_to_uc("202025232", "L.EIC001", "1LEIC05");
    File_Reader f("../dataset/changes.csv");
    auto st = f.read_changes();
    std::cout << application.reverse_changes(st);
    return 0;
    //test
}