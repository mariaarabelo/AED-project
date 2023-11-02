#include "Interface.h"

Interface::Interface(const Application &app){
}

void Interface::alphabetic_sort(std::vector<std::pair<std::string, std::string>> &v){
    std::sort(v.begin(), v.end(), [](const auto& a, const auto& b){
        return a.first < b.first;
    });
}

std::vector<std::pair<std::wstring, std::wstring>> Interface::convert_to_wstring(const std::vector<std::pair<std::string, std::string>>& v){
    std::vector<std::pair<std::wstring, std::wstring>> wv;
    for (const std::pair<std::string, std::string>& p : v){
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wstr_first = converter.from_bytes(p.first);
        std::wstring wstr_second = converter.from_bytes(p.second);
        wv.emplace_back(wstr_first, wstr_second);
    }
    return wv;
}

std::wstring Interface::smooth_string(const std::wstring& w){
    std::wstring sw;
    for (wchar_t c : w) {
        if (!iswspace(c)) {
            c = std::tolower(c);
            switch (c) {
                case L'á':
                case L'à':
                case L'â':
                case L'ä':
                case L'ã':
                case L'Á':
                case L'À':
                case L'Ã':
                case L'Â':
                case L'Ä':
                    sw += L'a';
                    break;
                case L'é':
                case L'è':
                case L'ê':
                case L'ë':
                case L'ẽ':
                case L'Ë':
                case L'É':
                case L'È':
                case L'Ê':
                case L'Ẽ':
                    sw += L'e';
                    break;
                case L'í':
                case L'ì':
                case L'î':
                case L'ï':
                case L'ĩ':
                case L'Í':
                case L'Ì':
                case L'Î':
                case L'Ĩ':
                case L'Ï':
                    sw += L'i';
                    break;
                case L'ó':
                case L'ò':
                case L'ô':
                case L'ö':
                case L'õ':
                case L'Ó':
                case L'Ò':
                case L'Õ':
                case L'Ô':
                case L'Ö':
                    sw += L'o';
                    break;
                case L'ú':
                case L'ù':
                case L'û':
                case L'ü':
                case L'ũ':
                case L'Ú':
                case L'Ù':
                case L'Ũ':
                case L'Û':
                case L'Ü':
                    sw += L'u';
                    break;
                default:
                    sw += c;
            }
        }
    }
    return sw;
}

void Interface::print_title(const std::vector<std::wstring>& t){
    for (const std::wstring& s : t){
        std::wcout << s << std::endl;
    }
}

void Interface::print_options(){
    for (const std::wstring& s : Options[location]){
        if (s == Options[location][selected] && !table_mode){
            if (Options[location][selected].substr(0, 6) == L"Search"){
                std::wcout << L"< " << w_underline << w_bold << w_red << L"Search for students name or ID ->" << w_end  << L"   " << write << L"   >" << std::endl << L"\n";
            }
            else {
                std::wcout << "< " << w_underline << w_bold << w_red << s << w_end << L" >" << std::endl << L"\n";
            }
        }
        else {
            std::wcout << w_bold << L"  " << s << w_end << std::endl << L"\n";
        }
    }
}

void Interface::print_directory(){
    std::wcout << w_bold << L" --";
    for (char c : directory){
        std::wcout << L"-";
    }
    std::wcout << L"\n| " << directory << L" |" << std::endl;
    std::wcout << L" --";
    for (char c : directory){
        std::wcout << L"-";
    }
    std::wcout << w_end << L"\n\n\n";
}

void Interface::list_booker(std::vector<std::pair<std::wstring, std::wstring>> l) {
    booked_list.clear();
    number_names[1] = 0;
    std::vector<std::pair<std::wstring, std::wstring>> v;
    int loop = 0;
    while (l.size() >= names_per_page){
        for (int i = 0; i < names_per_page; i++){
            v.push_back(l[i]);
        }
        v.emplace_back(L"Next", L"Page ['n']");
        if (loop > 0){v.emplace_back(L"Previous", L"Page ['p']");}
        if (loop > 1){v.emplace_back(L"First", L"Page");}
        if (l.size() - names_per_page > names_per_page){v.emplace_back(L"Last", L"Page");}
        booked_list.push_back(v);
        l.erase(l.begin(), l.begin() + names_per_page);
        v.clear();
        loop ++;
    }
    for (const std::pair<std::wstring, std::wstring>& p : l){
        v.push_back(p);
        number_names[1] ++;
    }
    if(booked_list.size() > 1){v.emplace_back(L"Previous", L"Page ['p']");}
    if(booked_list.size() > 2){v.emplace_back(L"First", L"Page");}
    booked_list.push_back(v);
}

