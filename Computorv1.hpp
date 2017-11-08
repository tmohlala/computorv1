#ifndef COMPUTORV1_HPP
# define COMPUTORV1_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include "Term.hpp"

class Computorv1 {
    double _a;
    double _b;
    double _c;
    double _sol1;
    double _sol2;
    double _alpha;
    double _beta1;
    double _beta2;
    int    _maxPow;
    int    _minPow;
    int    _flag;
    size_t _i;
    std::vector<int> _expSeq;
    std::vector<double> _term;
    std::vector<int> _exponent;
    std::vector<std::string> _lhs;
    std::vector<std::string> _rhs;
    std::vector<std::string> _lhsSigns;
    std::vector<std::string> _rhsSigns;
    std::string _equation;
    Computorv1();
public:
    Computorv1(std::string equation);
    Computorv1(Computorv1 const &rhs);
    Computorv1 & operator=(Computorv1 const &rhs);
    ~Computorv1();

    std::string checkSigns(size_t pos, bool flag);
    void assign();
    size_t printIndex();
    double sqrt(double sqrt);
    void readEquation();
    void printForm();
    void term();
    void senitizeTerm();
    void printReducedForm();
    void printSolution();
    int checkDiscriminant(double a, double b, double c);
    void solveEquation();
    std::string delSpaces(std::string &str);
    std::vector<std::string> split(std::string input, std::string substr);
    template <typename T>
    void Print (const std::vector<T> v);    
};


#endif