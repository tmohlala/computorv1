#include "Computorv1.hpp"

Computorv1::Computorv1() {}

Computorv1::Computorv1(std::string equation): _equation(equation) {
    transform(_equation.begin(), _equation.end(), _equation.begin(), ::toupper);
    _a = 0;
    _b = 0;
    _c = 0;
    _i = 0;
    _flag = 0;
    _maxPow = 0;
    _minPow = 0;
    _alpha = 0;
    _beta1 = 0;
    _beta2 = 0;
}

Computorv1::Computorv1(Computorv1 const &rhs): _equation(rhs._equation) {}

Computorv1::~Computorv1() {}

Computorv1 & Computorv1::operator=(Computorv1 const &rhs) {
    if(this != &rhs) {
        _equation = rhs._equation;
    }
    return *this;
}

void Computorv1::readEquation() {
    if(_equation.find("=") != std::string::npos){
        std::vector<std::string> temp;
        std::string sign = "+";
        temp = split(delSpaces(_equation), "=");
        _lhsSigns = split(temp[0], "0123456789.X^* ");
        _rhsSigns = split(temp[1], "0123456789.X^* ");
        _rhs = split(temp[1], "+-");
        _lhs = split(temp[0], "+-");
        if(_lhs.size() != _lhsSigns.size()) {
            _lhsSigns.insert(_lhsSigns.begin(), sign);
        }
        if(_rhs.size() != _rhsSigns.size()) {
            _rhsSigns.insert(_rhsSigns.begin(), sign);
        }
    }
    else {
        _flag = 1;
        std::cout << "Invalid equation" << std::endl;
    }
}

void Computorv1::term() {
    for(size_t i = 0; i < _lhs.size(); i++) {
        std::string sign = checkSigns(i, 1);
        Term obj(sign + _lhs[i]);
        if(std::find(_exponent.begin(), _exponent.end(), obj.getPow()) != _exponent.end()) {
            size_t i = 0;
            while(_exponent[i] != obj.getPow()) {
                i++;
            }
            if(obj.getPow() == _exponent[i]) {
                _term[i] += obj.getTerm();
            }
        }
        else {
            _exponent.push_back(obj.getPow());
            _term.push_back(obj.getTerm());
        }
    }
    for(size_t i = 0; i < _rhs.size(); i++) {
        std::string sign = checkSigns(i, 0);
        if(sign == "+") {
            sign = "-";
        }
        else {
            sign = "+";
        }
        Term obj(sign + _rhs[i]);
        if(std::find(_exponent.begin(), _exponent.end(), obj.getPow()) != _exponent.end()) {
            size_t i = 0;
            while(_exponent[i] != obj.getPow()) {
                i++;
            }
            if(obj.getPow() == _exponent[i]) {
                _term[i] += obj.getTerm();
            }
        }
        else {
            if(obj.getPow() > _maxPow) {
                _maxPow = obj.getPow();
            }
            _exponent.push_back(obj.getPow());
            _term.push_back(obj.getTerm());
        }
    }
    _expSeq = _exponent;
    std::sort(_expSeq.begin(), _expSeq.end());
}

void Computorv1::senitizeTerm() {
    for(size_t i = 0; i < _exponent.size(); i++) {
        if(_term[i] == 0) {
            _exponent.erase(_exponent.begin() + i);
            _term.erase(_term.begin() + i);
        }
        if(_maxPow < _exponent[i] && _term[i] != 0) {
            _maxPow = _exponent[i];
        }
    }
}

size_t Computorv1::printIndex() {
    size_t i;
    size_t j = _exponent.size();
    for(i = 0; i < j; i++) {
        if(_exponent[i] == _expSeq[_i]) {
            _i++;
            break;
        }  
    }
    return i;
 }

void Computorv1::printReducedForm() {
    term();
    size_t j;
    if(_exponent.size() > 0) {
        double temp;
        senitizeTerm();
        for(size_t i = 0; i < _exponent.size(); i++) {
            if(i == 0) {
                std::cout << "Reduced form: ";
            }
            j = printIndex();
            std::string sign = "";
            temp = _term[j];
            if(i == 0 && temp < 0) {
                sign = ""; 
            }
            else if(temp > 0 && i > 0) {
                sign = "+";
            }
            else if(temp < 0 && i > 0) {
                temp = _term[j];
                temp *= -1;
                sign = "-";
            }
            std::cout << sign<< " " << temp << " * X^" << _exponent[j] << " ";
        }
        if(_exponent.size() > 0)
            std::cout << "= 0" << std::endl;
    }
    if(!_flag) {
        printSolution();
    }
}

