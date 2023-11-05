//
// Created by master on 21-10-2023.
//

#ifndef AED_PROJECT_INTERFACE_H
#define AED_PROJECT_INTERFACE_H

#endif //AED_PROJECT_INTERFACE_H

#include <iostream>
#include <codecvt>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <locale>
#include "File_Reader.h"
#include "Class.h"
#include "Student.h"
#include "Schedule.h"
#include "Application.h"

//----------------------------------------- Class Stuff ------------------------------------------------------//
class Interface {
public:
    explicit Interface(const Application &app);

    void run();


private:
    //----------------- COLOR SCHEMES --------------------//
    std::wstring w_bg_light_red = L"\x1b[101m";
    std::wstring w_end_bg = L"\x1b[0m";
    std::wstring w_italic = L"\x1b[3m";
    std::wstring w_end_italic = L"\x1b[0m";
    std::wstring w_red = L"\033[31m";
    std::wstring w_bold = L"\033[1m";
    std::wstring w_underline = L"\033[4m";;
    std::wstring w_end = L"\033[0m";
    //----------------------------------------------------//
    int location = 0;

    unsigned long selected = 0;

    int selected_in_page = 0;

    int page = 0;

    int names_per_page = 10;
    int names_last_page;
    int number_names[2] = {names_per_page, names_last_page};

    wchar_t user_input;

    bool table_mode = false;
    bool write_mode = false;
    bool day_printed = false;
    bool write_has_letters = false;
    bool done = false;

    Application app_;

    std::vector<Lecture> lectures;

    std::vector<std::pair<std::string, std::string>> student_list;
    std::vector<std::pair<std::wstring, std::wstring>> w_student_list;
    std::vector<std::pair<std::wstring, std::wstring>> filtered_w_student_list;
    std::vector<std::pair<std::wstring, std::wstring>> save_filtered_w_student_list;


    std::vector<std::string> class_code_list;
    std::vector<std::wstring> w_class_code_list;
    std::vector<std::wstring> filtered_w_class_code_list;

    std::vector<std::string> uc_list;
    std::vector<std::wstring> w_uc_list;
    std::vector<std::wstring> filtered_w_uc_list;


    std::vector<std::vector<std::pair<std::wstring, std::wstring>>> booked_list;
    std::vector<std::vector<std::wstring>> booked_list_vector_of_wstrings;

    std::wstring earlier_directory;
    std::wstring directory;
    std::wstring temporary_directory;
    std::wstring write = w_italic + L"  You can write here  " + w_end_italic;
    const std::wstring write_default = w_italic + L"  You can write here  " + w_end_italic;

    std::wstring s_analised;
    std::wstring c_analised;
    std::wstring uc_analised;

    std::wstring feedback;


    std::vector<std::wstring> Horarinator = {
            L" --------------------------------------------------------------------------------------------------------------- ",
            L"|           █    █    ████   █████    ████   █████  ██████ ███    ██   ████  ████████  ████   █████             |",
            L"|           █    █   █    █  █    █  █    █  █    █   ██   ██ █   ██  █    █    ██    █    █  █    █            |",
            L"|           ██████  █      █ █████   ██████  █████    ██   ██  █  ██  ██████    ██   █      █ █████             |",
            L"|           █    █   █    █  █   █  █      █ █   █    ██   ██   █ ██ █      █   ██    █    █  █   █             |",
            L"|           █    █    ████   █    █ █      █ █    █ ██████ ██    ███ █      █   ██     ████   █    █    3000    |",
            L" --------------------------------------------------------------------------------------------------------------- ",
            L"\n"
    };

    std::vector<std::vector<std::wstring>> Options = {
            {
                    L"Consult",
                    L"Make change request",
                    L"History",
                    L"Quit"
            },
            {
                    L"Schedules",
                    L"Students",
                    L"Classes",
                    L"UCs",
                    L"Main Menu"
            },
            {
                    L"Students",
                    L"Classes",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Search for Student",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Search for Class",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"More information about ",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Search for Student",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Schedule",
                    L"Classes",
                    L"UCs",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"More information about ",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Schedule",
                    L"Students",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Search for Class",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Search for UC",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Students",
                    L"Classes",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Search for Student",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"UC",
                    L"Switch Classes",
                    L"Main Menu"
            },
            {
                    L"Remove Student from UC",
                    L"Add Student to a UC",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Search for Student",
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Back",
                    L"Main Menu"
            },
            {
                    L"Back",
                    L"Main Menu"
            }
    };

    std::wstring Helper = L" Use 'up' and 'down' arrow keys to navigate and 'enter' to select";
    std::wstring Helper_Students = L" Use 'tab' to interact and stop interacting with the students list";
    std::wstring Helper_Classes = L" Use 'tab' to interact and stop interacting with the classes list";
    std::wstring Helper_UCs = L" Use 'tab' to interact and stop interacting with the UCs list";


    static void print_title(const std::vector<std::wstring> &t);

    void print_options();

    void print_directory();

    void inputer();

    void basicInputResponse(wchar_t &user_in);

    void list_booker(std::vector<std::pair<std::wstring, std::wstring>> l);

    void booked_list_printer();

    static int tem_acento(const std::wstring &s);

    static void alphabetic_sort_vector_of_pairs_of_strings (std::vector<std::pair<std::string, std::string>> &v);

    static void alphabetic_sort_vector_of_strings (std::vector<std::string> &v);

    void InputResponse_inWriteMode(wchar_t &user_in);

    static std::vector<std::pair<std::wstring, std::wstring>> convert_to_wstring_vector_of_pairs(const std::vector<std::pair<std::string, std::string>>& v);

    static std::wstring smooth_string(const std::wstring& w);

    static std::wstring only_numbers(const std::wstring &w, bool allow_zeros);

    static std::vector<std::wstring> convert_to_wstring_vector_of_strings(const std::vector<std::string> &v);

    void list_booker_vector_of_wstrings(std::vector<std::wstring> wv);

    void booked_list_filter_vector_of_wstrings(const std::vector<std::wstring>& vw, std::vector<std::wstring>& filtered_vw);

    void booked_list_printer_vector_of_wstrings(const std::vector<std::wstring>& wv);

    static std::string convert_to_string(const std::wstring &ws);

    void schedule_printer(const Schedule& schedule);

    static std::wstring convert_to_wstring(const std::string &s);

    static void lecture_sorter(std::vector<Lecture> &v);

    static bool earlier_day(const std::string& s1, const std::string& s2);

    static std::string better_representation(const std::string& s);

    static bool hour_comparer(const std::string& s1, const std::string& s2);

    Student get_student_by_id(const std::vector<Student> &v);

    static void alphabetic_sort_vector_of_wstrings(std::vector<std::wstring> &v);

    static void alphabetic_sort_vector_of_pairs_of_wstrings(std::vector<std::pair<std::wstring, std::wstring>> &v);

    void booked_list_filter(const std::vector<std::pair<std::wstring, std::wstring>> &vw, std::vector<std::pair<std::wstring, std::wstring>> &filtered_vw);

    void print_feedback(const std::wstring &ws);
};

//------------------------------------------------------------------------------------------------------------//
