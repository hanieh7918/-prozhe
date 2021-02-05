#include "product.h"



Product::Product()
{}



//Product static Members And Functions
size_t Product::count = 0;
size_t Product::maxTokenSize = 0;
std::vector<Product *> Product::products;







void Product::getTokens(std::vector<std::string> &retStr, char token, std::string line)
{
	std::istringstream s(line);
	std::string t;
	while(std::getline(s, t, token))
		retStr.push_back(t);
}


