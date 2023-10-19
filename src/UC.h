//
// Created by alexandre on 10-10-2023.
//

#ifndef AED_PROJECT_UC_H
#define AED_PROJECT_UC_H

#include <string>
#include <vector>
#include <list>
#include "Class.h"

class UC {
private:
    std::string uc_code_;
    std::list<Class *> classes_;
public:
    UC(const std::string &uc_code, const std::list<Class *> &classes);
    const std::list<Class *> &classes() const;
    void removeClass(Class *c);
    void printClasses();
    std::string uc_code() const;
};


#endif //AED_PROJECT_UC_H
