#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <vector>
#include "product.h"

class Bill
{
	private:
		size_t m_ID;
		struct Date m_date;
		
		std::vector<std::string> m_names;
		std::vector<size_t> m_count;
		std::vector<float> m_prices;

		Bill();
	
	public:
		Bill(std::ifstream &ifs);

		void display(std::ostream &os);
		double totalPrice() const;

		//setter and getter
		size_t get_ID() const;
		struct Date get_date() const;
		std::vector<std::string> get_names() const;
		std::vector<size_t> get_counts() const;
		std::vector<float> get_prices() const;

		static size_t count;
		static std::vector<Bill> bills;
};

#endif
