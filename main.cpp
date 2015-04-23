#include <stdio.h>
#include <iostream>
#include <Python.h>
#include <fstream>
#include<stdlib.h>
#include "stock.cpp"
#include "algorithms/OLS.cpp"
#include "portfolio.cpp"
#include "stock_list.cpp"
#include "single_stock_list.cpp"
#include <string>
#include <time.h>
#include <iomanip>
#define STOCK_SIZE 100 
#define PAGE_LENGTH 25
#define DEFAULT 1
using namespace std;

void python_rip(string);
void prev_csv_rip(stock &local);
void current_csv_rip(string, portfolio);
void OLS_graphing(stock local, OLS regression);
void current_single_csv_rip(string python_sub, stock user_port);
double covariance(stock &stock_1, stock &stock_2);
double ** covariance_matrix(portfolio, int);
void matrix_save(portfolio, double**, int);
int main(int argc, char* argv[])
{
/*stock delcaration order stock
example
declaration name(stock symbol, current price, industry code)
stock IBM(IBM, 185.89, 2);

portfolio declaration order
example 
delcation name (# of stocks in portfolio, industry code)
*/
srand(time(NULL));

double Sap[100];
for(int i = 0; i < STOCK_SIZE; i++)
{
Sap[i] = rand() % 60 + 160;
}
/*
for( int i = 0; i <STOCK_SIZE; i++)
{
cout <<IBM.price_history[i]<<endl;
}
*/
string cont;
cont = "Y";
while(cont == "Y")
{
cout <<"Would you Like to Enter the Porfolio Generator or the Single Stock Analyzer"<<endl;
cout <<"Press P for Portfolio and S for Single Stock; Any other value will exit"<<endl;
string answer; 
cin >> answer;
if(answer=="P")
{
cout <<"Thank You for Selecting the Portfolio Generator"<<endl;
cout <<"Which Market would you like to Analyze"<<endl;
cout <<"Press 1 for the NYSE or Press 2 for the NASDAQ"<<endl;
int market;
cin >>market;
switch(market){
    case 1:
        {
        stock_list NYSE("NYSE");
        string python_sub = NYSE.get_python();
        int port_length = NYSE.get_port_length();
        portfolio user_port(PAGE_LENGTH,DEFAULT);
        //Removes from Stock List Class and Makes Local Portfolio
        user_port = NYSE.get_port(); 
        for (int i = 0; i < port_length ; i++)
            {
            cout <<"Local Port"<<endl;
            cout << user_port.group[i].get_name()<<endl;
            }
        cout <<"Form for Python Submission "<< python_sub <<endl;
        python_rip(python_sub);
        current_csv_rip(python_sub, user_port);
        for(int i = 0; i < port_length; i++)
            {
            cout <<user_port.group[i].get_cp()<<endl;
            }
        for(int i = 0; i<port_length; i++)
            {
            prev_csv_rip(user_port.group[i]);
            user_port.group[i].return_set();
            }
    /*for(int i =0; i <STOCK_SIZE; i++)
        {
            cout<<"Main Price History: " <<user_port.group[0].price_history[i]<<endl;
        }
    */
        
        double ** user_matrix = new double *[port_length];
        for(int i = 0; i < port_length; i++)
        {
        user_matrix[i] = new double[port_length];
        }
        user_matrix = covariance_matrix(user_port, port_length);
        matrix_save(user_port, user_matrix, port_length);
        break;
        }
    case 2:
        {
        stock_list NASDAQ("NASDAQ");
        string python_sub = NASDAQ.get_python();
        int port_length = NASDAQ.get_port_length();
        portfolio user_port(PAGE_LENGTH,DEFAULT);
        //Removes from Stock List Class and Makes Local Portfolio
        user_port = NASDAQ.get_port(); 
        for (int i = 0; i < port_length ; i++)
            {
            cout <<"Local Port"<<endl;
            cout << user_port.group[i].get_name()<<endl;
            }
        cout <<"Form for Python Submission "<< python_sub <<endl;
        python_rip(python_sub);
        current_csv_rip(python_sub, user_port);
        for(int i = 0; i < port_length; i++)
            {
            cout <<user_port.group[i].get_cp()<<endl;
            }
        for(int i = 0; i<port_length; i++)
            {
            prev_csv_rip(user_port.group[i]);
            user_port.group[i].return_set();
            }
    /*for(int i =0; i <STOCK_SIZE; i++)
        {
            cout<<"Main Price History: " <<user_port.group[0].price_history[i]<<endl;
        }
    */
        double ** user_matrix = new double *[port_length];
        for(int i = 0; i < port_length; i++)
        {
        user_matrix[i] = new double[port_length];
        }
        user_matrix = covariance_matrix(user_port, port_length);
        matrix_save(user_port, user_matrix, port_length);
        break;
        }
    }
}
if(answer =="S")
{
cout <<"Which Market woudl you like to Analyze"<<endl;
cout <<"Press 1 for the NYSE or Press 2 for the NASDAQ"<<endl;
int single;
cin >>single;
switch(single){
    case 1:
        {
        single_stock_list NYSE("NYSE");
        string python_sub = NYSE.get_python();
        cout <<"python Sub:"<< python_sub <<endl;
        python_rip(python_sub);
        stock local;
        local = NYSE.changer;
        current_single_csv_rip(python_sub,local);
        prev_csv_rip(local);
        cout <<"Would You Like to Perform an OLS regression on Your Stock?"<<endl;
        cout <<"Press Y to Perfom an OLS; All Else will Quit"<<endl;
        string ans;
        cin >>ans;
            if(ans == "Y")
            {
            OLS LOCAL_OLS;
            LOCAL_OLS.sum(local.price_history);
            LOCAL_OLS.dot(local.price_history,Sap);
            LOCAL_OLS.regression(local.price_history,Sap);
            cout<<"sum:"<<LOCAL_OLS.get_sum()<<" dot:"<<LOCAL_OLS.get_dot()<<endl;
            cout<<"beta:"<<LOCAL_OLS.get_beta()<< "alpha:" << LOCAL_OLS.get_alpha()<<endl;
            cout <<"Your Output graph will be "<< local.get_symbol()<<".png"<<endl;
            OLS_graphing(local,LOCAL_OLS);
            }
        break;
        }
    case 2:
        {
        single_stock_list NASDAQ("NASDAQ");
        string python_sub = NASDAQ.get_python();
        cout <<"python Sub:"<< python_sub <<endl;
        python_rip(python_sub);
        stock local;
        local = NASDAQ.changer;
        current_single_csv_rip(python_sub,local);
        prev_csv_rip(local);
        cout <<"Would You Like to Perform an OLS regression on Your Stock?"<<endl;
        cout <<"Press Y to Perfom an OLS; All Else will Quit"<<endl;
        string ans;
        cin >>ans;
            if(ans == "Y")
            {
            OLS LOCAL_OLS;
            LOCAL_OLS.sum(local.price_history);
            LOCAL_OLS.dot(local.price_history,Sap);
            LOCAL_OLS.regression(local.price_history,Sap);
            cout<<"sum:"<<LOCAL_OLS.get_sum()<<" dot:"<<LOCAL_OLS.get_dot()<<endl;
            cout<<"beta:"<<LOCAL_OLS.get_beta()<< "alpha:" << LOCAL_OLS.get_alpha()<<endl;
            cout <<"Your Output graph will be "<< local.get_symbol()<<".png"<<endl;
            OLS_graphing(local,LOCAL_OLS);
            }
        break;
        }
    }
}
if(answer!="P" || answer != "S")
{
exit(0);
}
//else{
//exit(0);
//}
cout << "Would you Like to run an additional Regression? If so type Y; anything else exits"<<endl;
cin >>cont;
}
/*
char * info[3];
info[0] = "IBM";
info[1] = "10";
info[2] = "45";
*/
//cout << info[0] <<endl;
cout <<"One More Time"<<endl;
}
void matrix_save(portfolio local, double ** matrix, int port_length)
{
string file_name;
cout << "what would you like your Co_variance Matrix file name to be?";
cin >>file_name;
file_name = file_name +".csv";
cout << "Your File will be saved as: " <<file_name<< endl; 
ofstream output;
output.open(file_name);
output <<",";
for( int i = 0; i <port_length; i++)
    {
    output << local.group[i].get_symbol() << ",";
    }
output <<endl;
for( int i =0; i<port_length; i++)
    {
    output <<local.group[i].get_symbol()<<",";
    for(int j = 0; j < port_length; j++)
        {
        output <<matrix[i][j] <<",";
        }
    output <<endl;
    }
output.close();
}




