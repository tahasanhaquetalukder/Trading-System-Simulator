#pragma once
#include<string>
#include<vector>
using namespace std;
class Stock 
{
public:
	string name;
	double current_price;

};
class Portfolio_Item
{
public:
	string stock_name;
	int quantity;
	double avarage_buy_price;
};
class User
{
public:
	string username;
	string password;
	double balance;
	vector<Portfolio_Item> portfolio;
	User(string  username, string password)
	{
		this->username = username;
		this->password = password;
	}
	User(){}
	bool Buy_stock(string stock_name, int quantity, double price);
	bool Sell_stock(string stock_name, int quantity, double price);


};