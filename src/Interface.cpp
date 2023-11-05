#include "Interface.h"

Interface::Interface(const Application &app){
}

Student Interface::get_student_by_id(const std::set<Student>& v){
    auto it = std::find_if(v.begin(), v.end(), [this](const Student &s) {
        return convert_to_wstring(s.student_code()) == s_analised.substr(s_analised.find_first_of(L'(') + 1, 9);
    });
    if (it != v.end()) return *it;
}

Student Interface::get_student_by_id_with_parameters(const std::set<Student>& v, const std::wstring& wstr){
    auto it = std::find_if(v.begin(), v.end(), [wstr](const Student &s) {
        return convert_to_wstring(s.student_code()) == wstr;
    });
    if (it != v.end()) return *it;
}

bool Interface::earlier_day(const std::string& s1, const std::string& s2)   {
    int idx1 = 0;
    int idx2 = 0;
    std::list<std::string> l = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    for (const std::string& s : l){
        if (s == s1){
            break;
        }
        idx1 ++;
    }
    for (const std::string& s : l){
        if (s == s2){
            break;
        }
        idx2 ++;
    }
    return idx1 < idx2;
}

bool Interface::hour_comparer(const std::string& s1, const std::string& s2){
    return std::stof(s1) < std::stof(s2);
}

void Interface::alphabetic_sort_vector_of_pairs_of_strings  (std::vector<std::pair<std::string, std::string>> &v){
    std::sort(v.begin(), v.end(), [](const auto& a, const auto& b){
        return a.first < b.first;
    });
}

void Interface::alphabetic_sort_vector_of_strings(std::vector<std::string> &v) {
    std::sort(v.begin(), v.end(), [](const auto& a, const auto& b){return a < b;});
}

void Interface::alphabetic_sort_vector_of_pairs_of_wstrings(std::vector<std::pair<std::wstring, std::wstring>> &v) {
    std::sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
        return a.first < b.first;
    });
}

void Interface::reverse_alphabetic_sort_vector_of_pairs_of_wstrings(std::vector<std::pair<std::wstring, std::wstring>> &v) {
    std::sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
        return a.first > b.first;
    });
}

void Interface::alphabetic_sort_vector_of_wstrings(std::vector<std::wstring> &v){
    std::sort(v.begin(), v.end(), [](const auto& a, const auto& b){return a < b;});
}

void Interface::reverse_alphabetic_sort_vector_of_wstrings(std::vector<std::wstring> &v){
    std::sort(v.begin(), v.end(), [](const auto& a, const auto& b){return a > b;});
}

std::wstring Interface::class_get_nums_students(const std::wstring& class_id){
    for(const auto& p : class_number_students) {
        if(p.first == class_id) return p.second;
    }
}

std::wstring Interface::ucs_get_nums_students(const std::wstring& uc_id){
    for(const auto& p : ucs_number_students) {
        if(p.first == uc_id) return p.second;
    }
}

void Interface::sort_classes_by_number_of_students_ascending(std::vector<std::wstring> &v){
    class_number_students = convert_to_wstring_vector_of_pairs(app_.class_id_student_number());
    std::sort(v.begin(), v.end(), [this](const auto& a, const auto& b){
        if(class_get_nums_students(a) == class_get_nums_students(b)) {
            return a < b;
        }
        else { return std::stoi(class_get_nums_students(a)) < std::stoi(class_get_nums_students(b));}
    });
}

void Interface::sort_classes_by_number_of_students_descending(std::vector<std::wstring> &v){
    class_number_students = convert_to_wstring_vector_of_pairs(app_.class_id_student_number());
    std::sort(v.begin(), v.end(), [this](const auto& a, const auto& b){
        if(class_get_nums_students(a) == class_get_nums_students(b)) {
            return a < b;
        }
        else { return std::stoi(class_get_nums_students(a)) > std::stoi(class_get_nums_students(b));}
    });
}

void Interface::sort_ucs_by_number_of_students_descending(std::vector<std::wstring> &v){
    ucs_number_students = convert_to_wstring_vector_of_pairs(app_.enrolled_students_in_ucs());
    std::sort(v.begin(), v.end(), [this](const auto& a, const auto& b){
        if(ucs_get_nums_students(a) == ucs_get_nums_students(b)) {
            return a < b;
        }
        else { return std::stoi(ucs_get_nums_students(a)) > std::stoi(ucs_get_nums_students(b));}
    });
}

void Interface::sort_ucs_by_number_of_students_ascending(std::vector<std::wstring> &v){
    ucs_number_students = convert_to_wstring_vector_of_pairs(app_.enrolled_students_in_ucs());
    std::sort(v.begin(), v.end(), [this](const auto& a, const auto& b){
        if(ucs_get_nums_students(a) == ucs_get_nums_students(b)) {
            return a < b;
        }
        else { return std::stoi(ucs_get_nums_students(a)) < std::stoi(ucs_get_nums_students(b));}
    });
}

void Interface::lecture_sorter(std::vector<Lecture> &v){
    std::sort(v.begin(), v.end(), [](const auto& a, const auto& b){
        if (a.weekday() == b.weekday()){
            return hour_comparer(a.start_hour(), b.start_hour());
        }
        else{
            return earlier_day(a.weekday(), b.weekday());
        }
    });
}

std::string Interface::better_representation(const std::string& s){
    int idx = 0;
    for (char c : s){
        if (c == '.'){
            break;
        }
        else{
            idx ++;
        }
    }
    if (idx == s.size()){
        return s.substr(0, idx) + ":00";
    }
    else{
        return s.substr(0, idx) + ":30";
    }
}

std::vector<std::pair<std::wstring, std::wstring>> Interface::convert_to_wstring_vector_of_pairs(const std::vector<std::pair<std::string, std::string>>& v){
    std::vector<std::pair<std::wstring, std::wstring>> wv;
    for (const std::pair<std::string, std::string>& p : v){
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wstr_first = converter.from_bytes(p.first);
        std::wstring wstr_second = converter.from_bytes(p.second);
        wv.emplace_back(wstr_first, wstr_second);
    }
    return wv;
}

std::vector<std::wstring> Interface::convert_to_wstring_vector_of_strings(const std::vector<std::string>& v){
    std::vector<std::wstring> wv;
    for (const std::string& s: v){
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wstr = converter.from_bytes(s);
        wv.emplace_back(wstr);
    }
    return wv;
}

std::wstring Interface::convert_to_wstring (const std::string& s){
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wstr = converter.from_bytes(s);
    return wstr;
}

std::string Interface::convert_to_string(const std::wstring& ws){
    std::locale loc("");
    std::string s;
    for (wchar_t wc : ws) {
        s += std::use_facet<std::ctype<wchar_t>>(loc).narrow(wc, 0);
    }
    return s;
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
                case L'ç':
                    sw += L'c';
                default:
                    if (!ispunct(c)) {
                        sw += c;
                    }
            }
        }
    }
    return sw;
}

std::wstring Interface::only_numbers(const std::wstring& w, bool allow_zeros = true) {
    std::wstring nw;
    for (wchar_t c: w) {
        if (isdigit(c)) {
            if (allow_zeros || ((c != '0') && !allow_zeros)) {
                nw.push_back(c);
            }
        }
    }
    return nw;
}

void Interface::print_feedback(const std::wstring& ws){
    std::wcout << L"\n ====================[  " << w_bold << w_underline << ws << w_end << L"  ]====================" << std::endl;
}

void Interface::print_title(const std::vector<std::wstring>& t){
    for (const std::wstring& s : t){
        std::wcout << s << std::endl;
    }
}

