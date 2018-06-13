#include "stdafx.h"
#include"BickieShop.h"



/// Remove item from the shop
///
/// Remove the product and ideally keep the array in proper state
void BickieShop::removeProduct(int productId)
{
	delete m_products[productId];

	for (int i = productId; i < m_productsCount - 1; ++i)
		m_products[i] = m_products[i + 1];
}



/// Edit a product by supplying a full list of properties
///
/// In case a proper value is given for a property, update it.
void BickieShop::editProduct(int id, char* name = nullptr, char* desc = nullptr, double price = -1)
{
	Product* product = findProductById(id);

	if (name) {
		product->setName(name);
	}

	if (desc) {
		product->setDescription(name);
	}

	if (price >= 0) {
		product->setPrice(price);
	}
}
