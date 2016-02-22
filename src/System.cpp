#include "System.h"

System::System(std::vector<Function>arrF, std::vector<double> x, double epsilon)
{
    this->arrF=arrF;
    setX(x);
    setEpsilon(epsilon);
    setArrDerivative();
    setArrValue();
    epsilon=0;
    setDx();
}

void System::setArrDerivative()
{
    arrDerivative.resize(arrF.size());
    for(unsigned int i=0; i<arrF.size(); ++i)
    {
        arrDerivative[i].resize(arrF.size());
        for(unsigned int j=0; j<arrF.size(); ++j)
            arrDerivative[i][j]=getDerivative(i,j);
    }

}

double System::getDerivative(const unsigned int i,unsigned int j)
{
    std::vector<double> temp=x;
    //for(unsigned k=0;k<temp.size();++k)
    temp[j]+=epsilon;
    double t=(arrF[i].getValue(temp)-arrF[i].getValue(x))/epsilon;
    return t;
}

void System::setArrValue()
{
    arrValue.resize(arrF.size());
    for(unsigned int i=0; i<arrF.size(); ++i)
        arrValue[i]=arrF[i].getValue(x);
}

void System::setX(std::vector<double> x)
{
    this->x=x;
}

void System::setEpsilon(double epsilon)
{
    this->epsilon=epsilon;
}

void System::setDx()
{
    dx.resize(arrF.size());
    for(unsigned int i=0; i<arrF.size(); ++i)
    {
        dx[i]=0;
    }
}

double System::getDet(std::vector<std::vector<double>> a)
{
    unsigned int i,j;
    std::vector<std::vector<double>> temp;
    double determ=0;
    if (a.size()==2)
    {
        determ=a[0][0]*a[1][1]-a[0][1]*a[1][0];
    }
    else
    {
        temp.resize(a.size()-1);

        for(i=0; i<a.size(); i++)
        {
            for(j=0; j<temp.size(); j++)
            {
                if(j<i)
                {
                    temp[j]=a[j];
                }
                else
                {
                    temp[j]=a[j+1];
                }
            }
            determ+=pow(-1,(i+j))*getDet(temp)*a[i][temp.size()];
        }
        temp.clear();
    }
    return determ;
}

std::vector<double> System::getX()
{
    return x;
}

void System::solveKramerDx()
{
    double det=-getDet(arrDerivative);
    for(unsigned int i=0; i<dx.size(); ++i)
    {
        std::vector<std::vector<double>> temp=arrDerivative;
        temp[i]=arrValue;
        dx[i]=getDet(temp)/det;
    }
}

bool System::isAbsDxLessEpsilon()
{
    std::vector<double>::const_iterator largest = max_element( dx.begin(), dx.end() );
    double k=*largest;
    if(fabs(k)<epsilon) return false;
    return true;
}

void System::solveSystem()
{
    do
    {
        for(unsigned int i=0; i<x.size(); ++i)
            x[i]+=dx[i];
        setArrDerivative();
        setArrValue();
        solveKramerDx();
    }
    while(isAbsDxLessEpsilon());
}

std::vector<double> System::getResult()
{
    return x;
}
