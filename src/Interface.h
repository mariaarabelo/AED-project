//
// Created by master on 21-10-2023.
//

#ifndef AED_PROJECT_INTERFACE_H
#define AED_PROJECT_INTERFACE_H

#endif //AED_PROJECT_INTERFACE_H

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <string>
#include "File_Reader.h"
#include "Class.h"
#include "Student.h"
#include "Schedule.h"
#include "Application.h"

//----------------------------------------- Class Stuff ------------------------------------------------------//
class Interface{
public:
    Interface(const Application &app);
    void run();

private:
    //----------------- COLOR SCHEMES --------------------//
    std::string end = "\033[0m";
    std::string end_italic = "\x1b[0m";
    std::string underline = "\033[4m";
    std::string bold = "\033[1m";
    std::string italic = "\x1b[3m";
    std::string red = "\033[31m";
    //----------------------------------------------------//
    int location = 0;

    unsigned long selected = 0;

    int user_input{};

    std::string earlier_directory;
    std::string directory;

    std::vector<std::string> Horarinator = {
            " --------------------------------------------------------------------------------------------------------------- ",
            "|           █    █    ████   █████    ████   █████  ██████ ███    ██   ████  ████████  ████   █████             |",
            "|           █    █   █    █  █    █  █    █  █    █   ██   ██ █   ██  █    █    ██    █    █  █    █            |",
            "|           ██████  █      █ █████   ██████  █████    ██   ██  █  ██  ██████    ██   █      █ █████             |",
            "|           █    █   █    █  █   █  █      █ █   █    ██   ██   █ ██ █      █   ██    █    █  █   █             |",
            "|           █    █    ████   █    █ █      █ █    █ ██████ ██    ███ █      █   ██     ████   █    █    3000    |",
            " --------------------------------------------------------------------------------------------------------------- ",
            "\n"
    };

    std::vector<std::vector<std::string>> Options = {
            {
                    "Consult",
                    "Option 2",
                    "Quit"
            },
            {
                    "Schedules",
                    "Option 2",
                    "Option 3",
                    "Main Menu"
            },
            {
                    "Students",
                    "Classes",
                    "Back",
                    "Main Menu"
            },
            {
                    "Search for Student",
                    "Back",
                    "Main Menu"
            }
    };

    std::string Helper = {" Use 'up' and 'down' arrow keys to navigate and 'enter' to select"};
    std::string Helper_Students = {" Use 'tab' to interact and stop interacting with the students list"};

    void inputer();

    void basicInputResponse(const int &user_in);

    void print_directory();

    void print_options();

    static void print_title(const std::vector<std::string> &t);
};
//------------------------------------------------------------------------------------------------------------//



