//
// Created by alexandre on 10-10-2023.
//

#ifndef AED_PROJECT_UC_H
#define AED_PROJECT_UC_H

#include <string>
#include <vector>
#include "Class.h"

class UC {
private:
    std::string uc_code_;
    std::vector<Class> classes_;
public:
    UC(const std::string &uc_code, const std::vector<Class> &classes);
    std::vector<Class> classes() const;
    std::string &uc_code();
    std::vector<Class> &classes();
    std::string uc_code() const;
};


#endif //AED_PROJECT_UC_H
