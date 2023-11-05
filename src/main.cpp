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
    Application application;
    Interface anInterface(application);
    anInterface.run();
    return 0;
    //test
}