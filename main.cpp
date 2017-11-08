#include "Computorv1.hpp"

int main(int argc, char **argv) {
   
    if(argc == 2) {
        Computorv1 obj(argv[1]);
        obj.readEquation();
        obj.printReducedForm();
    }
    return 0;
}