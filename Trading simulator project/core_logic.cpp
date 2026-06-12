#include"core_logic.h"
#include<string>
#include<vector>
using namespace std;
bool User::Buy_stock(string stock_name, int quantity, double price)
{
	double total_cost = quantity * price;
	if (total_cost > balance)
	{
		return false;
	 }
	for (size_t i = 0;i < portfolio.size();i++)
	{
		if (portfolio[i].stock_name == stock_name)
		{
			double 
		}
	}
}