void Interface::booked_list_filter(){
    filtered_w_student_list.clear();
    if(!(write.empty()) && write != write_default){
        std::wstring smooth_write = smooth_string(write);
        if (isalnum(smooth_write[0]) && !isalpha(smooth_write[0])){
            for (const std::pair<std::wstring, std::wstring>& p : w_student_list){
                if(smooth_string(p.second).substr(0, smooth_write.size()) == smooth_write){
                    filtered_w_student_list.push_back(p);
                }
            }
        }
        else{
            for (const std::pair<std::wstring, std::wstring>& p : w_student_list){
                if(smooth_string(p.first).substr(0, smooth_write.size()) == smooth_write){
                    filtered_w_student_list.push_back(p);
                }
            }
        }
    }
    else{
        filtered_w_student_list = w_student_list;
    }
}

void Interface::booked_list_printer(){
    std::wcout << L"\n\n" << w_bold << L" ------------------------------------------------ " << w_end << L"\n";
    int idx = 0;
    for (const std::pair<std::wstring, std::wstring>& p : booked_list[page]){
        if (p == booked_list[page][selected_in_page] && table_mode) {
            if (idx < number_names[page == booked_list.size() - 1]) {
                std::wcout << L"| " << w_bg_light_red << w_underline << p.first << std::wstring(30 + tem_acento(p.first)- p.first.size(), ' ')
                           << L"| "
                           << p.second << std::wstring(14 - p.second.size(), ' ') << w_end << w_end_bg << L" |" << std::endl;
            }
            else{
                if (idx == number_names[page == booked_list.size() - 1]){std::wcout << L"|------------------------------------------------|" << std::endl;}
                std::wcout << L"| " << w_bg_light_red << w_italic  << w_underline << w_bold << p.first << L' ' << p.second << std::wstring(45 - p.first.size() - p.second.size(), ' ') << w_end_italic << w_end  << L" |" << std::endl;
            }
        }
        else if ( idx < number_names[page == booked_list.size() - 1]){
            std::wcout << L"| " << p.first << std::wstring(30 + tem_acento(p.first) - p.first.size(), ' ') << L"| " << p.second
                       << std::wstring(14 - p.second.size(), ' ') << L" |" << std::endl;
        }
        else{
            if (idx == number_names[page == booked_list.size() - 1]){std::wcout << L"|------------------------------------------------|" << std::endl;}
            std::wcout << L"| " << w_italic << w_bold << p.first << L' ' << p.second << w_end_italic << w_end << std::wstring(45 - p.first.size() - p.second.size(), ' ') << L" |" << std::endl;
        }
        idx ++;
    }
    std::wcout << L"|------------------------------------------------|" << std::endl;
    std::wcout << L"|" << std::wstring(44 - std::to_string(page + 1).size() - std::to_string(booked_list.size()).size(), ' ') << page + 1 << L"/" << booked_list.size() << L"   |" << std::endl;
    std::wcout << w_bold << L" ------------------------------------------------ " << w_end << std::endl;
}

int Interface::tem_acento(const std::wstring& s) {
    int count = 0;
    for (wchar_t c : s){
        if (c >= 128 && c <= 255){
            count ++;
        }
    }
    count /= 2;
    return count;
}

