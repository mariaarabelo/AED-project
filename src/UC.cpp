//
// Created by alexandre on 10-10-2023.
//

#include "UC.h"

#include <string>
#include <vector>


UC::UC(const std::string &uc_code, const std::vector<Class> &classes) {
    this->uc_code_ = uc_code;
    this->classes_ = classes;
}

std::string UC::uc_code()  const{
    return uc_code_;
}

std::vector<Class> UC::classes() const {
    return classes_;
}

std::string &UC::uc_code() {
    return this->uc_code_;
}

std::vector<Class> &UC::classes() {
    return this->classes_;
}
