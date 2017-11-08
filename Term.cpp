#include "Term.hpp"

Term::Term() {}

Term::Term(std::string var) {
    _var = var;
    _term = std::stod(_var, &_sz);
    _pow = int((_var[_var.length() - 1]) - '0');
}

Term::Term(Term const &rhs) {
    _term = rhs._term;
    _pow = rhs._pow;
}

Term & Term::operator=(Term const &rhs) {
    if(this != &rhs) {
        _term = rhs._term;
        _pow = rhs._pow;
    }
    return *this;
}

Term::~Term() {}

double Term::getTerm() {
    return _term;
}

int Term::getPow() {
    return _pow;
}