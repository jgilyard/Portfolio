#ifndef SINGLE_STOCK_LIST_H
#define SINGLE_STOCK_LIST_H
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include"portfolio.cpp"
#include <time.h>
#define PAGE_LENGTH 25
#define DEFAULT 1
#include <math.h>
using namespace std;



class single_stock_list{

public:
void csv_reader();

single_stock_list(string name)
    {
    string ending;
    ending = ".csv";
    file_name = "markets/";
    file_name = file_name +name;
    file_name = file_name + ending;
    csv_reader();
    market_name = name;
    //my_port.set_group(PAGE_LENGTH);
    stock_browse();
    //portfolio_counter = 0;
    //25 at a time browse
    }
void stock_browse();
string url_prep();
string get_python(){return python_sub;}
stock changer;
private:
info *list;
string file_name; 
string market_name;
string python_sub;
int line_number;

};


void single_stock_list::csv_reader()
{
line_number = 0;
string line;
std::ifstream inFile(file_name.c_str());
//Allows for strings to be passed
while(getline(inFile,line))
    {
    line_number++;

    }   
cout <<"line number: " << line_number <<endl;
list = new info[line_number];
inFile.close();
inFile.open(file_name.c_str());
int iter = 0;
//array technically begin at list[1]-list[line_number]
while(getline(inFile,list[iter].symbol, ','))
    {
    getline(inFile, list[iter].name);
    //cout << "Company Name: "<<list[iter].name<<endl;
    //cout <<"Ticker: " <<list[iter].symbol <<endl;
    iter++;
    if(iter == line_number)
    {
    break;
    //prevents seg fault
    }
    }
cout <<"MARKET SUCCUESSFULLY LOADED"<<endl;
}


string single_stock_list::url_prep()
{
    string python_url;
//portfolio my_port(PAGE_LENGTH,DEFAULT)
    python_url = python_url + changer.get_symbol();
    python_sub = changer.get_symbol();
return python_url;   
}


void single_stock_list::stock_browse()
{
int num_pages = ceil(line_number/PAGE_LENGTH);
cout << "Number of Pages to View Stocks " << num_pages <<endl;
//portfolio my_port(PAGE_LENGTH,DEFAULT);
for(int i =1; i<line_number; i++)
    {
    int prev_page = i ; 
    cout << "Stock Number " << i <<endl;
    cout << "Company Name: " << list[i].name <<endl;
    cout << "Ticker: "<< list[i].symbol <<endl;
    cout << endl;
    if (i % PAGE_LENGTH ==0)
        {
        cout <<"You May View up 25 stocks per page"<<endl;
        cout <<"Would you like to look at the next 25 stocks?"<<endl;
        cout <<"If so, Press Y, P to select that stock, X to exit" <<endl;
        string answer;
        cin >>answer;
            while(answer != "Y"&& answer != "X" && answer != "P")
            {
            cout <<"Please Select either Y, P or X"<<endl;
            cin >>answer;
                if(answer =="Y"|| answer == "X")
                {
                break;
                }
            }
            
            if(answer == "P")
            {
            cout<<"Please enter which stock number you would like to analyze"<<endl;
            int port_number;
            cin >>port_number;
            //write to actual memory location
            changer.set_symbol(list[port_number].symbol);
            changer.set_name(list[port_number].name);
            answer = "X";
            } 
            if(answer == "X")
            {
            url_prep();
            break;
            }
        }
    }
}
#endif
