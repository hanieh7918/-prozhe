#include "food_product.h"
#include "pharmeceutical_product.h"
#include "bills.h"

const char *BILLS_FILE = "bills.csv";
const char *PRODUCTS_FILE = "products.csv";

void loadProducts();
void loadBills();
void showMenu();
void showEditMenu();
void saveProducts();
void saveBills();

void bill_report();
void show_item_detail();
void add_item_detail();
void edit_item_detail();
void delete_item_detail();

int searchP(size_t ID);
int searchB(size_t ID);

int main()
{

	loadProducts();
	loadBills();

	showMenu();



	saveProducts();
	saveBills();	


	//Free Memory	
	while(!Product::products.empty())
	{
		delete Product::products.back();
		Product::products.pop_back();
	}

return 0;
}

void loadProducts()
{
	std::ifstream ifs(PRODUCTS_FILE);
	if(!ifs)
		return;

	ifs.seekg(0, std::ios::end);
	if(ifs.tellg() == 0)
		return;

	ifs.seekg(std::ios::beg);
	std::string line;
try
{
	while(ifs.good() && !ifs.eof() )
	{
		std::getline(ifs, line);
		if(line.empty())
			continue;

		if(line == "P")
		{
			Product::products.push_back(new PharmeceuticalProduct(ifs));
			Product::count ++;
		}
		else if(line == "F")
		{
				Product::products.push_back(new FoodProduct(ifs));
				Product::count ++;
		}

	}
}catch(const char *e)
{
	std::cerr << e << std::endl;
}

}

void loadBills()
{
	std::ifstream ifs(BILLS_FILE);
	if(!ifs)
		return;

	ifs.seekg(0, std::ios::end);
	if(ifs.tellg() == 0)
		return;
	
	ifs.seekg(std::ios::beg);
	try
	{

		while(ifs.good() && !ifs.eof())
		{
			Bill::bills.push_back(Bill(ifs));
			Bill::count ++;
		}

	}catch(const char *e)
	{
		std::cerr << e << std::endl;
	}
}

void showMenu()
{

	int ans;
	bool loop = true;
	while(loop)
	{
		system("cls");
		std::cout << "\t\t\tSuper Market\n";
		std::cout << "\t\t\t====================\n\n";

		std::cout << "\t\t1. Bill Report" << std::endl;
		std::cout << "\t\t2. Add/Remove/Edit Item" << std::endl;
		std::cout << "\t\t3. Show Item Details" << std::endl;
		std::cout << "\t\t0. Exit" << std::endl;
		std::cout << "\t\tEnter Required Option: ";
		
		while(1)
		{
			std::cin >> ans;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			if(!std::cin.fail() && (ans >= 0 && ans <= 3))
				break;

			std::cin.clear();
			std::cout << "Wrong Input!try again: ";
		}


		switch(ans)
		{
			//If Bill Report
			case 1:
				bill_report();

				std::cout << "Press Enter To continue...";
				std::cin.get();
			break;

			//If Add Remove
			case 2:
				showEditMenu();
			break;

			case 3:
				show_item_detail();

				std::cout << "Press Enter To continue...";
				std::cin.get();

			break;
	
			case 0:
				loop = false;
			break;
		}// switch case

	}// Main loop
}

void showEditMenu()
{
	int ans;
	bool loop = true;
	size_t ID;

	std::cout << "ID: ";
	while(1)
	{
		std::cin >> ID;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			if(!std::cin.fail())
				break;

			std::cin.clear();
			std::cout << "Wrong Input!try again: ";
		}

	int index = -1;
	index = searchP(ID);

	while(loop)
	{	
		system("cls");
		std::cout << "\t\t\tBill Editor\n";
		std::cout << "\t\t\t====================\n\n";

		std::cout << "\t\t1. Add Item Details\n";
		std::cout << "\t\t2. Edit Item Details\n";
		std::cout << "\t\t3. Delete Item Details\n";
		std::cout << "\t\t0. Back to Main Menu\n";

		if(index != -1)
		{
			std::cout << "\tItem NO: " << index + 1 << std::endl;
			std::cout << "\tName of the Item: " << Product::products[index]->get_name() << std::endl;
			struct Date d = Product::products[index]->get_time();
			std::cout << "\tManifacture Date(dd-mm-yy): " << d.year << "-" << d.month << "-" << d.day << std::endl;
			std::cout << "\tPrice: $" << Product::products[index]->get_price() << std::endl;
		}

		std::cout << "Choose an Option: ";

		while(1)
		{
			std::cin >> ans;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			if(!std::cin.fail() && (ans >= 0 && ans <= 3))
				break;

			std::cin.clear();
			std::cout << "Wrong Input!try again: ";
		}

	switch(ans)
	{
		case 1:
			add_item_detail();
		break;

		case 2:
				edit_item_detail();
		break;

		case 3:
			delete_item_detail();
		break;

		case 0:
			loop = false;
		break;
	}//End of switch


		std::cout << "Press Enter To continue...";
		std::cin.get();

	}//Main Loop

}

void saveProducts()
{
	std::ofstream of(PRODUCTS_FILE);
	if(!of)
	{
		std::cerr << "Faild to save to File\n";
	}

	for(auto tmp : Product::products)
		tmp->display(of);
}

