Student Interface::get_student_by_id(const std::set<Student>& v){
    auto it = std::find_if(v.begin(), v.end(), [this](const Student &s) {
        return convert_to_wstring(s.student_code()) == s_analised.substr(s_analised.find_first_of(L'(') + 1, 9);
    });
    if (it != v.end()) return *it;
}//
// Created by alexandre on 05-11-2023.
//