double ** covariance_matrix(portfolio local, int port_length)
{
double ** matrix = new double*[port_length];
for( int i = 0; i<port_length; i++)
    {
    matrix[i]= new double[port_length];
    }
    
for( int i = 0; i< port_length; i++)
    {    
    for(int j = 0; j<port_length; j++)
        {
        matrix[i][j]=covariance(local.group[i], local.group[j]);
        }
    }
int port_restraint;
int correct_port = port_length -1;
cout << "      ";
for(int i = 0; i <port_length; i++)
    {
    cout << local.group[i].get_symbol() << "    ";
    }
cout <<endl;
for(int i = 0; i<port_length; i++)
    {
    /*for(port_restraint = correct_port;port_restraint <port_length; port_restraint++)
        {
        cout << matrix[i][port_restraint] <<" ";
        }
    correct_port--;
   if(correct_port == -1)
    {
    break;
    }
    */
    cout << local.group[i].get_symbol() << "    ";
    for(int j = 0; j < port_length; j++)
        {
        //if(matrix[i][j] < .008)
        //{
        //cout << 0.0000;
        //}
        //else
            //{
            cout<<setprecision(4) <<matrix[i][j]<< " ";
            //}
        }
    cout <<endl;
    }
return matrix;
}
void OLS_graphing(stock local, OLS regression)
{
setenv("PYTHONPATH",".",1);
PyObject *pName, *pModule, *pArgs, *pFunc, *pCall;
Py_Initialize();
pName = PyString_FromString((char*)"simple_plot");
pModule = PyImport_Import(pName);
PyObject_Print(pModule, stdout, 0);
pFunc = PyObject_GetAttrString(pModule, (char*)"sim_plot");
string python_string = local.get_symbol();
pArgs = PyTuple_Pack(3,PyString_FromString(python_string.c_str()), PyFloat_FromDouble(regression.get_beta()), PyFloat_FromDouble(regression.get_alpha()));
pCall = PyObject_CallObject(pFunc, pArgs);
Py_Finalize();
}

