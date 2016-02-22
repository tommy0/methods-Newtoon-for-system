#include "Output.h"

void output(std::vector<double> x)
{
    for(unsigned int i=0; i<x.size(); ++i)
    {
        std::cout<<x[i]<<" ";
    }
}
