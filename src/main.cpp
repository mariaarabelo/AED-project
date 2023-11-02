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
    //TODO: ADD EDGE CASE TO WHEN STUDENT IS ALREADY IN CLASS AND YOURE TRYING TO ADD HIM INTO IT
    Application application;
    //202025232,Iara,L.EIC002,1LEIC05
    //std::cout << application.remove_student_from_uc("202025232", "L.EIC002", "1LEIC05") << "\n";
    std::string s = "202025232";

    //auto it = std::find_if(application.students().begin(), application.students().end(), [s](const Student &obj) {
        //return s == obj.student_code();
    //});
    //Schedule sc(*it, application.lectures());
    //sc.printSchedule();
    std::cout << application.add_student_to_uc("202025232", "L.EIC001", "1LEIC05");
    return 0;
}