void python_rip(string python_sub)
{
setenv("PYTHONPATH",".",1);
PyObject *pName, *pModule, *pArgs, *pFunc, *pCall;
Py_Initialize();
pName = PyString_FromString((char*)"data");
pModule = PyImport_Import(pName);
PyObject_Print(pModule, stdout, 0);
pFunc = PyObject_GetAttrString(pModule, (char*)"data");
pArgs = PyTuple_Pack(1,PyString_FromString(python_sub.c_str()));
pCall = PyObject_CallObject(pFunc, pArgs);
Py_Finalize();
}
void prev_csv_rip(stock &local)
    {
    setenv("PYTHONPATH",".",1);
    PyObject *pName, *pModule, *pArgs, *pFunc, *pCall;
    Py_Initialize();
    pName = PyString_FromString((char*)"prev_data");
    pModule = PyImport_Import(pName);
    PyObject_Print(pModule, stdout, 0);
    pFunc = PyObject_GetAttrString(pModule, (char*)"data_prev");
    pArgs = PyTuple_Pack(1,PyString_FromString(local.get_symbol().c_str()));
    pCall = PyObject_CallObject(pFunc, pArgs);
    Py_Finalize();
    string submission; 
    submission = local.get_symbol() + "prev_.csv";
    
    std::ifstream inFile(submission.c_str());
    string name;
    string dummy;
    getline(inFile,dummy);
    int iter = 0; 
    string cp;
    //one-trick
    while(getline(inFile,name, ','))
    {
    getline(inFile, cp,',');
    //cout <<"The Price"<<cp <<endl;
    if (cp != "N/A")
    {
    local.price_history[iter] = stod(cp); 
    }
    else
    {
    local.price_history[iter] = 0;
    cout << "Setting Zero"<<endl;
    }
    iter++;

    getline(inFile,name, ',');
    getline(inFile,name, ',');
    getline(inFile,name, ',');
    getline(inFile,name, ',');
    getline(inFile,name);
    if(iter == STOCK_SIZE)
    {
    break;
    //prevents seg fault
    }
    }
cout <<"PRICE HISTORY UPDATED" <<endl;
}

