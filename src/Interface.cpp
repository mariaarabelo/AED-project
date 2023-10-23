#include "Interface.h"

Interface::Interface(const Application &app){
}

void Interface::print_title(const std::vector<std::string>& t){
    for (const std::string& s : t){
        std::cout << s << std::endl;
    }
}

void Interface::print_options(){
    for (const std::string& s : Options[location]){
        if (s == Options[location][selected]){
            std::cout << "< " << underline << bold << red << s << end << " >" << std::endl << "\n";
        }
        else {
            std::cout << bold << "  " << s << end << std::endl << "\n";
        }
    }
}

void Interface::print_directory(){
    std::cout << bold << " --";
    for (char c : directory){
        std::cout << "-";
    }
    std::cout << "\n| " << directory << " |" << std::endl;
    std::cout << " --";
    for (char c : directory){
        std::cout << "-";
    }
    std::cout << end << "\n\n\n";
}

void Interface::basicInputResponse(const int& user_in){
    if (user_in == 'A'){
        if (selected > 0){selected -= 1;}
        else{selected = Options[location].size() - 1;}
    }
    if (user_in == 'B'){selected += 1;}
    if (selected >= Options[location].size() ){
        selected = 0;
    }
    if (user_in == 'q'){location = -1;}
//----------------------------------- Enter inputs traveling the menu ------------------------------------//
    if (user_in == '\n'){
        switch (location){
            case 0:
                switch (selected){
                    case 0:
                        earlier_directory = directory;
                        directory += Options[location][selected];
                        location = 1;
                        break;
                    case 1:
                        break;
                    case 2:
                        location = -1;
                        break;
                    default:
                        break;
                }
                break;
            case 1:
                switch (selected){
                    case 0:
                        earlier_directory = directory;
                        directory += " > " + Options[location][selected];
                        location = 2;
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        location = 0;
                        selected = 0;
                        directory = "";
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                switch (selected){
                    case 0:
                        earlier_directory = directory;
                        directory += " > " + Options[location][selected];
                        location = 3;
                        break;
                    case 1:
                        break;
                    case 2:
                        directory = earlier_directory;
                        location = 1;
                        selected = 0;
                        break;
                    case 3:
                        location = 0;
                        selected = 0;
                        directory = "";
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                switch (selected){
                    case 0:
                        break;
                    case 1:
                        directory = earlier_directory;
                        location = 2;
                        selected = 0;
                        break;
                    case 2:
                        location = 0;
                        selected = 0;
                        directory = "";
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
//---------------------------------------------------------------------------------------------------------
}

void Interface::inputer(){
    user_input = getchar();
    if (user_input == 27) {
        user_input = getchar();
        user_input = getchar();
    }
    basicInputResponse(user_input);
}

void Interface::run(){
    struct termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt); // Get the current terminal settings

    newt = oldt; // Copy the current settings to the new settings

    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode (line buffering) and echoing

    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Set the new settings

    while(location != -1)
    {
        switch (location) {
            case 0:                      //MAIN MENU
                system("clear");
                print_title(Horarinator);
                print_options();
                std::cout << "\n\n" << italic << Helper << end_italic;
                inputer();
                break;
            case 1:                    // CONSULT
            case 2:                    // CONSULT SCHEDULE
                system("clear");
                print_directory();
                print_options();
                std::cout << "\n\n" << italic << Helper << end_italic;
                inputer();
                break;
            case 3:                      // CONSULT SCHEDULE STUDENT
                system("clear");
                print_directory();
                print_options();
                std::cout << "\n\n" << italic << Helper << end_italic;
                std::cout << "\n" << italic << Helper_Students << end_italic;
                inputer();
                break;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //restore old terminal
    system("clear");
}