void Interface::print_options(){
    for (const std::wstring& s : Options[location]){
        if (s == Options[location][selected] && !table_mode){
            if (Options[location][selected].substr(0, 6) == L"Search" || Options[location][selected].substr(0, 4) == L"Show"){
                if (location == 3 || (location == 6 && selected == 0)|| location == 17 || location == 22 || location == 27) {
                    std::wcout << L"< " << w_underline << w_bold << w_red << L"Search for students name or ID ->"
                               << w_end << L"   " << write << L"   >" << std::endl << L"\n";
                }
                else if (location == 6 && selected == 2){
                    std::wcout << L"< " << w_underline << w_bold << w_red << L"Insert the minimum number of UCs ->"
                               << w_end << L"   " << write_n << L"   >" << std::endl << L"\n";
                }
                else if (location == 4 || location == 11){
                    std::wcout << L"< " << w_underline << w_bold << w_red << L"Search for class ID ->"
                               << w_end << L"   " << write << L"   >" << std::endl << L"\n";
                }
                else if(location == 15){
                    std::wcout << L"< " << w_underline << w_bold << w_red << L"Search for UC ID ->"
                               << w_end << L"   " << write << L"   >" << std::endl << L"\n";
                }
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
    if(!booked_list.empty()){v.emplace_back(L"Previous", L"Page ['p']");}
    if(booked_list.size() > 1){v.emplace_back(L"First", L"Page");}
    booked_list.push_back(v);
}

void Interface::list_booker_vector_of_wstrings(std::vector<std::wstring> wv) {
    booked_list_vector_of_wstrings.clear();
    number_names[1] = 0;
    std::vector<std::wstring> v;
    int loop = 0;
    while (wv.size() >= names_per_page){
        for (int i = 0; i < names_per_page; i++){
            v.push_back(wv[i]);
        }
        v.emplace_back(L"Next Page ['n']");
        if (loop > 0){v.emplace_back(L"Previous Page ['p']");}
        if (loop > 1){v.emplace_back(L"First Page");}
        if (wv.size() - names_per_page > names_per_page){v.emplace_back(L"Last Page");}
        booked_list_vector_of_wstrings.push_back(v);
        wv.erase(wv.begin(), wv.begin() + names_per_page);
        v.clear();
        loop ++;
    }
    for (const std::wstring& s : wv){
        v.push_back(s);
        number_names[1] ++;
    }
    if(!booked_list_vector_of_wstrings.empty()){v.emplace_back(L"Previous Page ['p']");}
    if(booked_list_vector_of_wstrings.size() > 1){v.emplace_back(L"First Page");}
    booked_list_vector_of_wstrings.push_back(v);
}

void Interface::aditional_filter_students(std::vector<std::pair<std::wstring, std::wstring>>& vw, int filter_mode){
    if (filter_mode == 0){
        alphabetic_sort_vector_of_pairs_of_wstrings(vw);
    }
    if (filter_mode == 1){
        reverse_alphabetic_sort_vector_of_pairs_of_wstrings(vw);
    }
}

void Interface::aditional_filter_classes(std::vector<std::wstring>& vw, int filter_mode){
    if (filter_mode == 0){
        alphabetic_sort_vector_of_wstrings(vw);
    }
    if (filter_mode == 1){
        reverse_alphabetic_sort_vector_of_wstrings(vw);
    }
    if (filter_mode == 2){
        sort_classes_by_number_of_students_ascending(vw);
    }
    if (filter_mode == 3){
        sort_classes_by_number_of_students_descending(vw);
    }
}

void Interface::aditional_filter_ucs(std::vector<std::wstring>& vw, int filter_mode){
    if (filter_mode == 0){
        alphabetic_sort_vector_of_wstrings(vw);
    }
    if (filter_mode == 1){
        reverse_alphabetic_sort_vector_of_wstrings(vw);
    }
    if (filter_mode == 2){
        sort_ucs_by_number_of_students_ascending(vw);
    }
    if (filter_mode == 3){
        sort_ucs_by_number_of_students_descending(vw);
    }
}

void Interface::booked_list_filter(const std::vector<std::pair<std::wstring, std::wstring>>& vw, std::vector<std::pair<std::wstring, std::wstring>>& filtered_vw){
    filtered_vw.clear();
    if (!(write.empty()) && write != write_default) {
        std::wstring smooth_write = smooth_string(write);
        if (isalnum(smooth_write[0]) && !isalpha(smooth_write[0])) {
            for (const std::pair<std::wstring, std::wstring> &p: vw) {
                if (smooth_string(p.second).substr(0, smooth_write.size()) == smooth_write) {
                    filtered_vw.push_back(p);
                }
            }
        } else {
            for (const std::pair<std::wstring, std::wstring> &p: vw) {
                if (smooth_string(p.first).substr(0, smooth_write.size()) == smooth_write) {
                    filtered_vw.push_back(p);
                }
            }
        }
    } else {
        filtered_vw = vw;
    }
}

void Interface::booked_list_filter_vector_of_wstrings(const std::vector<std::wstring>& vw, std::vector<std::wstring>& filtered_vw) {
    filtered_vw.clear();
    for (wchar_t c : smooth_string(write)){
        if (isalpha(c)){
            write_has_letters = true;
        }
    }
    if (!(write.empty()) && write != write_default) {
        std::wstring smooth_write = smooth_string(write);
        for (const std::wstring &s: vw) {
            if ((smooth_write == smooth_string(s).substr(0,smooth_write.size()) && write_has_letters) ||
                ((smooth_write == only_numbers(smooth_string(s), false).substr(0, smooth_write.size())  || (smooth_write == only_numbers(smooth_string(s)).substr(0, smooth_write.size())) ) && !write_has_letters)) {
                filtered_vw.push_back(s);
            }
        }
    } else {
        filtered_vw = vw;
    }
    write_has_letters = false;
}

void Interface::booked_list_printer(const std::vector<std::pair<std::wstring, std::wstring>>& vw){
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
    if (vw.empty()){std::wcout << "|" << w_italic << L"  No results                                    " << w_end << "|" << std::endl;}
    std::wcout << L"|------------------------------------------------|" << std::endl;
    std::wcout << L"|" << std::wstring(44 - std::to_string(page + 1).size() - std::to_string(booked_list.size()).size(), ' ') << page + 1 << L"/" << booked_list.size() << L"   |" << std::endl;
    std::wcout << w_bold << L" ------------------------------------------------ " << w_end << std::endl;
    std::wcout << w_italic << L"Number of students : " << w_end_italic << w_bold<< vw.size() << w_end << std::endl;
}

void Interface::booked_list_printer_vector_of_wstrings(const std::vector<std::wstring>& wv) {
    std::wcout << L"\n\n" << w_bold << L" ----------------------- " << w_end << L"\n";
    int idx = 0;
    for (const std::wstring &s: booked_list_vector_of_wstrings[page]) {
        if (s == booked_list_vector_of_wstrings[page][selected_in_page] && table_mode) {
            if (idx < number_names[page == booked_list_vector_of_wstrings.size() - 1]) {
                std::wcout << L"| " << w_bg_light_red << w_underline << s
                           << std::wstring(21 + tem_acento(s) - s.size(), ' ')
                           << w_end << w_end_bg << L" |" << std::endl;
            } else {
                if (idx == number_names[page == booked_list_vector_of_wstrings.size() - 1]) {
                    std::wcout << L"|-----------------------|" << std::endl;
                }
                std::wcout << L"| " << w_bg_light_red << w_italic << w_underline << w_bold << s << L' '
                           << w_end_italic
                           << w_end << std::wstring(20 - s.size(), ' ') << L" |" << std::endl;
            }
        } else if (idx < number_names[page == booked_list_vector_of_wstrings.size() - 1]) {
            std::wcout << L"| " << s << std::wstring(22 + tem_acento(s) - s.size(), ' ') << L"| "
                       << std::endl;
        } else {
            if (idx == number_names[page == booked_list_vector_of_wstrings.size() - 1]) {
                std::wcout << L"|-----------------------|" << std::endl;
            }
            std::wcout << L"| " << w_italic << w_bold << s << L' ' << w_end_italic << w_end
                       << std::wstring(20 - s.size(), ' ') << L" |" << std::endl;
        }
        idx++;
    }
    if (wv.empty()){std::wcout << "|" << w_italic << L"  No results           " << w_end << "|" << std::endl;}
    std::wcout << L"|-----------------------|" << std::endl;
    std::wcout << L"|" << std::wstring(19    - std::to_string(page + 1).size() - std::to_string(booked_list_vector_of_wstrings.size()).size(), ' ') << page + 1 << L"/" << booked_list_vector_of_wstrings.size() << L"   |" << std::endl;
    std::wcout << w_bold << L" ----------------------- " << w_end << std::endl;
}

void Interface::schedule_printer(const Schedule& schedule){
    lectures = schedule.get_lectures();
    lecture_sorter(lectures);
    std::wcout << w_bold << "\n" << L" ---------------------- MONDAY ----------------------"  << w_end << std::endl;
    for (const auto &lec : lectures){
        if (lec.weekday() == "Monday") {
            std::wcout << L"| " << w_underline << convert_to_wstring(lec.uc_code()) << w_end
                       << std::wstring(10 - convert_to_wstring(lec.uc_code()).size(), L' ')
                       << L" (" << convert_to_wstring(lec.type()) << L")"
                       << std::wstring(3 - convert_to_wstring(lec.type()).size(), ' ') << L"|| "
                       << convert_to_wstring(better_representation(lec.start_hour())) << L" - "
                       << convert_to_wstring(better_representation(lec.end_hour()))
                       << L" (" << convert_to_wstring(better_representation(lec.duration())) << L")"
                       << std::wstring(14 - convert_to_wstring(better_representation(lec.duration())).size() -
                                       convert_to_wstring(better_representation(lec.end_hour())).size()
                                       - convert_to_wstring(better_representation(lec.start_hour())).size(), L' ')
                       << L" || " << convert_to_wstring(lec.class_code()) << std::wstring(8 - convert_to_wstring(lec.class_code()).size(), L' ')
                       << L"|" << std::endl;
            day_printed = true;
        }
    }
    if (!day_printed){
        std::wcout << L"|   " << w_italic << "No classes" << w_end_italic << "                                       |" << std::endl;
    }
    day_printed = false;
    std::wcout << w_bold << L" ----------------------------------------------------" << w_end << std::endl;
    std::wcout << w_bold << L" ---------------------- TUESDAY ---------------------"  << w_end << std::endl;
    for (const auto &lec : lectures){
        if (lec.weekday() == "Tuesday") {
            std::wcout << L"| " << w_underline << convert_to_wstring(lec.uc_code()) << w_end
                       << std::wstring(10 - convert_to_wstring(lec.uc_code()).size(), L' ')
                       << L" (" << convert_to_wstring(lec.type()) << L")"
                       << std::wstring(3 - convert_to_wstring(lec.type()).size(), ' ') << L"|| "
                       << convert_to_wstring(better_representation(lec.start_hour())) << L" - "
                       << convert_to_wstring(better_representation(lec.end_hour()))
                       << L" (" << convert_to_wstring(better_representation(lec.duration())) << L")"
                       << std::wstring(14 - convert_to_wstring(better_representation(lec.duration())).size() -
                                       convert_to_wstring(better_representation(lec.end_hour())).size()
                                       - convert_to_wstring(better_representation(lec.start_hour())).size(), L' ')
                       << L" || " << convert_to_wstring(lec.class_code()) << std::wstring(8 - convert_to_wstring(lec.class_code()).size(), L' ')
                       << L"|" << std::endl;
            day_printed = true;
        }
    }
    if (!day_printed){
        std::wcout << L"|   " << w_italic << "No classes" << w_end_italic << "                                       |" << std::endl;
    }
    day_printed = false;
    std::wcout << w_bold << L" ----------------------------------------------------" << w_end << std::endl;
    std::wcout << w_bold << L" --------------------- WEDNESDAY --------------------"  << w_end << std::endl;
    for (const auto &lec : lectures){
        if (lec.weekday() == "Wednesday") {
            std::wcout << L"| " << w_underline << convert_to_wstring(lec.uc_code()) << w_end
                       << std::wstring(10 - convert_to_wstring(lec.uc_code()).size(), L' ')
                       << L" (" << convert_to_wstring(lec.type()) << L")"
                       << std::wstring(3 - convert_to_wstring(lec.type()).size(), ' ') << L"|| "
                       << convert_to_wstring(better_representation(lec.start_hour())) << L" - "
                       << convert_to_wstring(better_representation(lec.end_hour()))
                       << L" (" << convert_to_wstring(better_representation(lec.duration())) << L")"
                       << std::wstring(14 - convert_to_wstring(better_representation(lec.duration())).size() -
                                       convert_to_wstring(better_representation(lec.end_hour())).size()
                                       - convert_to_wstring(better_representation(lec.start_hour())).size(), L' ')
                       << L" || " << convert_to_wstring(lec.class_code()) << std::wstring(8 - convert_to_wstring(lec.class_code()).size(), L' ')
                       << L"|" << std::endl;
            day_printed = true;
        }
    }
    if (!day_printed){
        std::wcout << L"|   " << w_italic << "No classes" << w_end_italic << "                                       |" << std::endl;
    }
    day_printed = false;
    std::wcout << w_bold << L" ----------------------------------------------------" << w_end << std::endl;
    std::wcout << w_bold << L" --------------------- THURSDAY ---------------------"  << w_end << std::endl;
    for (const auto &lec : lectures){
        if (lec.weekday() == "Thursday") {
            std::wcout << L"| " << w_underline << convert_to_wstring(lec.uc_code()) << w_end
                       << std::wstring(10 - convert_to_wstring(lec.uc_code()).size(), L' ')
                       << L" (" << convert_to_wstring(lec.type()) << L")"
                       << std::wstring(3 - convert_to_wstring(lec.type()).size(), ' ') << L"|| "
                       << convert_to_wstring(better_representation(lec.start_hour())) << L" - "
                       << convert_to_wstring(better_representation(lec.end_hour()))
                       << L" (" << convert_to_wstring(better_representation(lec.duration())) << L")"
                       << std::wstring(14 - convert_to_wstring(better_representation(lec.duration())).size() -
                                       convert_to_wstring(better_representation(lec.end_hour())).size()
                                       - convert_to_wstring(better_representation(lec.start_hour())).size(), L' ')
                       << L" || " << convert_to_wstring(lec.class_code()) << std::wstring(8 - convert_to_wstring(lec.class_code()).size(), L' ')
                       << L"|" << std::endl;
            day_printed = true;
        }
    }
    if (!day_printed){
        std::wcout << L"|   " << w_italic << "No classes" << w_end_italic << "                                       |" << std::endl;
    }
    day_printed = false;
    std::wcout << w_bold << L" ----------------------------------------------------" << w_end << std::endl;
    std::wcout << w_bold << L" ---------------------- FRIDAY ----------------------"  << w_end << std::endl;
    for (const auto &lec : lectures){
        if (lec.weekday() == "Friday") {
            std::wcout << L"| " << w_underline << convert_to_wstring(lec.uc_code()) << w_end
                       << std::wstring(10 - convert_to_wstring(lec.uc_code()).size(), L' ')
                       << L" (" << convert_to_wstring(lec.type()) << L")"
                       << std::wstring(3 - convert_to_wstring(lec.type()).size(), ' ') << L"|| "
                       << convert_to_wstring(better_representation(lec.start_hour())) << L" - "
                       << convert_to_wstring(better_representation(lec.end_hour()))
                       << L" (" << convert_to_wstring(better_representation(lec.duration())) << L")"
                       << std::wstring(14 - convert_to_wstring(better_representation(lec.duration())).size() -
                                       convert_to_wstring(better_representation(lec.end_hour())).size()
                                       - convert_to_wstring(better_representation(lec.start_hour())).size(), L' ')
                       << L" || " << convert_to_wstring(lec.class_code()) << std::wstring(8 - convert_to_wstring(lec.class_code()).size(), L' ')
                       << L"|" << std::endl;
            day_printed = true;
        }
    }
    if (!day_printed){
        std::wcout << L"|   " << w_italic << "No classes" << w_end_italic << "                                       |" << std::endl;
    }
    std::wcout << w_bold << L" ----------------------------------------------------" << w_end << std::endl;
    day_printed = false;
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
    if (location == 3 || location == 4 || location == 6 || location == 11 || location == 13 || location == 14 || location == 15 || location == 17 || location == 18 || location == 19 || location == 22 || location == 23 || location == 25 || location == 27) {
        if (user_in == '\t' && ((!filtered_w_student_list.empty() && (location == 3 || location == 6 || location == 17 || location == 14 || location == 13 || location == 22 || location == 27))
                                || (!filtered_w_class_code_list.empty() && (location == 4 || location == 11 || location == 19 || location == 25))
                                || (!filtered_w_uc_list.empty() && (location == 15 || location == 18 || location == 23)))){
            table_mode = !table_mode;
            selected = 0;
            selected_in_page = 0;
        }
        if (user_in == 'n'){
            page ++;
            selected_in_page = 0;
            if(location == 3 || location == 6 || location == 14 || location == 17 || location == 22 || location == 27) {
                if (page >= booked_list.size()) {
                    page--;
                }
            }
            else{
                if (page >= booked_list_vector_of_wstrings.size()) {
                    page--;
                }
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
        if ((location == 3 || location == 6 || location == 22 || location == 27 || location == 17) && selected == 1) {
            if (user_in == 'C') {
                select_filter--;
                if (select_filter < 0) {
                    select_filter = student_sort_write.size() - 1;
                }
            }
            if (user_in == 'D') {
                select_filter ++;
                if (select_filter > student_sort_write.size() - 1) {
                    select_filter = 0;
                }
            }
        }
        if ((location == 4 || location == 11) && selected == 1) {
            if (user_in == 'C') {
                select_filter--;
                if (select_filter < 0) {
                    select_filter = class_sort_write.size() - 1;
                }
            }
            if (user_in == 'D') {
                select_filter ++;
                if (select_filter > class_sort_write.size() - 1) {
                    select_filter = 0;
                }
            }
        }
        if ((location == 15) && selected == 1) {
            if (user_in == 'C') {
                select_filter--;
                if (select_filter < 0) {
                    select_filter = uc_sort_write.size() - 1;
                }
            }
            if (user_in == 'D') {
                select_filter ++;
                if (select_filter > uc_sort_write.size() - 1) {
                    select_filter = 0;
                }
            }
        }
    }
    else{
        if (user_in == 'A' && (location == 3 || location == 6 || location == 14 || location == 17 || location == 22 || location == 27)) {
            if (selected_in_page > 0) { selected_in_page -= 1; }
            else { selected_in_page = booked_list[page].size() - 1; }
        }
        if (user_in == 'B' && (location == 3 || location == 6 || location == 14 || location == 17 || location == 22 || location == 27)){
            selected_in_page ++;
            if (selected_in_page > booked_list[page].size() - 1){selected_in_page = 0;}
        }
        if (user_in == 'A' && (location == 4 || location == 11 || location == 13 || location == 15 || location == 18 || location == 19 || location == 23 || location == 25)) {
            if (selected_in_page > 0) { selected_in_page -= 1; }
            else { selected_in_page = booked_list_vector_of_wstrings[page].size() - 1; }
        }
        if (user_in == 'B' && (location == 4 || location == 11 || location == 13 || location == 15 || location == 18 || location == 19 || location == 23 || location == 25)){
            selected_in_page ++;
            if (selected_in_page > booked_list_vector_of_wstrings[page].size() - 1){selected_in_page = 0;}
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
                        earlier_directory = directory;
                        directory += Options[location][selected];
                        selected = 0;
                        location = 20;
                        break;
                    case 2:
                        directory += Options[location][selected];
                        selected = 0;
                        location = 28;
                        break;
                    case 3:
                        location = -1;
                        break;
                    default:
                        break;
                }
                break;
            case 1:
                select_filter = 0;
                switch (selected){
                    case 0:
                        earlier_directory = directory;
                        directory += L" > " + Options[location][selected];
                        location = 2;
                        break;
                    case 1:
                        earlier_directory = directory;
                        directory += L" > " + Options[location][selected];
                        location = 6;
                        selected = 0;
                        break;
                    case 2:
                        earlier_directory = directory;
                        directory += L" > " + Options[location][selected];
                        location = 11;
                        selected = 0;
                        break;
                    case 4:
                        earlier_directory = directory;
                        directory += L" > " + Options[location][selected];
                        location = 26;
                        selected = 0;
                        break;
                    case 3:
                        earlier_directory = directory;
                        directory += L" > " + Options[location][selected];
                        location = 15;
                        selected = 0;
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
                        earlier_directory = directory;
                        directory += L" > " + Options[location][selected];
                        selected = 0;
                        location = 4;
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
                            case 1:
                                break;
                            case 2:
                                directory = L"Consult > Schedules";
                                location = 2;
                                selected = 0;
                                write = write_default;
                                break;
                            case 3:
                                location = 0;
                                selected = 0;
                                directory = L"";
                                write = write_default;
                                break;
                            default:
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 && selected_in_page < number_names[page == booked_list.size() - 1]) {
                                    s_analised = booked_list[page][selected_in_page].first + L"(" + booked_list[page][selected_in_page].second + L")";
                                    directory = L"Consult > Schedules > " + s_analised;
                                    location = 5;
                                    selected = 0;
                                    selected_in_page = 0;
                                    page = 0;
                                    write = write_default;
                                    table_mode = !table_mode;
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
                break;
            case 6:
                switch (table_mode){
                    case false:
                        switch (selected){
                            case 0:
                            case 1:
                            case 2:
                                break;
                            case 3:
                                directory = L"Consult";
                                location = 1;
                                selected = 0;
                                write = write_default;
                                write_n = write_default;
                                break;
                            case 4:
                                location = 0;
                                selected = 0;
                                directory = L"";
                                write = write_default;
                                write_n = write_default;
                                break;
                            default:
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 && selected_in_page < number_names[page == booked_list.size() - 1]) {
                                    s_analised = booked_list[page][selected_in_page].first + L"(" + booked_list[page][selected_in_page].second + L")";
                                    directory = L"Consult > " + s_analised;
                                    location = 7;
                                    selected = 0;
                                    selected_in_page = 0;
                                    page = 0;
                                    write = write_default;
                                    write_n = write_default;
                                    table_mode = !table_mode;
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
                break;
            case 4:
            case 11:
                switch (table_mode){
                    case false:
                        switch (selected){
                            case 0:
                            case 1:
                                break;
                            case 2:
                                location == 11 ? directory = L"Consult" : directory = L"Consult > Schedules";
                                location == 11 ? location = 1 : location = 2;
                                selected = 0;
                                write = write_default;
                                break;
                            case 3:
                                location = 0;
                                selected = 0;
                                directory = L"";
                                write = write_default;
                                break;
                            default:
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 && selected_in_page < number_names[page == booked_list_vector_of_wstrings.size() - 1]) {
                                    c_analised = booked_list_vector_of_wstrings[page][selected_in_page];
                                    earlier_directory.substr(0, 19) == L"Consult > Schedules" ? location = 9 : location = 10;
                                    earlier_directory = directory;
                                    location == 9 ? directory = L"Consult > Schedules > Class " + c_analised : directory = L"Consult > Class " + c_analised;;
                                    page = 0;
                                    selected = 0;
                                    selected_in_page = 0;
                                    write = write_default;
                                    table_mode = !table_mode;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Next Page ['n']") {
                                    page++;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Previous Page ['p']") {
                                    page--;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"First Page") {
                                    page = 0;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Last Page") {
                                    page = booked_list_vector_of_wstrings.size() - 1;
                                    selected_in_page = 0;
                                }
                        }
                        break;
                }
                break;
            case 5:
                switch (selected) {
                    case 0:
                        earlier_directory = directory;
                        directory = L"Consult > " + s_analised;
                        location = 7;
                        break;
                    case 1:
                        directory.substr(0, 19) == L"Consult > Schedules" ? location = 3 : location = 6;
                        location == 3 ? directory = L"Consult > Schedules > Students" : directory = L"Consult > Students";
                        selected = 0;
                        break;
                    case 2:
                        location = 0;
                        selected = 0;
                        directory = L"";
                        break;
                }
                break;
            case 7:
                switch (selected){
                    case 0:
                        earlier_directory = directory;
                        directory = L"Consult > " + s_analised + L" > Schedule";
                        location = 8;
                        break;
                    case 1:
                        earlier_directory = directory;
                        directory = L"Consult > " + s_analised + L" > Classes";
                        selected = 0;
                        location = 13;
                        break;
                    case 2:
                        earlier_directory = directory;
                        directory = L"Consult > " + s_analised + L" > UCs";
                        selected = 0;
                        location = 18;
                        break;
                    case 3:
                        earlier_directory.substr(0, 19) == L"Consult > Schedules" ? location = 5 : location = 6;
                        if (location == 6 && earlier_directory.substr(0, 15) == L"Consult > Class"){
                            location = 14;
                        }
                        if (location == 6 && earlier_directory.substr(0, 12) == L"Consult > UC"){
                            location = 17;
                        }
                        if (location == 6 && earlier_directory.substr(0, 12) == L"Consult > Ye"){
                            location = 27;
                        }
                        location == 5 ? directory = L"Consult > Schedules > " + s_analised : directory = L"Consult > Students";
                        if (location == 14){
                            directory = L"Consult > Class " + c_analised + L" > Students";
                        }
                        if (location == 17){
                            directory = L"Consult > UC " + uc_analised + L" > Students";
                        }
                        if (location == 27){
                            directory = earlier_directory;
                        }
                        earlier_directory = directory;
                        page = 0;
                        selected = 0;
                        break;
                    case 4:
                        location = 0;
                        selected = 0;
                        directory = L"";
                        break;
                    default:
                        break;
                }
                break;
            case 8:
                switch (selected) {
                    case 0:
                        earlier_directory = directory;
                        directory = L"Consult > " + s_analised ;
                        location = 7;
                        break;
                    case 1:
                        location = 0;
                        selected = 0;
                        directory = L"";
                        break;
                }
                break;
            case 9:
                switch (selected) {
                    case 0:
                        earlier_directory = directory;
                        directory = L"Consult > Class " + c_analised;
                        location = 10;
                        break;
                    case 1:
                        directory.substr(0, 19) == L"Consult > Schedules" ? location = 4 : location = 11;
                        location == 4 ? directory = L"Consult > Schedules > Classes" : directory = L"Consult > Classes";
                        earlier_directory = directory;
                        selected = 0;
                        break;
                    case 2:
                        location = 0;
                        selected = 0;
                        directory = L"";
                        break;
                }
                break;
            case 10:
                switch (selected) {
                    case 0:
                        earlier_directory = directory;
                        directory = L"Consult > Class " + c_analised + L" > Schedule";
                        location = 12;
                        break;
                    case 1:
                        selected = 0;
                        earlier_directory = directory;
                        directory = L"Consult > Class " + c_analised + L" > Students";
                        location = 14;
                        break;
                    case 2:
                        earlier_directory.substr(0, 19) == L"Consult > Schedules" ? location = 9 : location = 11;
                        if (location == 11 && earlier_directory.substr(0, 12) == L"Consult > UC"){
                            location = 19;
                        }
                        if (location == 11 && earlier_directory.substr(0, 15) != L"Consult > Class"){
                            location = 13;
                        }
                        earlier_directory = directory;
                        location == 9 ? directory = L"Consult > Schedules > Class " + c_analised : directory = L"Consult > Classes";
                        if (location == 19){
                            directory = L"Consult > " + uc_analised + L" > Classes";
                        }
                        if (location == 13){
                            directory = L"Consult > " + s_analised + L" > Classes";
                        }
                        page = 0;
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
            case 12:
                switch (selected) {
                    case 0:
                        earlier_directory = directory;
                        directory = L"Consult > Class " + c_analised ;
                        location = 10;
                        break;
                    case 1:
                        location = 0;
                        selected = 0;
                        directory = L"";
                        break;
                }
                break;
            case 13:
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 0:
                                earlier_directory = directory;
                                directory = L"Consult > " + s_analised;
                                location = 7;
                                break;
                            case 1:
                                location = 0;
                                selected = 0;
                                directory = L"";
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 && selected_in_page < number_names[page == booked_list_vector_of_wstrings.size() - 1]) {
                                    c_analised = booked_list_vector_of_wstrings[page][selected_in_page];
                                    directory = L"Consult > Class" + c_analised;
                                    page = 0;
                                    location = 10;
                                    selected = 0;
                                    selected_in_page = 0;
                                    write = write_default;
                                    table_mode = !table_mode;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Next Page ['n']") {
                                    page++;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Previous Page ['p']") {
                                    page--;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"First Page") {
                                    page = 0;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Last Page") {
                                    page = booked_list_vector_of_wstrings.size() - 1;
                                    selected_in_page = 0;
                                }
                        }
                        break;
                        break;
                }
                break;
            case 14:
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 0:
                                earlier_directory = directory;
                                directory = L"Consult > Class " + c_analised;
                                location = 10;
                                break;
                            case 1:
                                location = 0;
                                selected = 0;
                                directory = L"";
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 && selected_in_page < number_names[page == booked_list.size() - 1]) {
                                    s_analised = booked_list[page][selected_in_page].first + L"(" + booked_list[page][selected_in_page].second + L")";
                                    directory = L"Consult >  " + s_analised;
                                    page = 0;
                                    location = 7;
                                    selected = 0;
                                    selected_in_page = 0;
                                    write = write_default;
                                    table_mode = !table_mode;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Next Page ['n']") {
                                    page++;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Previous Page ['p']") {
                                    page--;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"First Page") {
                                    page = 0;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Last Page") {
                                    page = booked_list_vector_of_wstrings.size() - 1;
                                    selected_in_page = 0;
                                }
                        }
                        break;
                        break;
                }
                break;
            case 15:
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 0:
                            case 1:
                                break;
                            case 2:
                                location = 1;
                                selected = 0;
                                page = 0;
                                directory = L"Consult";
                                write = write_default;
                                break;
                            case 3:
                                location = 0;
                                selected = 0;
                                directory = L"";
                                write = write_default;
                                break;
                            default:
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 && selected_in_page < number_names[page == booked_list_vector_of_wstrings.size() - 1]) {
                                    uc_analised = booked_list_vector_of_wstrings[page][selected_in_page];
                                    location = 16;
                                    earlier_directory = directory;
                                    directory = L"Consult > UC " + uc_analised;
                                    page = 0;
                                    selected = 0;
                                    selected_in_page = 0;
                                    write = write_default;
                                    table_mode = !table_mode;
                                } else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Next Page ['n']") {
                                    page++;
                                    selected_in_page = 0;
                                } else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Previous Page ['p']") {
                                    page--;
                                    selected_in_page = 0;
                                } else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"First Page") {
                                    page = 0;
                                    selected_in_page = 0;
                                } else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Last Page") {
                                    page = booked_list_vector_of_wstrings.size() - 1;
                                    selected_in_page = 0;
                                }
                        }
                        break;
                }
                break;
            case 16:
                switch (selected){
                    case 0:
                        location = 17;
                        earlier_directory = directory;
                        directory = L"Consult > UC " + uc_analised + L" > Students";
                        selected = 0;
                        break;
                    case 1:
                        location = 19;
                        selected = 0;
                        earlier_directory = directory;
                        directory = L"Consult > UC " + uc_analised + L" > Classes";
                        break;
                    case 2:
                        location = 15;
                        earlier_directory = directory;
                        directory = L"Consult > UCs";
                        page = 0;
                        selected = 0;
                        break;
                    case 3:
                        location = 0;
                        selected = 0;
                        directory = L"";
                        break;
                }
                break;
            case 17:
                switch (table_mode){
                    case false:
                        switch (selected){
                            case 0:
                            case 1:
                                break;
                            case 2:
                                directory = L"Consult > UC " + uc_analised;
                                location = 16;
                                selected = 0;
                                write = write_default;
                                break;
                            case 3:
                                location = 0;
                                selected = 0;
                                directory = L"";
                                write = write_default;
                                break;
                            default:
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 && selected_in_page < number_names[page == booked_list.size() - 1]) {
                                    s_analised = booked_list[page][selected_in_page].first + L"(" + booked_list[page][selected_in_page].second + L")";
                                    earlier_directory = directory;
                                    directory = L"Consult > " + s_analised;
                                    location = 7;
                                    selected = 0;
                                    selected_in_page = 0;
                                    page = 0;
                                    write = write_default;
                                    table_mode = !table_mode;
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
                break;
            case 18:
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 0:
                                earlier_directory = directory;
                                directory = L"Consult > " + s_analised;
                                location = 7;
                                break;
                            case 1:
                                location = 0;
                                selected = 0;
                                directory = L"";
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 && selected_in_page < number_names[page == booked_list_vector_of_wstrings.size() - 1]) {
                                    uc_analised = booked_list_vector_of_wstrings[page][selected_in_page];
                                    directory = L"Consult >  UC " + uc_analised;
                                    page = 0;
                                    location = 16;
                                    selected = 0;
                                    selected_in_page = 0;
                                    write = write_default;
                                    table_mode = !table_mode;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Next Page ['n']") {
                                    page++;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Previous Page ['p']") {
                                    page--;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"First Page") {
                                    page = 0;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Last Page") {
                                    page = booked_list_vector_of_wstrings.size() - 1;
                                    selected_in_page = 0;
                                }
                        }
                        break;
                        break;
                }
                break;
            case 19:
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 0:
                                earlier_directory = directory;
                                directory = L"Consult > UC " + uc_analised;
                                location = 16;
                                break;
                            case 1:
                                location = 0;
                                selected = 0;
                                directory = L"";
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 && selected_in_page < number_names[page == booked_list_vector_of_wstrings.size() - 1]) {
                                    c_analised = booked_list_vector_of_wstrings[page][selected_in_page];
                                    directory = L"Consult >  Class " + c_analised;
                                    page = 0;
                                    location = 10;
                                    selected = 0;
                                    selected_in_page = 0;
                                    write = write_default;
                                    table_mode = !table_mode;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Next Page ['n']") {
                                    page++;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Previous Page ['p']") {
                                    page--;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"First Page") {
                                    page = 0;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Last Page") {
                                    page = booked_list_vector_of_wstrings.size() - 1;
                                    selected_in_page = 0;
                                }
                        }
                        break;
                        break;
                }
                break;
            case 20:
                switch (selected){
                    case 0:
                        location = 21;
                        earlier_directory = directory;
                        directory += L" > UC";
                        break;
                    case 1:
                        location = 22;
                        selected = 0;
                        earlier_directory = directory;
                        directory += L" > Switch Classes";
                        break;
                    case 2:
                        location = 0;
                        selected = 0;
                        directory = L"";
                        break;
                        break;
                }
                break;
            case 21:
                switch (selected){
                    case 0:
                        location = 22;
                        earlier_directory = directory;
                        directory += L" > Remove Student from UC";
                        break;
                    case 1:
                        location = 22;
                        selected = 0;
                        earlier_directory = directory;
                        directory += L" > Add Student to UC";
                        break;
                    case 2:
                        location = 20;
                        selected = 0;
                        earlier_directory = directory;
                        directory = L"Make change request";
                        break;
                    case 3:
                        location = 0;
                        selected = 0;
                        directory = L"";
                        break;
                }
                break;
            case 22:
                switch (table_mode){
                    case false:
                        switch (selected){
                            case 0:
                            case 1:
                                break;
                            case 2:
                                earlier_directory.substr(0, 24) == L"Make change request > UC" ? location = 21 : location = 20;
                                location == 21 ? directory = L"Make change request > UC" : directory = L"Make change request";
                                selected = 0;
                                write = write_default;
                                break;
                            case 3:
                                location = 0;
                                selected = 0;
                                directory = L"";
                                write = write_default;
                                break;
                            default:
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 && selected_in_page < number_names[page == booked_list.size() - 1]) {
                                    s_analised = booked_list[page][selected_in_page].first + L"(" + booked_list[page][selected_in_page].second + L")";
                                    if (directory.substr(0, 28) == L"Make change request > UC > R") {
                                        directory = L"Make change request > UC > Remove " + s_analised + L" from UC";
                                    }
                                    if (directory.substr(0, 28) == L"Make change request > UC > A") {
                                        directory = L"Make change request > UC > Add " + s_analised + L" to UC";
                                    }
                                    if (directory.substr(0, 23) == L"Make change request > S") {
                                        directory = L"Make change request > Switch " + s_analised + L" class";
                                    }
                                    location = 23;
                                    selected = 0;
                                    selected_in_page = 0;
                                    page = 0;
                                    write = write_default;
                                    table_mode = !table_mode;
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
                break;
            case 23:
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 0:
                                if (directory.substr(0, 28) == L"Make change request > UC > R") {
                                    directory = L"Make change request > UC > Remove Student from UC";
                                }
                                if (directory.substr(0, 28) == L"Make change request > UC > A") {
                                    directory = L"Make change request > UC > Add Student to UC";
                                }
                                if (directory.substr(0, 23) == L"Make change request > S") {
                                    directory = L"Make change request > Switch Classes";
                                }
                                location = 22;
                                break;
                            case 1:
                                location = 0;
                                selected = 0;
                                directory = L"";
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 && selected_in_page < number_names[page == booked_list_vector_of_wstrings.size() - 1]) {
                                    uc_analised = booked_list_vector_of_wstrings[page][selected_in_page];
                                    directory += L" " + uc_analised;
                                    page = 0;
                                    if (directory.substr(0, 28) == L"Make change request > UC > R") {
                                        location = 24;
                                    }
                                    if (directory.substr(0, 28) == L"Make change request > UC > A") {
                                        location = 25;
                                        directory += L" and to Class";
                                    }
                                    if (directory.substr(0, 23) == L"Make change request > S") {
                                        directory = L"Make change request > Switch " + s_analised + L" class " +
                                                    convert_to_wstring(app_.students_class_from_uc(convert_to_string((uc_analised)), get_student_by_id(app_.students())))
                                                    + L" to class";
                                        location = 25;
                                    }
                                    selected = 0;
                                    selected_in_page = 0;
                                    write = write_default;
                                    table_mode = !table_mode;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Next Page ['n']") {
                                    page++;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Previous Page ['p']") {
                                    page--;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"First Page") {
                                    page = 0;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Last Page") {
                                    page = booked_list_vector_of_wstrings.size() - 1;
                                    selected_in_page = 0;
                                }
                        }
                        break;
                }
                break;
            case 24:
                switch (selected) {
                    case 0:
                        earlier_directory = directory;
                        if (directory.substr(0, 23) == L"Make change request > S") {
                            directory = L"Make change request";
                            location = 20;
                        }
                        else {
                            directory = L"Make change request > UC";
                            location = 21;
                        }
                        break;
                    case 1:
                        location = 0;
                        selected = 0;
                        directory = L"";
                        break;
                }
                done = false;
                break;
            case 25:
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 0:
                                earlier_directory = directory;
                                if (directory.substr(0, 23) == L"Make change request > S") {
                                    directory = L"Make change request > Switch " + s_analised + L" class";
                                }
                                else {
                                    directory = L"Make change request > UC > Add " + s_analised + L" to UC";
                                }
                                location = 23;
                                break;
                            case 1:
                                location = 0;
                                selected = 0;
                                directory = L"";
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 && selected_in_page < number_names[page == booked_list_vector_of_wstrings.size() - 1]) {
                                    c_analised = booked_list_vector_of_wstrings[page][selected_in_page];
                                    directory += L" " + c_analised;
                                    page = 0;
                                    location = 24;
                                    selected = 0;
                                    selected_in_page = 0;
                                    write = write_default;
                                    table_mode = !table_mode;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Next Page ['n']") {
                                    page++;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Previous Page ['p']") {
                                    page--;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"First Page") {
                                    page = 0;
                                    selected_in_page = 0;
                                }
                                else if (booked_list_vector_of_wstrings[page][selected_in_page] == L"Last Page") {
                                    page = booked_list_vector_of_wstrings.size() - 1;
                                    selected_in_page = 0;
                                }
                        }
                        break;
                        break;
                }
                break;
            case 26:
                switch (selected){
                    case 0:
                    case 1:
                    case 2:
                        directory += L" > " + Options[location][selected];
                        location = 27;
                        selected = 0;
                        break;
                    case 3:
                        location = 1;
                        selected = 0;
                        directory = L"Consult";
                        break;
                    case 4:
                        location = 0;
                        selected = 0;
                        directory = L"";
                        break;
                }
                break;
            case 27:
                switch (table_mode){
                    case false:
                        switch (selected){
                            case 0:
                            case 1:
                                break;
                            case 2:
                                location = 26;
                                selected = 0;
                                directory = L"Consult > Year";
                                write = write_default;
                                break;
                            case 3:
                                location = 0;
                                selected = 0;
                                directory = L"";
                                write = write_default;
                                break;
                            default:
                                break;
                        }
                        break;
                    case true:
                        switch (selected_in_page) {
                            default:
                                if (selected_in_page >= 0 && selected_in_page < number_names[page == booked_list.size() - 1]) {
                                    s_analised = booked_list[page][selected_in_page].first + L"(" + booked_list[page][selected_in_page].second + L")";
                                    earlier_directory = directory;
                                    location = 7;
                                    directory = L"Consult > " + s_analised;
                                    selected = 0;
                                    selected_in_page = 0;
                                    page = 0;
                                    write = write_default;
                                    table_mode = !table_mode;
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
                break;
            case 28:
                switch (selected) {
                    case 0:
                        location = 29;
                        directory += L" > Revert change";
                        break;
                    case 1:
                        directory = L"";
                        location = 0;
                        selected = 0;
                        break;
                }
                break;
            case 29:
                switch (selected) {
                    case 0:
                        location = 28;
                        directory = L"History";
                        break;
                    case 1:
                        location = 0;
                        directory = L"";
                        selected = 0;
                }
                break;
            default:
                break;
        }
    }
//--------------------------------------------------------------------------------------------------------//
}