std::vector<std::string> Computorv1::split(std::string input, std::string substr) {
    std::vector<std::string> terms ; //Use vector to add the words
    
        std::size_t prev_pos = 0, pos;
        while ((pos = input.find_first_of(substr, prev_pos)) != std::string::npos)
        {
            if (pos > prev_pos)
                terms.push_back(input.substr(prev_pos, pos-prev_pos));
            prev_pos= pos+1;
        }
        if (prev_pos < input.length())
            terms.push_back(input.substr(prev_pos, std::string::npos));
        return (terms);
}

std::string Computorv1::checkSigns(size_t pos, bool flag) {
    if(flag)
        return (_lhsSigns[pos]);
    return (_rhsSigns[pos]);
}

void Computorv1::assign() {
    if(_maxPow == 2 || _maxPow == 1) {
        for(size_t i = 0; i < _exponent.size(); i++) {
            if(_exponent[i] == 0) {
                _c = _term[i];
            }
            else if(_exponent[i] == 1) {
                _b = _term[i];
            }
            else {
                _a = _term[i];
            }
        }
    }
}

void Computorv1::solveEquation() {
    int disc = checkDiscriminant(_a, _b, _c);
    if(disc < 0) {
        _alpha = (_b * -1.0) / (2.0 * _a);
        _beta1 = sqrt((_b * _b) - (4.0 * _a * _c * -1.0)) / (2.0 * _a);
        _beta2 = - sqrt((_b * _b) - (4.0 * _a * _c * -1.0)) / (2.0 * _a);
    }
    if(_a != 0) {
        _sol1 = ((_b * -1.0) + sqrt((_b * _b) - (4.0 * _a * _c))) / (2.0 * _a);
        _sol2 = ((_b * -1.0) - sqrt((_b * _b) - (4.0 * _a * _c))) / (2.0 * _a);
    }

    if(_a == 0) {
        if(_c != 0)
            _c *= -1;
        _sol1 = _c / _b;
    }
}

int Computorv1::checkDiscriminant(double a, double b, double c) {
    double disc = (b * b) - (4 * a * c);
    if(disc > 0) {
        return 1;
    }
    else if(disc < 0) {
        return -1;
    }
    return 0;
}

void Computorv1::printSolution() {
    assign();
    if(_maxPow == 2) {
        int disc = checkDiscriminant(_a, _b, _c);
        if(disc > 0) {
            std::cout << "Polynomial degree: 2" << std::endl;
            std::cout << "Discriminant is strictly positive, the two solution are:" << std::endl;
            solveEquation();
            std::cout << _sol1 << std::endl;
            std::cout << _sol2 << std::endl;
        }
        else if(disc == 0) {
            std::cout << "Polynomial degree: 2" << std::endl;
            std::cout << "Discriminant has a repeated solution, the solution is:" << std::endl;
            solveEquation();
            std::cout << _sol1 << std::endl;
            //std::cout << _sol2 << std::endl;
        }
        else {
            std::cout << "Polynomial degree: 2" << std::endl;
            std::cout << "Discriminant has no real roots" << std::endl;
            solveEquation();
            std::cout << _alpha << " + " << _beta1 << " * i"<< std::endl;
            std::cout << _alpha << " - " << (_beta2 * -1) << " * i" << std::endl;
        }
    }
    else if(_maxPow == 1) {
        std::cout << "Polynomial degree: 1" << std::endl;
        solveEquation();
        std::cout << _sol1 << std::endl;
    }
    else if(_maxPow > 2){
        std::cout << "Polynomial degree: " << _maxPow << std::endl;
        std::cout << "The polynomial degree is strictly greater than 2, can't solve" << std::endl;
    }
    else if(_maxPow == 0 && _term[0] == 0) {
        std::cout << "All real numbers are a solution" << std::endl;
    }
    else if(_maxPow == 0 && _term[0] != 0) {
        std::cout << "The equation has no solutions" << std::endl;
    }
}

std::string Computorv1::delSpaces(std::string &str) {
   str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
   return str;
}

double Computorv1::sqrt(double square)
{
    double root = square/3;
    int i;
    if (square <= 0) return 0;
    for (i = 0; i < 32; i++)
        root = (root + square / root) / 2;
    return root;
}

/* * * * * * * * * * * *
 * Used for debugging 
 * * * * * * * * * * * */

template <typename T>
void Computorv1::Print (const std::vector<T> v){
    for (size_t i = 0; i < v.size(); i++){
      std::cout << v[i] << std::endl;
    }
}