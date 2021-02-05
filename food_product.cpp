#include "food_product.h"

FoodProduct::FoodProduct() 
{}


FoodProduct::FoodProduct(std::istream &is)
{
	if(!is.good())
		throw "Bad Istream Object!";

	std::string temp;
	//If is was cin
	if(&is == &std::cin)
	{

		//Set ID	
		m_ID = ++ Product::count;

		//Get name
		std::cout << "Food name: ";
		while(1)
		{
			getline(is, temp);
			
			if(!temp.empty())
				break;

			std::cout << "Name cant be empty!try again: ";
		}

		m_name = temp;
		maxTokenSize = temp.length() > maxTokenSize ? temp.length() : maxTokenSize;

	
		//Get Type	
		std::cout << "Food type: ";
		while(1)
		{
			getline(is, temp);
			
			if(!temp.empty())
				break;

			std::cout << "Type cant be empty!try again: ";
		}		

		m_type = temp;
		maxTokenSize = temp.length() > maxTokenSize ? temp.length() : maxTokenSize;

		//Get The price
		std::cout << "Food Price: ";
		while(1)
		{
			is >> m_price;
			is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

			if(!is.fail())
				break;

			is.clear();
			std::cout << "Wrong input!try again: ";
		}


		//Get the manifacture date
		std::cout << "Manifacture Date: " << std::endl;
		std::cout << "Year: ";
		while(1)
		{
			is >> m_date.year;
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if(!is.fail())
				break;
			
			is.clear();
			std::cout << "Wrong input!try again: ";
		} 
	
		std::cout << "Month: ";
		while(1)
		{
			is >> m_date.month;
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if(!is.fail() && (m_date.month >= 1 && m_date.month <= 12))
				break;
			
			is.clear();
			std::cout << "Wrong input!try again(Month Must be between 1 and 12): ";
		} 	

		std::cout << "Day: ";
		while(1)
		{
			is >> m_date.day;
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if(!is.fail() && (m_date.day >= 1 && m_date.day <= 31))
				break;
			
			is.clear();
			std::cout << "Wrong input!try again(Day must be between 1 and 31): ";
		}

		//Food Calory
		std::cout << "Food Calories: ";
		while(1)
		{
			is >> m_calories;
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if(!is.fail())
				break;
			
			is.clear();
			std::cout << "Wrong input!try again: ";
		} 


	}//End of cin part
	else//If is is ifstream
	{
		std::vector<std::string> strings;
		std::string line;

		std::getline(is, line);

		if(line.empty())
			throw "Corrupt File";
		
		Product::getTokens(strings, ',', line);
	
		//set The Datas
		m_ID = stoul(strings[0]);
		
		m_name = strings[1];
		maxTokenSize = m_name.length() > maxTokenSize ? m_name.length() : maxTokenSize;
		

		m_type = strings[2];
		maxTokenSize = m_type.length() > maxTokenSize ? m_type.length() : maxTokenSize;
		
		m_price = stof(strings[3]);
		m_date.year = stoi(strings[4]);
		m_date.month = stoi(strings[5]);
		m_date.day = stoi(strings[6]);

		m_calories = stoul(strings[7]);
		
	}

}


void FoodProduct::display(std::ostream &os)
{
	//If os is cout
	if(&os == &std::cout)
	{
		os << std::setw(9) << "Name: " << std::setw(maxTokenSize) << std::left << m_name << "\n";
		os << std::setw(9) << "Type: " << std::setw(maxTokenSize) << std::left << m_type << "\n";
		os << std::setw(9) << "ID: " << std::setw(10) << std::left << m_ID << "\n";
		os << std::setw(9) << "Price: $" << std::setw(5) << std::left << std::setprecision(2) << m_price << "\n";
		os << "Manifacture Date: ";
		os << std::setw(4) << std::right << m_date.year << "-";
		os << std::setw(2) << std::left << m_date.month << "-";
		os << std::setw(2) << std::left << m_date.day << "\n";
		os <<std::setw(9) << "Calories: " << std::setw(7) << std::left << m_calories << "\n";
	}else
	{
	//If os is ofstream
	os <<"F\n" << m_ID << "," << m_name << "," << m_type << "," <<  m_price << "," << m_date.year << "," << m_date.month << "," << m_date.day << "," << m_calories << "\n";
	}
}

//setter and getters
void FoodProduct::set_price(float price)
{
	m_price = price;
}
void FoodProduct::set_date(struct Date date)
{
	m_date = date;
}
void FoodProduct::set_name(std::string name)
{
	m_name = name;
}
void FoodProduct::set_type(std::string type)
{
	m_type = type;
}

float FoodProduct::get_price() const
{
	return m_price;
}

size_t FoodProduct::get_id() const
{
	return m_ID;
}

struct Date FoodProduct::get_time() const
{
	return m_date;
}

std::string FoodProduct::get_name() const
{
	return m_name;
}

std::string FoodProduct::get_type() const
{
	return m_type;
}


void FoodProduct::set_calories(size_t calories)
{
	m_calories = calories;
}

size_t FoodProduct::get_calories() const
{
	return m_calories;
}

