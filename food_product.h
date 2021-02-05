#ifndef FOOD_PRODUCT_H
#define FOOD_PRODUCT_H

#include "product.h"

class FoodProduct : public Product
{

	private:
		size_t m_calories;

		//to delete
		FoodProduct();
	public:

		FoodProduct(std::istream &is);

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


		void set_calories(size_t calories);
		size_t get_calories() const;
};

#endif