void saveBills()
{
	std::ofstream of(BILLS_FILE);
	if(!of)
	{
		std::cerr << "Faild to save to File\n";
	}

	for(auto tmp : Bill::bills)
		tmp.display(of);

}

int searchP(size_t ID)
{
	std::vector<Product *> &p = Product::products;
	for(size_t i = 0; i < p.size(); i++)
		if(p[i]->get_id() == ID)
			return i;

return -1;
}

int searchB(size_t ID)
{
	std::vector<Bill> &p = Bill::bills;
	for(size_t i = 0; i < p.size(); i++)
		if(p[i].get_ID() == ID)
			return i;

return -1;
}

void bill_report()
{
	size_t ID;
	int index;

	std::cout << "Enter ID: ";
	while(1)
	{
		std::cin >> ID;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			if(!std::cin.fail())
				break;

			std::cin.clear();
			std::cout << "Wrong Input!try again: ";
		}

	if((index = searchB(ID)) < 0)
	{
		std::cout << "ID not found!" << std::endl;
		return;
	}

	std::cout << "------------------------\n";
	Bill::bills[index].display(std::cout);
	std::cout << "------------------------\n";

}

void show_item_detail()
{
	size_t ID;
	int index;

	std::cout << "Enter ID: ";

	while(1)
	{
		std::cin >> ID;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			if(!std::cin.fail())
				break;

			std::cin.clear();
			std::cout << "Wrong Input!try again: ";
		}


	if((index = searchP(ID)) < 0)
	{
		std::cout << "ID not found!" << std::endl;
		return;
	}

	std::cout << "------------------------\n";
	Product::products[index]->display(std::cout);
	std::cout << "------------------------\n";


}

void add_item_detail()
{
	int ans;

	std::cout << "What Kind of product You want to add?\n";
	std::cout << "1. Food Product\n";
	std::cout << "2. Pharmeceutical Product\n";
	std::cout << ":-";
  
	while(1)
	{
		std::cin >> ans;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			if(!std::cin.fail() && (ans >= 1 && ans <= 2))
				break;

			std::cin.clear();
			std::cout << "Wrong Input!try again: ";
		}

	
	std::cout << "------------------------\n";
	if(ans == 1)
		Product::products.push_back(new FoodProduct(std::cin));
	else if(ans == 2)
		Product::products.push_back(new PharmeceuticalProduct(std::cin));
	std::cout << "------------------------\n";

}
void edit_item_detail()
{
	size_t ID;
	int index;
	std::string temp;

	std::cout << "Enter ID: ";

	while(1)
	{
		std::cin >> ID;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			if(!std::cin.fail())
				break;

			std::cin.clear();
			std::cout << "Wrong Input!try again: ";
		}


	if((index = searchP(ID)) < 0)
	{
		std::cout << "ID not found!" << std::endl;
		return;
	}

	Product *p = Product::products[index];

	//Get name
	std::cout << "name: ";
	while(1)
	{
		std::getline(std::cin, temp);
		std::cin.ignore();		
		
		if(!temp.empty())
			break;

		std::cout << "Name cant be empty!try again: ";
	}

  p->set_name(temp);

	//Get Type	
	std::cout << "type: ";
	while(1)
	{
		std::getline(std::cin, temp);
		std::cin.ignore();		
		
		if(!temp.empty())
			break;

		std::cout << "Type cant be empty!try again: ";
	}		

	p->set_type(temp);


	float price;
	//Get The price
	std::cout << "Price: ";
	while(1)
	{
		std::cin >> price;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

		if(!std::cin.fail())
			break;

		std::cin.clear();
		std::cout << "Wrong input!try again: ";
	}

	p->set_price(price);

	//Get the manifacture date
	Date date;
	std::cout << "Manifacture Date: " << std::endl;
	std::cout << "Year: ";
	while(1)
	{
		std::cin >> date.year;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if(!std::cin.fail())
			break;
		
		std::cin.clear();
		std::cout << "Wrong input!try again: ";
	} 

	std::cout << "Month: ";
	while(1)
	{
		std::cin >> date.month;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if(!std::cin.fail() && (date.month >= 1 && date.month <= 12))
			break;
		
		std::cin.clear();
		std::cout << "Wrong input!try again(Month Must be between 1 and 12): ";
	} 	

	std::cout << "Day: ";
	while(1)
	{
		std::cin >> date.day;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if(!std::cin.fail() && (date.day >= 1 && date.day <= 31))
			break;
		
		std::cin.clear();
		std::cout << "Wrong input!try again(Day must be between 1 and 31): ";
	}

	p->set_date(date);
}

void delete_item_detail()
{
	size_t ID;
	int index;

	std::cout << "Enter ID: ";

	while(1)
	{
		std::cin >> ID;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			if(!std::cin.fail())
				break;

			std::cin.clear();
			std::cout << "Wrong Input!try again: ";
		}


	if((index = searchP(ID)) < 0)
	{
		std::cout << "ID not found!" << std::endl;
		return;
	}

	Product::products.erase(Product::products.begin() + index);
}
