//
// Created by alexandre on 10-10-2023.
//

#ifndef AED_PROJECT_UC_H
#define AED_PROJECT_UC_H

#include <string>
#include <vector>
#include <list>
#include <memory>
#include "Class.h"
#include "Student.h"

class UC {
private:
    std::string uc_code_;
    std::list<std::shared_ptr<Class>> classes_;
    std::list<std::shared_ptr<Student>> enrolled_students_;
public:
    UC(const std::string &uc_code, const std::list<std::shared_ptr<Class>> &classes,
       const std::list<std::shared_ptr<Student>> &enrolled_students);
    const std::list<std::shared_ptr<Class>> &classes() const;
    void removeClass(std::shared_ptr<Class> c);
    void printClasses();
    std::string uc_code() const;
};


#endif //AED_PROJECT_UC_H
