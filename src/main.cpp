//
// Created by alexandre on 09-10-2023.
//

#include <iostream>
#include "Application.h"
#include <exception>
#include "Interface.h"

int main(int argc, char *argv[]) {
    /*
     * TODO
     * Very important to add a function that runs when closing the program to write all the changes to the files.
     */
    try {
        Application application;
        //202025232,Iara,L.EIC002,1LEIC05
        //202071557,Ludovico,L.EIC021,3LEIC04
        //std::cout << application.remove_student_from_uc("202025232","L.EIC002","1LEIC05") << "\n";
        std::cout << application.add_student_to_uc("202071557","L.EIC021","1LEIC05") << "\n";
        //Interface anInterface(application);
        //anInterface.run();
    } catch (const std::exception &e) {
        std::cout << e.what();
    }
    return 0;
}