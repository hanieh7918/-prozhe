#include "bills.h"


size_t Bill::count = 0;
std::vector<Bill> Bill::bills;

Bill::Bill()
{}

Bill::Bill(std::ifstream &ifs)
{
	if(!ifs.good())
		throw "Bad ifstream object!";

	std::string line;
	std::vector<std::string> temp;

	//get ID
	getline(ifs, line);
	m_ID = stoul(line);

	if(ifs.eof())
		throw "Corrupted File";

	//Get Names
	getline(ifs, line);
	Product::getTokens(m_names, ',', line);

	if(ifs.eof())
		throw "Corrupted File";

	//get counts
	getline(ifs, line);
	Product::getTokens(temp, ',', line);

	for(auto tmp : temp)
		m_count.push_back(stoul(tmp));
	temp.clear();

	if(ifs.eof())
		throw "Corrupted File";


	//get prices
	getline(ifs, line);
	Product::getTokens(temp, ',', line);

	for(auto tmp : temp)
		m_prices.push_back(stof(tmp));

	if(ifs.eof())
		throw "Corrupted File";

	//get Date
	getline(ifs, line);
	Product::getTokens(temp, '-', line);

	m_date.year = stoi(temp[0]);
	m_date.month = stoi(temp[1]);
	m_date.day = stoi(temp[2]);

	

}

void Bill::display(std::ostream &os)
{
	if(&os == &std::cout)
	{
		os << "Bill ID: " << m_ID << std::endl;
		
		os << "Date: " << m_date.year << "-" << m_date.month << "-" << m_date.day << std::endl;

		os << std::setw(10) << std::left << "Name\t" << std::setw(10) << std::left << "Counts\t" << std::setw(10) << std::left << "Price" << std::endl;	
		for(int i = 0; i < m_names.size(); i++)
		{
			os << std::setw(10) << std::left << m_names[i] << "\t";
			os << std::setw(10) << std::left << m_count[i] << "\t";
			os << std::setw(10) << std::left << m_prices[i] << "\n";
		}
		os << std::endl;
		os << "Total Price: " << totalPrice() << std::endl;

	}else
	{
		os << m_ID;
		for(auto tmp : m_names)
			os << tmp << ",";
		os << "\b\n";

		for(auto tmp : m_count)
			os << tmp << ",";
		os << "\b\n";


		for(auto tmp : m_prices)
			os << tmp << ",";
		os << "\b\n";

		os << m_date.year << "-" << m_date.month << "-" << m_date.day << std::endl;

	}

}

//setter and getter
size_t Bill::get_ID() const
{
	return m_ID;
}

struct Date Bill::get_date() const
{
	return m_date;
}

std::vector<std::string> Bill::get_names() const
{
	return m_names;
}

std::vector<size_t> Bill::get_counts() const
{
	return m_count;
}

std::vector<float> Bill::get_prices() const
{
	return m_prices;
}


double Bill::totalPrice() const
{
	double t_price = 0.0;
	for(auto tmp : m_prices)
		t_price += tmp;

	return t_price;
}
