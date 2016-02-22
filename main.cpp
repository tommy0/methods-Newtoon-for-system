#include "Function.h"
#include "System.h"
#include "Input.h"
#include "Output.h"

int main()
{
    Function first(f1);
    Function second(f2);
    std::vector<double> x;
    std::vector<double> result;
    double epsilon;
    std::vector<Function> functions ={first, second};
    inputX(x,functions.size());
    inputEpsilon(epsilon);
    System equation(functions,x,epsilon);
    equation.solveSystem();
    result=equation.getResult();
    output(result);
    return 0;
}

