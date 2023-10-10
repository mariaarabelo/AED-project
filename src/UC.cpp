//
// Created by alexandre on 10-10-2023.
//

#include "UC.h"

#include <string>
#include <vector>


UC::UC(const std::string &uc_code, const std::vector<Class> &classes) {
    this->uc_code = uc_code;
    this->classes = classes;
}