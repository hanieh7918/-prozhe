#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

struct Date
{
	int day;
	int month;
	int year;
};

class Product
{


	protected:
		size_t m_ID;
		float m_price;
		struct Date m_date;
		

		std::string m_name;
		std::string m_type;

	public:

		static size_t count;
		static size_t maxTokenSize;
		static std::vector<Product *> products;
		static void getTokens(std::vector<std::string> &retStr, char token, std::string line);

		Product();
		virtual void display(std::ostream &os) = 0;

		//setter and getters
		virtual void set_price(float price) = 0;
		virtual void set_date(struct Date date) = 0;
		virtual void set_name(std::string name) = 0;
		virtual void set_type(std::string type) = 0;

		virtual float get_price() const = 0;
		virtual size_t get_id() const = 0;
		virtual struct Date get_time() const = 0;
		virtual std::string get_name() const = 0;
		virtual std::string get_type() const = 0;
};


#endif
