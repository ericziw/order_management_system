#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

struct Customer {
	string first_name;
	string last_name;
	int age;
	int address_num;
	string address_name;
	string address_suffix;
	int cust_order_id[10];
};

struct Order {
	int order_id;
	int order_check;
	int order_amount;
	float order_price;
	string order_item[10];
} Odr[10];

void name_check(Customer C[], string f, string l, int &cust_num, bool &check, int cust_amount);

int main()
{
	int cust_amount;
	
	ifstream infile;
	infile.open("customers.dat");
	
	infile >> cust_amount;
	
	Customer C[cust_amount];
	
	for(int i = 0; i < cust_amount; i++)
	{
		infile >> C[i].first_name;
		infile >> C[i].last_name;
		infile >> C[i].age;
		infile >> C[i].address_num;
		infile >> C[i].address_name;
		infile >> C[i].address_suffix;
	}
	
	infile.close();
	
	int order_num_f = 0;
	int cust_num = 0;
	int item_amount = 0;
	int order_num = 0;
	for(int i = 0; i < cust_amount; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			C[i].cust_order_id[j] = -1;
		}
	}
	for(int i = 0; i < 10; i++)
	{
		Odr[i].order_check = -1;
	}
	for(int i = 0; i < 10; i++)
	{
		Odr[i].order_id = -1;
	}
	
	string command;
	string f_name;
	string l_name;
	
	infile.open("commands.dbcmd");
	
	infile >> command;
	while(infile)
	{
		bool check = false;
		if(command == "update")
		{
			infile >> f_name;
			infile >> l_name;
			name_check(C, f_name, l_name, cust_num, check, cust_amount);
			
			if(check == true)
			{
				infile >> C[cust_num].first_name;
				infile >> C[cust_num].last_name;
				infile >> C[cust_num].age;
				infile >> C[cust_num].address_num;
				infile >> C[cust_num].address_name;
				infile >> C[cust_num].address_suffix;
			}
			if(check == false)
			{
				cout << "This customer was not found. Ignoring update request." << endl;
			}
		}
		
		if(command == "place")
		{
			bool order_cap = false;
			infile >> f_name;
			infile >> l_name;
			name_check(C, f_name, l_name, cust_num, check, cust_amount);
			
			if(check == true)
			{
				for(int i = 0; i < 10; i++)
				{
					if(Odr[i].order_check == -1)
					{
						for(int k = 0; k < 10; k++)
						{
							if(C[cust_num].cust_order_id[k] == -1)
							{
								C[cust_num].cust_order_id[k] = order_num;
								break;
							}
						}
						Odr[i].order_id = order_num;
						Odr[i].order_check = 0;
						infile >> Odr[i].order_price;
						infile >> item_amount;
						Odr[i].order_amount = item_amount;
						
						for(int j = 0; j < item_amount; j++)
						{
							infile >> Odr[i].order_item[j];
						}
						order_cap = false;
						break;
						
					}
					else
					{
						order_cap = true;
					}
				}
			
			}
			if(order_cap == true)
			{
				cout << "At maximum order capacity. Ignoring order placement." << endl;
			}
			
			if(check == false)
			{
				cout << "This customer was not found. Ignoring order placement." << endl;
			}
			
			order_num++;
		}
		if(command == "fulfill")
		{
			bool order_exist = true;
			infile >> order_num_f;
			for(int i = 0; i < cust_amount; i++)
			{
				for(int j = 0; j < 10; j++)
				{
					if(order_num_f == C[i].cust_order_id[j])
					{
						C[i].cust_order_id[j] = -1;
					}
				}
			}
			for(int i = 0; i < 10; i++)
			{
				if(order_num_f == Odr[i].order_id)
				{
					for(int j = 0; j < 10; j++)
					{
						Odr[i].order_id = -1;
						Odr[i].order_check = -1;
						Odr[i].order_item[j].clear();
					}
					order_exist = true;
					break;
				}
				else
				{
					order_exist = false;
				}
			}
			if(order_exist == false)
			{
				cout << "This order does not exist. Ignoring fulfillment." << endl;
			}
		}
		
		infile >> command;
	}
	
	infile.close();
	
	cout << setfill('#') << setw(22) << "#" << endl;
	cout << "Customers" << endl;
	cout << setfill('#') << setw(22) << "#" << endl;
			
	for(int i = 0; i < cust_amount; i++)
	{
		cout << C[i].first_name << " " << C[i].last_name << endl;
		cout << C[i].age << endl;
		cout << C[i].address_num << " " << C[i].address_name << " " << C[i].address_suffix << endl << endl;
		cout << "Open Orders: ";
		for(int j = 0; j < 10; j++)
		{
			if(C[i].cust_order_id[j] > -1)
			{
				cout << C[i].cust_order_id[j] << "  ";
			}
		}
		cout << endl << endl;
		cout << setfill('-') << setw(22) << "-" << endl;
	}
	
	cout << setfill('#') << setw(22) << "#" << endl;
	cout << "All Open Orders" << endl;
	cout << setfill('#') << setw(22) << "#" << endl;
	
	int k;
	for(int i = 0; i < 10; i++)
	{
		k = Odr[i].order_amount;
		for(int j = 0; j < k; j++)
		{
			if(Odr[i].order_id == -1)
			{
				cout << "No Open Orders" << endl;
				break;
			}
			cout << "Order " << Odr[i].order_id << ": " << Odr[i].order_item[j] << endl << endl;
		}
	}
	
	cout << setfill('#') << setw(22) << "#" << endl;
	cout << "Order Prices" << endl;
	cout << setfill('#') << setw(22) << "#" << endl;
	
	for(int i = 0; i < 10; i++)
	{
		if(Odr[i].order_id == -1)
		{
			continue;
		}
		cout << "Order " << Odr[i].order_id << ": " << Odr[i].order_price << endl << endl;
	}
	
}

void name_check(Customer C[], string f, string l, int &cust_num, bool &check, int cust_amount)
{
	for(int i = 0; i < cust_amount; i++)
	{
		if(f == C[i].first_name)
		{
			if(l == C[i].last_name)
			{
				cust_num = i;
				check = true;
			}
			else
			{
				check = false;
			}
		}
	}
}
