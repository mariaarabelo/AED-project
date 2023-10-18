//
// Created by alexandre on 09-10-2023.
//

#include <iostream>
#include "File_Reader.h"
#include "Class.h"
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
    File_Reader f("../dataset/classes.csv");
    std::vector<Lecture> l = f.instatiateLectures();
    Class c("1LEIC12", l);
    c.printLectures();
    return 0;
}