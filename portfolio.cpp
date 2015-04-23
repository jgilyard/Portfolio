#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include "stock.cpp"
#include <iostream>

using namespace std;

class portfolio{

public:
portfolio(int s, int in)
{
size = s;
industry = in; 
group = new stock [size];
}
portfolio()
{
}
stock *group;
void set_in(int in){industry = in;} 
void set_s(int s){size = s;}
int get_in(){return industry;}
int get_s(){return size;}
void set_group(int in)
{
group = new stock[in];
}
private:
int industry;
int size;




};
#endif
