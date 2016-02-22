#include "Input.h"

double f1(std::vector<double> inX)
{
    return sin(inX[0])-inX[1]-1.32;
}

double f2(std::vector<double> inX)
{
    return cos(inX[1])-inX[0]+0.85;
}

void inputX(std::vector<double> &x,int xsize)
{
    std::cout<<"Enter starts roots: ";
    for(unsigned int i=0; i<xsize;++i)
    {
        double temp;
        std::cin>>temp;
        x.push_back(temp);
    }
}

void inputEpsilon(double &epsilon)
{
    std::cout<<"Enter epsilon: ";
    std::cin>>epsilon;
}
