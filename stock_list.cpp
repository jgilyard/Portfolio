#ifndef STOCK_LIST_H
#define STOCK_LIST_H
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
class stock_list{

public:
void csv_reader();

stock_list(string name)
    {
    string ending;
    ending = ".csv";
    file_name = "markets/";
    file_name = file_name +name;
    file_name = file_name + ending;
    csv_reader();
    market_name = name;
    my_port.set_group(PAGE_LENGTH);
    stock_browse();
    //portfolio_counter = 0;
    //25 at a time browse
    }
void stock_browse();
string url_prep(portfolio);
string get_python(){return python_sub;}
portfolio get_port(){return my_port;}
int get_port_length(){return portfolio_counter;}
private:
info *list;
string file_name; 
string market_name;
string python_sub;
int line_number;
int portfolio_counter;
portfolio my_port;
};


void stock_list::csv_reader()
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


string stock_list::url_prep(portfolio url)
{

//portfolio my_port(PAGE_LENGTH,DEFAULT);
string python_url;
stock *changer;

for(int i = 0; i< portfolio_counter; i++)
    {
    changer = &my_port.group[i];
    python_url = python_url + changer->get_symbol();
        
        if( i == portfolio_counter - DEFAULT)
        {
        break;
        }
        else
            {
            python_url = python_url + "+";
            }
    }
return python_url;   
}


void stock_list::stock_browse()
{
int num_pages = ceil(line_number/PAGE_LENGTH);
cout << "Number of Pages to View Stocks " << num_pages <<endl;
portfolio_counter = 0;
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
        cout <<"You May Construct a Portfolio of up to 25 stocks for analysis"<<endl;
        cout <<"Would you like to look at the next 25 stocks?"<<endl;
        cout <<"If so, Press Y, P to add a stock to your Portfolio, V to view your portfolio, X to exit" <<endl;
        string answer;
        cin >>answer;
            while(answer != "Y"&& answer != "X" && answer != "P" && answer!= "V")
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
            cout<<"Please enter which stock number you would like to add to your portfolio"<<endl;
            int port_number;
            cin >>port_number;
            stock *changer;
            changer = &my_port.group[portfolio_counter];
            my_port.group[portfolio_counter].set_symbol(list[port_number].symbol);
            //write to actual memory location
            changer->set_symbol(list[port_number].symbol);
            changer->set_name(list[port_number].name);
            portfolio_counter++;
            i = prev_page-PAGE_LENGTH; 
            }
            if(answer =="V")
            {
                for(int runner = 0; runner < portfolio_counter; runner++)
                {
                cout << my_port.group[runner].get_name()<<endl;
                }
            i = prev_page-PAGE_LENGTH;
            python_sub = url_prep(my_port);
            cout <<"Stocks Prepared for Python Submission "<<python_sub<<endl;
            cout <<"Press C to Continue with Additional Options and Stock View or X to Exit "<<endl;
            string next;
            cin >> next; 
                if (next == "C")
                    {
                
                    }
                if(next =="X")
                    {
                    break;
                    }
            
            }
            
            if(answer == "X")
            {
            python_sub = url_prep(my_port);
            break;
            }
        }
    }
}
#endif
