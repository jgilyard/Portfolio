#ifndef OLS_H
#define STOCK_H
#include "../stock.cpp"
#include <iostream>
#define STOCK_SIZE 100
//#include <array>
using namespace std;

class OLS{
public:

void set_sum(double s){OLS_sum = s;}
void set_dot(double d){OLS_dot= d;}
double sum(double array[]);
double dot(double array[], double array_2[]);
void regression(double array[], double array_2[]);
double get_sum(){return OLS_sum;}
double get_dot(){return OLS_dot;}
double get_beta(){return beta;}
double get_alpha(){return alpha;}
private:
double OLS_sum;
double OLS_dot;
double beta;
double alpha; 
};

double OLS::sum(double array[])
{
double temp = 0;
for( int i = 0; i < STOCK_SIZE; i++)
    {
    temp = array[i] + temp;
    }
OLS_sum = temp;
return temp;
}

double OLS::dot(double array[], double array_2[])
{
double temp = 0;
double holder = 0;
for (int i =0; i <STOCK_SIZE;i++)
    {
    holder = array[i]*array_2[i];
    temp = holder + temp;
    }
OLS_dot = temp;
return temp;
}

void OLS::regression(double array[], double array_2[])
{
double x = sum(array)/STOCK_SIZE;
cout <<"x"<<x<<endl;
double y = sum(array_2)/STOCK_SIZE;
cout <<"y"<<y<<endl;
double sxy = dot(array,array_2)/STOCK_SIZE - (x*y)/STOCK_SIZE;
double sxx = dot(array_2, array_2)- (x*x)/STOCK_SIZE;

cout <<"sxy"<<sxy<<endl;
cout <<"sxx"<<sxx<<endl;
beta = (sxy/sxx);
alpha = y - beta*x;
}

#endif
