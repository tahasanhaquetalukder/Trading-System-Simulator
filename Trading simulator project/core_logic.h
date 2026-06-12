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
struct Transaction
{
	string type;
	string stock_name;
	int quantity;
	double price;
};
class User
{
public:
	string username;
	string password;
	double balance;
	vector<Portfolio_Item> portfolio;
	vector<Transaction> transaction_history;
	User(string username, string password);
	User();
	bool Buy_stock(string stock_name, int quantity, double price);
	bool Sell_stock(string stock_name, int quantity, double price);
	double getbalance();
	vector<Portfolio_Item> getportfolio();
	bool add_money(double ammount);
	double check_profit_loss(string stock_name, double current_market_price);
	vector<Transaction> get_transaction_history();
};