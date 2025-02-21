//
// Created by Emil Watz on 21.02.2025.
//

#ifndef DIMACSFORMATEXCEPTION_H
#define DIMACSFORMATEXCEPTION_H
#include <stdexcept>


class DimacsFormatException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};



#endif //DIMACSFORMATEXCEPTION_H
