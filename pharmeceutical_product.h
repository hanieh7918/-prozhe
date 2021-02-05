#ifndef PHARMECEUTICAL_PRODUCT_H
#define PHARMECEUTICAL_PRODUCT_H

#include "product.h"

class PharmeceuticalProduct : public Product
{
	private:
		std::string m_impact; 

		PharmeceuticalProduct();
	public:

		PharmeceuticalProduct(std::istream &is);

		void display(std::ostream &os);

	//setter and getters
		void set_price(float price);
		void set_date(struct Date date);
		void set_name(std::string name);
		void set_type(std::string type);

		float get_price() const;
		size_t get_id() const;
		struct Date get_time() const;
		std::string get_name() const;
		std::string get_type() const;

		void set_impact(std::string impact);
		std::string get_impact() const;
	
};


#endif
