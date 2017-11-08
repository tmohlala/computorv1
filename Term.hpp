#ifndef TERM_HPP
#define TERM_HPP

#include <string>
#include <algorithm>
#include <iostream>
#include <string.h>

class Term {
    Term();
    std::string _var;
    double _term;
    double _pow;
    std::string::size_type _sz;

public:
    Term(std::string var);
    Term(Term const &rhs);
    Term & operator=(Term const &);
    ~Term();

    double getTerm();
    int getPow();
};

#endif