void Interface::InputResponse_inWriteMode(wchar_t &user_in) {
    if (location == 6 && selected == 2){
        if (isdigit(user_in)) {
            if (write_n == write_default) {
                write_n = L"";
            }
            write_n += user_in;
        }
        if (location == 6 && selected == 2) {
            if (write_n.size() > 1 && write_n != write_default) {
                write_n.pop_back();
            }
        }
        if ((user_in == 8 || user_in == 127) && write_n != write_default) {
            if (!write_n.empty()) {
                write_n.pop_back();
            }
        }
        if (write_n.empty()) {
            write_n = write_default;
        }
        page = 0;
    }
    else {
        if (isalpha(user_in) || isalnum(user_in) || (user_in >= 128 && user_in <= 255) || (ispunct(user_in))) {
            if (write == write_default) {
                write = L"";
            }
            write += user_in;
        }
        if (user_in == 32 && write != write_default) {
            write += L" ";
        }
        if ((user_in == 8 || user_in == 127) && write != write_default) {
            if (!write.empty()) {
                write.pop_back();
            }
        }
        if (write.empty()) {
            write = write_default;
        }
        page = 0;
        if (location == 4 || location == 11) {
            if (write.size() > 7 && write != write_default) {
                write.pop_back();
            }
        }
        if (location == 15 || location == 18 || location == 23) {
            if (write.size() > 8 && write != write_default) {
                write.pop_back();
            }
        }
        if (location == 3 || (location == 6 && selected == 0) || location == 17 || location == 22 || location == 27) {
            if (write.size() > 40 && write != write_default) {
                write.pop_back();
            }
        }
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
        else if ((user_input == 9 || (user_input == '\n')) && ((!filtered_w_student_list.empty() && (location == 3 || location == 6 || location == 17 || location == 22 || location == 27))
                                                               || (!filtered_w_class_code_list.empty() && (location == 4 || location == 11)) || (!filtered_w_uc_list.empty() && (location == 15 || location == 18 || location == 23)))){
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
    alphabetic_sort_vector_of_pairs_of_strings(student_list);
    w_student_list = convert_to_wstring_vector_of_pairs(student_list);
    class_code_list = app_.class_codes();
    alphabetic_sort_vector_of_strings(class_code_list);
    w_class_code_list = convert_to_wstring_vector_of_strings(class_code_list);
    uc_list = app_.ucs_codes();
    alphabetic_sort_vector_of_strings(uc_list);
    w_uc_list = convert_to_wstring_vector_of_strings(uc_list);

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
            case 7:                    // CONSULT STUDENT(name)
            case 10:                   // CONSULT CLASS(name)
            case 16:                   // CONSULT UC(name)
            case 20:                   // make change request
            case 21:                   // make change request > classes
            case 26:                    // consult year
                system("clear");
                print_directory();
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                inputer();
                break;
            case 3:                      // CONSULT SCHEDULE STUDENT
            case 6:                      // consult students
            case 22:                      // mkchr remove uc choose student
                system("clear");
                print_directory();
                if (location == 6){
                    if (write_n != write_default) {
                        save_filtered_w_student_list = convert_to_wstring_vector_of_pairs(
                                app_.students_in_n_ucs(std::stoi(write_n)));
                        Options[location][2] = L"Show students in at least " + write_n + L" UCs";
                    }
                    else{
                        save_filtered_w_student_list = convert_to_wstring_vector_of_pairs(
                                app_.students_in_n_ucs(0));
                        Options[location][2] = L"Show students in at least 0 UCs";
                    }
                }
                if (!write.empty() && write != write_default) {
                    Options[location][0] = L"Searching for: " + w_end + write + w_bold;
                } else {
                    Options[location][0] = L"Search for Student";
                }
                Options[location][1] = student_sort_write[select_filter];
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_Students << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_Sorts << w_end_italic << std::endl;
                if ((Options[location][selected].substr(0, 6) == L"Search" || (location == 6 && selected == 2)) && !table_mode) {
                    write_mode = true;
                }
                if (location != 6) {
                    booked_list_filter(w_student_list, filtered_w_student_list);
                    if (filtered_w_student_list.empty()) {
                        aditional_filter_students(w_student_list, select_filter);
                    } else {
                        aditional_filter_students(filtered_w_student_list, select_filter);
                    }
                }
                else{
                    booked_list_filter(save_filtered_w_student_list, filtered_w_student_list);
                    if (filtered_w_student_list.empty()) {
                        aditional_filter_students(save_filtered_w_student_list, select_filter);
                    } else {
                        aditional_filter_students(filtered_w_student_list, select_filter);
                    }
                }
                list_booker(filtered_w_student_list);
                booked_list_printer(filtered_w_student_list);
                inputer();
                break;
            case 4:                                                 // CONSULT SCHEDULE CLASS
            case 11:                                               // CONSULT CLASS
                system("clear");
                print_directory();
                Options[location][1] = class_sort_write[select_filter];
                if (!write.empty() && write != write_default) {
                    Options[location][0] = L"Searching for: " + w_end + write + w_bold;
                } else {
                    Options[location][0] = L"Search for Class";
                }
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_Classes << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_Sorts << w_end_italic << std::endl;
                if (Options[location][selected].substr(0, 6) == L"Search" && !table_mode) {
                    write_mode = true;
                }
                booked_list_filter_vector_of_wstrings(w_class_code_list, filtered_w_class_code_list);
                if (filtered_w_class_code_list.empty()) {
                    aditional_filter_classes(w_class_code_list, select_filter);
                }
                else{
                    aditional_filter_classes(filtered_w_class_code_list, select_filter);
                }
                list_booker_vector_of_wstrings(filtered_w_class_code_list);
                booked_list_printer_vector_of_wstrings(filtered_w_class_code_list);
                inputer();
                break;
            case 5: {   // CONSULT SCHEDULE STUDENT_NAME
                system("clear");
                Options[location][0] = L"More information about " + w_bold + s_analised + w_end;
                print_directory();
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                Schedule schedule = Schedule(get_student_by_id(app_.students()), app_.lectures());
                schedule_printer(schedule);
                inputer();
                break;
            }
            case 8: {                 // Consult Student(name) Schedule
                system("clear");
                print_directory();
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                Schedule schedule = Schedule(get_student_by_id(app_.students()), app_.lectures());
                schedule_printer(schedule);
                inputer();
                break;
            }
            case 9: {       // Consult schedule class(name)
                system("clear");
                Options[location][0] = L"More information about Class " + w_bold + c_analised + w_end;
                print_directory();
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                Class this_class = Class(convert_to_string(c_analised), app_.lectures(), app_.students());
                Schedule schedule = Schedule(this_class);
                schedule_printer(schedule);
                inputer();
                break;
            }
            case 12: {     // Consult class(name) schedule
                system("clear");
                print_directory();
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                Class this_class = Class(convert_to_string(c_analised), app_.lectures(), app_.students());
                Schedule schedule = Schedule(this_class);
                schedule_printer(schedule);
                inputer();
                break;
            }
            case 13:      //consult student(name) classes
                system("clear");
                filtered_w_class_code_list = convert_to_wstring_vector_of_strings(get_student_by_id(app_.students()).enrolled_classes_id());
                alphabetic_sort_vector_of_wstrings(filtered_w_class_code_list);
                print_directory();
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_Classes << w_end_italic << std::endl;
                list_booker_vector_of_wstrings(filtered_w_class_code_list);
                booked_list_printer_vector_of_wstrings(filtered_w_class_code_list);
                inputer();
                break;
            case 14: {         // consult class(name) students
                system("clear");
                Class this_class = Class(convert_to_string(c_analised), app_.lectures(), app_.students());;
                filtered_w_student_list = convert_to_wstring_vector_of_pairs(this_class.getEnrolledStudents());
                alphabetic_sort_vector_of_pairs_of_wstrings(filtered_w_student_list);
                print_directory();
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_Classes << w_end_italic << std::endl;
                list_booker(filtered_w_student_list);
                booked_list_printer(w_student_list);
                inputer();
                break;
            }
            case 15:                     //consul ucs
                system("clear");
                print_directory();
                Options[location][1] = uc_sort_write[select_filter];
                if (!write.empty() && write != write_default) {
                    Options[location][0] = L"Searching for: " + w_end + write + w_bold;
                } else {
                    Options[location][0] = L"Search for UC";
                }
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_UCs << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_Sorts<< w_end_italic << std::endl;
                if (Options[location][selected].substr(0, 6) == L"Search" && !table_mode) {
                    write_mode = true;
                }
                booked_list_filter_vector_of_wstrings(w_uc_list, filtered_w_uc_list);
                if (filtered_w_uc_list.empty()) {
                    aditional_filter_ucs(w_uc_list, select_filter);
                }
                else{
                    aditional_filter_ucs(filtered_w_uc_list, select_filter);
                }
                list_booker_vector_of_wstrings(filtered_w_uc_list);
                booked_list_printer_vector_of_wstrings(filtered_w_uc_list);
                inputer();
                break;
            case 17:                  //consult uc(name) students
                system("clear");
                save_filtered_w_student_list = convert_to_wstring_vector_of_pairs(app_.students_from_uc(convert_to_string(uc_analised)));
                alphabetic_sort_vector_of_pairs_of_wstrings(save_filtered_w_student_list);
                Options[location][1] = class_sort_write[select_filter];
                print_directory();
                if (!write.empty() && write != write_default) {
                    Options[location][0] = L"Searching for: " + w_end + write + w_bold;
                } else {
                    Options[location][0] = L"Search for Student";
                }
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_Students << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_Sorts<< w_end_italic << std::endl;
                if (Options[location][selected].substr(0, 6) == L"Search" && !table_mode) {
                    write_mode = true;
                }
                booked_list_filter(save_filtered_w_student_list, filtered_w_student_list);
                if (filtered_w_student_list.empty()) {
                    aditional_filter_students(w_student_list, select_filter);
                }
                else{
                    aditional_filter_students(filtered_w_student_list, select_filter);
                }
                list_booker(filtered_w_student_list);
                booked_list_printer(filtered_w_student_list);
                inputer();
                break;
            case 18:
            case 23:
                system("clear");
                if (location == 23 && (directory.substr(0, 28) == L"Make change request > UC > R" || directory.substr(0, 23) == L"Make change request > S") || location == 18) {
                    filtered_w_uc_list = convert_to_wstring_vector_of_strings(
                            get_student_by_id(app_.students()).enrolled_ucs_id());
                    alphabetic_sort_vector_of_wstrings(filtered_w_uc_list);
                }
                if(location == 23 && directory.substr(0, 28) == L"Make change request > UC > A") {
                    filtered_w_uc_list = convert_to_wstring_vector_of_strings(uc_list);
                }
                print_directory();
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_UCs << w_end_italic << std::endl;
                list_booker_vector_of_wstrings(filtered_w_uc_list);
                booked_list_printer_vector_of_wstrings(filtered_w_uc_list);
                inputer();
                break;
            case 19:
            case 25:      //make change request > uc > add to uc >> choose class
                system("clear");
                filtered_w_class_code_list = convert_to_wstring_vector_of_strings(app_.classes_from_uc(convert_to_string(uc_analised)));
                alphabetic_sort_vector_of_wstrings(filtered_w_class_code_list);
                print_directory();
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_Classes     << w_end_italic << std::endl;
                list_booker_vector_of_wstrings(filtered_w_class_code_list);
                booked_list_printer_vector_of_wstrings(filtered_w_class_code_list);
                inputer();
                break;
            case 24:
                system("clear");
                print_directory();
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                if (!done) {
                    if (directory.substr(0, 28) == L"Make change request > UC > R") {
                        feedback = convert_to_wstring(app_.remove_student_from_uc(
                                convert_to_string(s_analised.substr(s_analised.find_first_of(L'(') + 1, 9)),
                                convert_to_string(uc_analised),
                                app_.students_class_from_uc(convert_to_string((uc_analised)),
                                                            get_student_by_id(app_.students()))));
                    }
                    if (directory.substr(0, 28) == L"Make change request > UC > A") {
                        feedback = convert_to_wstring(app_.add_student_to_uc(
                                convert_to_string(s_analised.substr(s_analised.find_first_of(L'(') + 1, 9)),
                                convert_to_string(uc_analised),
                                convert_to_string(c_analised)));
                    }
                    if (directory.substr(0, 23) == L"Make change request > S") {
                        feedback = convert_to_wstring(app_.switch_student_class(convert_to_string(s_analised.substr(s_analised.find_first_of(L'(') + 1, 9)),
                                                                                convert_to_string(uc_analised),
                                                                                app_.students_class_from_uc(convert_to_string(uc_analised), get_student_by_id(app_.students())),
                                                                                convert_to_string(c_analised)));
                    }
                    done = true;
                }
                print_feedback(feedback);
                inputer();
                break;
            case 27:
                system("clear");
                print_directory();
                Options[location][1] = student_sort_write[select_filter];
                if (directory == L"Consult > Year > First year"){
                    save_filtered_w_student_list = convert_to_wstring_vector_of_pairs(app_.check_year("1"));
                }
                if (directory == L"Consult > Year > Second year"){
                    save_filtered_w_student_list = convert_to_wstring_vector_of_pairs(app_.check_year("2"));
                }
                if (directory == L"Consult > Year > Third year"){
                    save_filtered_w_student_list = convert_to_wstring_vector_of_pairs(app_.check_year("3"));
                }
                alphabetic_sort_vector_of_pairs_of_wstrings(save_filtered_w_student_list);
                if (!write.empty() && write != write_default) {
                    Options[location][0] = L"Searching for: " + w_end + write + w_bold;
                } else {
                    Options[location][0] = L"Search for Student";
                }
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_Students << w_end_italic << std::endl;
                std::wcout << w_italic << Helper_Sorts<< w_end_italic << std::endl;
                if (Options[location][selected].substr(0, 6) == L"Search" && !table_mode) {
                    write_mode = true;
                }
                booked_list_filter(save_filtered_w_student_list, filtered_w_student_list);
                if (filtered_w_student_list.empty()) {
                    aditional_filter_students(w_student_list, select_filter);
                }
                else{
                    aditional_filter_students(filtered_w_student_list, select_filter);
                }
                list_booker(filtered_w_student_list);
                booked_list_printer(w_student_list);
                inputer();
                break;
            case 28:
                system("clear");
                if (convert_to_wstring(app_.get_latest_change()[0]) == L"SWITCH") {
                    Options[location][0] = L"Revert switch " + convert_to_wstring(get_student_by_id_with_parameters(app_.students(), convert_to_wstring(app_.get_latest_change()[1])).student_name())
                                           + L"(" + convert_to_wstring(app_.get_latest_change()[1]) + L") from Class "
                                           + convert_to_wstring(app_.get_latest_change()[3]) + L" to Class " + convert_to_wstring(app_.get_latest_change()[4]);
                }
                if (convert_to_wstring(app_.get_latest_change()[0]) == L"REMOVEFROMUC") {
                    Options[location][0] = L"Revert removing of " + convert_to_wstring(get_student_by_id_with_parameters(app_.students(), convert_to_wstring(app_.get_latest_change()[1])).student_name())
                                           + L"(" + convert_to_wstring(app_.get_latest_change()[1]) + L") from UC "
                                           + convert_to_wstring(app_.get_latest_change()[3]);
                }
                if (convert_to_wstring(app_.get_latest_change()[0]) == L"ADDTOUC") {
                    Options[location][0] = L"Revert addition of " + convert_to_wstring(get_student_by_id_with_parameters(app_.students(), convert_to_wstring(app_.get_latest_change()[1])).student_name())
                                           + L"(" + convert_to_wstring(app_.get_latest_change()[1]) + L") to UC "
                                           + convert_to_wstring(app_.get_latest_change()[3]) + L" class " + convert_to_wstring(app_.get_latest_change()[4]);
                }
                if (convert_to_wstring(app_.get_latest_change()[0]) == L"There are no changes"){
                    Options[location][0] = L"There are no changes";
                }
                print_directory();
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                inputer();
                break;
            case 29:
                system("clear");
                print_directory();
                print_options();
                std::wcout << L"\n\n" << w_italic << Helper << w_end_italic << std::endl;
                std::wcout << L"\n\n===================[  " << convert_to_wstring(app_.reverse_change()) << L"  ]====================" << std::endl;
                inputer();
                break;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //restore old terminal
    system("clear");
}