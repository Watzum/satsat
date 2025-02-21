//
// Created by Emil Watz on 16.02.2025.
//

#ifndef DIMACS_H
#define DIMACS_H

#include <string>

namespace dimacs {
    long to_positive_long(const std::string&);
    void ignore_whitespaces(std::ifstream&);
}



#endif //DIMACS_H