void Interface::basicInputResponse(wchar_t& user_in) {
    if (location == 3) {
        if (user_in == '\t') {
            table_mode = !table_mode;
            selected = 0;
            selected_in_page = 0;
        }
        if (user_in == 'n'){
            page ++;
            selected_in_page = 0;
            if (page >= booked_list.size()){
                page --;
            }
        }
        if (user_in == 'p'){
            page --;
            selected_in_page = 0;
            if (page < 0){
                page ++;
            }
        }
    }

    if (!table_mode) {
        if (user_in == 'A') {
            if (selected > 0) { selected -= 1; }
            else { selected = Options[location].size() - 1; }
        }
        if (user_in == 'B') {
            selected ++;
            if (selected >= Options[location].size()) {selected = 0;}
        }
    }
    else{
        if (user_in == 'A') {
            if (selected_in_page > 0) { selected_in_page -= 1; }
            else { selected_in_page = booked_list[page].size() - 1; }
        }
        if (user_in == 'B'){
            selected_in_page ++;
            if (selected_in_page > booked_list[page].size() - 1){selected_in_page = 0;}
        }
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
                        break;
                    case 3:
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
                        directory += L" > " + Options[location][selected];
                        location = 2;
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        location = 0;
                        selected = 0;
                        directory = L"";
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                switch (selected){
                    case 0:
                        earlier_directory = directory;
                        directory += L" > " + Options[location][selected];
                        location = 3;
                        break;
                    case 1:
                        break;
                    case 2:
                        directory = L"Consult";
                        location = 1;
                        selected = 0;
                        break;
                    case 3:
                        location = 0;
                        selected = 0;
                        directory = L"";
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                switch (table_mode){
                    case false:
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
                                directory = L"";
                                break;
                            default:
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 &&
                                    selected_in_page < number_names[page == booked_list.size() - 1]) {

                                }
                                else if (booked_list[page][selected_in_page].first == L"Next") {
                                    page++;
                                    selected_in_page = 0;
                                }
                                else if (booked_list[page][selected_in_page].first == L"Previous") {
                                    page--;
                                    selected_in_page = 0;
                                }
                                else if (booked_list[page][selected_in_page].first == L"First") {
                                    page = 0;
                                    selected_in_page = 0;
                                }
                                else if (booked_list[page][selected_in_page].first == L"Last") {
                                    page = booked_list.size() - 1;
                                    selected_in_page = 0;
                                }
                        }
                        break;
                }
            default:
                break;
        }
    }
//--------------------------------------------------------------------------------------------------------//
}

void Interface::InputResponse_inWriteMode(wchar_t &user_in) {
    if (isalpha(user_in)){
        if (write == write_default) {
            write = L"";
        }
        write += user_in;
    }
    else if (isalnum(user_in)){
        if (write == write_default) {
            write = L"";
        }
        write += user_in;
    }
    else if (user_in >= 128 && user_in <= 255){
        if (write == write_default) {
            write = L"";
        }
        write += user_in;
    }
    if (user_in == 32 && write != write_default){
        write += L" ";
    }
    if ((user_in == 8 || user_in == 127) && write != write_default){
        if(!write.empty()){
            write.pop_back();
        }
    }
    if (write.empty()) {
        write = write_default;
    }
}

void Interface::inputer(){
    user_input = getwchar();

    if (!write_mode) {
        if (user_input == 27) {
            user_input = getwchar();
            user_input = getwchar();
        }
        basicInputResponse(user_input);
    }
    else{
        if (user_input == 27){
            user_input = getwchar();
            user_input = getwchar();
            write_mode = false;
            basicInputResponse(user_input);
        }
        else if (user_input == 9){
            write_mode = false;
            table_mode = true;
        }
        else if (user_input == '\n'){
            write_mode = false;
            table_mode = true;
        }
        else {
            InputResponse_inWriteMode(user_input);
        }
    }
}

void Interface::run(){

    student_list = app_.students_name_id();
    alphabetic_sort(student_list);
    w_student_list = convert_to_wstring(student_list);

    setlocale(LC_CTYPE, "en_US.UTF-8"); // enconding to UTF-8 for extended characters such as "ç"

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
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                inputer();
                break;
            case 1:                    // CONSULT
            case 2:                    // CONSULT SCHEDULE
                system("clear");
                print_directory();
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                inputer();
                break;
            case 3:                      // CONSULT SCHEDULE STUDENT
                system("clear");
                print_directory();
                if (!write.empty() && write!= write_default){
                    Options[location][0] = L"Searching for: " + w_end + write + w_bold;
                }
                else{
                    Options[location][0] = L"Search for Student";
                }
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_Students << w_end_italic << std::endl;
                if (Options[location][selected].substr(0, 6) == L"Search" && !table_mode) {
                    write_mode = true;
                }
                booked_list_filter();
                list_booker(filtered_w_student_list);
                booked_list_printer();
                inputer();
                break;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //restore old terminal
    system("clear");
}