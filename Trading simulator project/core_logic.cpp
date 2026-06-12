#include"core_logic.h"
#include<string>
#include<vector>
using namespace std;
bool User::Buy_stock(string stock_name, int quantity, double price)
{
    double total_cost = quantity * price;

    if (total_cost > balance) {
        return false;
    }
    for (size_t i = 0; i < portfolio.size(); i++) {
        if (portfolio[i].stock_name == stock_name) {
            double current_total_value = portfolio[i].quantity * portfolio[i].avarage_buy_price;
            double new_total_value = current_total_value + total_cost;
            int total_quantity = portfolio[i].quantity + quantity;

            portfolio[i].avarage_buy_price = new_total_value / total_quantity;
            portfolio[i].quantity += quantity;
            balance -= total_cost;
            Transaction new_transaction;
            new_transaction.type = "Buy";
            new_transaction.stock_name = stock_name;
			new_transaction.quantity = quantity;
			new_transaction.price = price;
			transaction_history.push_back(new_transaction);


            return true;
        }
    }
    Portfolio_Item new_item;
    new_item.stock_name = stock_name;
    new_item.quantity = quantity;
    new_item.avarage_buy_price = price;
    portfolio.push_back(new_item);
    balance -= total_cost;

    Transaction new_transaction;
    new_transaction.type = "Buy";
    new_transaction.stock_name = stock_name;
    new_transaction.quantity = quantity;
    new_transaction.price = price;
    transaction_history.push_back(new_transaction);
    return true;
}
bool User::Sell_stock(string stock_name, int quantity, double price)
{
    for (size_t i = 0; i < portfolio.size(); i++)
    {
        
        
		if (portfolio[i].stock_name == stock_name)
        {
            if (portfolio[i].quantity < quantity)
            {
                return false;
            }
            double revenue = quantity * price;
            balance = balance + revenue;
            portfolio[i].quantity -= quantity;
            if (portfolio[i].quantity == 0)
            {
                portfolio.erase(portfolio.begin() + i);
            }
            Transaction new_transaction;
            new_transaction.type = "Sell";
            new_transaction.stock_name = stock_name;
            new_transaction.quantity = quantity;
            new_transaction.price = price;
            transaction_history.push_back(new_transaction);

			return true;
        }
    }
    return false;
}
User::User(string username, string password)
{
    this->username = username;
    this->password = password;
	balance = 10000.0;
}
double User::getbalance()
{
    return balance;
}
vector<Portfolio_Item> User :: getportfolio()
{
	return portfolio;
}
bool User::add_money(double ammount)
{
    if (ammount < 0)
    {
        return false;
    }
    else
    {
		balance += ammount;
		return true;
    }
}
double User::check_profit_loss(string stock_name, double current_market_price)
{
    for (size_t i = 0;i < portfolio.size();i++)
    {
        if (portfolio[i].stock_name == stock_name)
        {
            double profit_loss_count = (current_market_price - portfolio[i].avarage_buy_price) * portfolio[i].quantity;
            return profit_loss_count;
        }
        
    }
    return 0.0;
}
vector<Transaction> User::get_transaction_history()
{
    return transaction_history;
}