double covariance(stock &stock_1, stock &stock_2)
{

    double init_sum;
    double fin_sum;
    double co_va;
    for(int i = 0; i <STOCK_SIZE-1; i++)
    {

    init_sum = (stock_1.return_history[i] - stock_2.return_calc_average());
    fin_sum = (stock_1.return_calc_average() - stock_2.return_history[i]);
    co_va = init_sum +fin_sum + co_va;
    //cout << "Co-Va Set:" << co_va <<endl;
    }
    co_va = co_va/(STOCK_SIZE-2);
    return co_va;


}

void current_single_csv_rip(string python_sub, stock user_port)
{
int line_number = 0;
string line;
string submission;
submission = python_sub +".csv";
std::ifstream inFile(submission.c_str());
//Allows for strings to be passed
while(getline(inFile,line))
    {
    line_number++;

    }   
inFile.close();
inFile.open(submission.c_str());
int iter = 0;
string name;
string cp;
double current_price;

//array technically begin at list[1]-list[line_number]
while(getline(inFile,name, ','))
    {
    cout <<iter<< " Times Through"<<endl;
    user_port.set_name(name);
    getline(inFile, cp);
    if (cp != "N/A")
    {
    current_price = stod(cp); 
    }
    else
    {
    current_price = 0;
    }
    user_port.set_cp(current_price);
    //cout << "Company Name: "<<list[iter].name<<endl;
    //cout <<"Ticker: " <<list[iter].symbol <<endl;
    iter++;
    if(iter == line_number)
    {
    break;
    //prevents seg fault
    }
}
cout <<"SINGLE STOCK SUCCUESSFULLY UPDATED TO CURRENT PRICE"<<endl;
}
void current_csv_rip(string python_sub, portfolio user_port)
{
int line_number = 0;
string line;
string submission;
submission = python_sub +".csv";
std::ifstream inFile(submission.c_str());
//Allows for strings to be passed
while(getline(inFile,line))
    {
    line_number++;

    }   
inFile.close();
inFile.open(submission.c_str());
int iter = 0;
string name;
string cp;
double current_price;

//array technically begin at list[1]-list[line_number]
while(getline(inFile,name, ','))
    {
    cout <<iter<< " Times Through"<<endl;
    user_port.group[iter].set_name(name);
    getline(inFile, cp);
    if (cp != "N/A")
    {
    current_price = stod(cp); 
    }
    else
    {
    current_price = 0;
    }
    user_port.group[iter].set_cp(current_price);
    //cout << "Company Name: "<<list[iter].name<<endl;
    //cout <<"Ticker: " <<list[iter].symbol <<endl;
    iter++;
    if(iter == line_number)
    {
    break;
    //prevents seg fault
    }
}
cout <<"PORTFOLIO SUCCUESSFULLY UPDATED TO CURRENT PRICE"<<endl;
}
