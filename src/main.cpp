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
#include "Application.h"
#include "Interface.h"

int main(int argc, char *argv[]) {
    Application application;
    Interface anInterface(application);
    anInterface.run();
    return 0;
}