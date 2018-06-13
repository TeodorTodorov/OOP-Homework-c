#pragma once
#include<iostream>
#include"Product.h"
#include"Order.h"
#include"User.h"
#include"Guard.h"
const int MAX_PRODUCTS_COUNT = 100;
const int MAX_ORDERS_COUNT = 100;
const int MAX_USERS_COUNT = 100;
class BickieShop {

	int g_currentProductId = 1;
	int generateUniqueId()
	{
		return g_currentProductId++;
	}

public:
	BickieShop()
	{
		// we start all clear
		m_productsCount = 0;
		m_ordersCount = 0;
		m_usersCount = 0;
	}

	~BickieShop()
	{
		for (int i = 0; i < m_productsCount; ++i) {
			delete m_products[i];
		}
		for (int i = 0; i < m_ordersCount; ++i) {
			delete m_orders[i];
		}
	}

	/*****************
	*  Order utils  *
	*****************/
	void addOrder(int productId, char* address, int userId)
	{
		if (m_ordersCount < MAX_ORDERS_COUNT) {
			// construct a product using a generated unique identifier
			m_orders[m_ordersCount] = new Order(generateUniqueId(), productId, address, userId);
			// Now increase the number of items
			m_ordersCount++;
		}
		else {
			std::cerr << "Now please sit down and breath slowly... We're full. We can't manage any more orders." << std::endl;
		}
	}

	void removeOrder(int orderId)
	{
		int pos = -1;
		for (int i = 0; i < m_ordersCount; i++)
		{
			if (m_orders[i]->getId() == orderId)
			{
				pos = i;
			}
		}
		if (pos != -1) {
			delete m_orders[pos];

			for (int i = pos; i < m_ordersCount - 1; ++i) {
				m_orders[i] = m_orders[i + 1];
			}
			--m_ordersCount;
		}
	}
	Product* findProductById(int id)
	{
		for (int i = 0; i < m_productsCount; ++i) {
			if (m_products[i]->getId() == id) {
				return m_products[i];
			}
		}
		// possibly not
		return nullptr;
	}
	int filterUserOrders(Order** arr,int userId ) {
		int size = 0;
		for (int i = 0; i < m_ordersCount; i++)
		{
			if (m_orders[i]->getUserId() == userId)
			{
				arr[size] = (m_orders[i]);
				size++;
			}
		}
		return size;

	}
	User* findUserById(int id)
	{
		for (int i = 0; i < m_usersCount; ++i) {
			if (m_users[i]->getId() == id) {
				return m_users[i];
			}
		}
		// possibly not
		return nullptr;
	}
	Order* findOrderById(int id)
	{
		for (int i = 0; i < m_ordersCount; ++i) {
			if (m_orders[i]->getId() == id) {
				return m_orders[i];
			}
		}
		// possibly not
		return nullptr;
	}
private:	void swap(Order *xp, Order *yp)
{
	Order temp = *xp;
	*xp = *yp;
	*yp = temp;
}
public:
	void SortOrdersByStatus() {
		int i, j;
		for (i = 0; i < m_ordersCount; i++)

			// Last i elements are already in place   
			for (j = 0; j < m_ordersCount - i-1; j++)
				if (m_orders[j]->getStatus() > m_orders[j + 1]->getStatus())
					swap(m_orders[j], m_orders[j + 1]);
	}
	void SortOrdersByProductName() {
		int i, j;
		for (i = 0; i < m_ordersCount; i++) {

			// Last i elements are already in place   
			for (j = 0; j < m_ordersCount - i-1; j++) {
				int jid0 = m_orders[j]->getProductId();
				int jid1 = m_orders[j + 1]->getProductId();

				Product* prod0 = findProductById(jid0);
				Product* prod1 = findProductById(jid1);
				//getProductById(jid0, prod0);
				//getProductById(jid1, prod1);


					if (strcmp(prod0->getName(), prod1->getName())>0) {
						swap(m_orders[j], m_orders[j + 1]);
					}
			}
		}
	}
	/*bool getProductById(int id, Product* prod) {
		for (int i = 0; i < m_productsCount; i++)
		{
			if (m_products[i]->getId() == id)
			{
				*prod = *m_products[i];
				return true;
			}
		

		}
		return false;
	}*/
	Product** getProductsList() {
		return m_products;
	}
	
	User** getUsersList() {
		return m_users;
	}
		
		
	int getUsersCount() {
		return m_usersCount;
	}
	int getProductCount() {
		return m_productsCount;
	}

	Order** getOrdersList() {
		return m_orders;
	}

	int getOrderCount() {
		return m_ordersCount;
	}

	/// Create a product and add it to the existing list of such.
	/// NOTE: it generates an id for that item
	void addProduct(char* name, double price, char* desciption)
	{
		// XXX looks exactly like `addOrder`
		if (m_productsCount < MAX_PRODUCTS_COUNT) {
			// construct a product using a generated unique identifier
			m_products[m_productsCount] = new Product(generateUniqueId(), name, price, desciption);
			// Now increase the number of items
			m_productsCount++;
		}
		else {
			std::cerr << "Could not add any more products. Shop is full.";
		}
	}
	void editProduct(int productId, char* name, char* desc, double price);
	void removeProduct(int productId); // XXX not implemented


									   /*******************
									   *  User utils  *
									   *******************/
									   // TODO: encrypt password, and add field for salt;)
									   // crypto is cool PHP (h)
	void addUser(const  char*name, const char* email, const char* password, const char* role)
	{
		if (m_usersCount < MAX_USERS_COUNT) {
			// construct a user using a generated unique identifier
			m_users[m_usersCount] = new User(generateUniqueId(), name, email, password, role);
			// Now increase the number of items
			m_usersCount++;
		}
		else {
			std::cerr << "Now please sit down and breath slowly... We're full. We can't manage any more users." << std::endl;
		}
	}
	bool authUser(const char* email, const char* password, Guard* guard) {
		for (int i = 0; i < m_usersCount; i++)
		{
			if (strcmp(m_users[i]->getEmail(), email) == 0) {
				if (strcmp(m_users[i]->getPassword(), password) == 0) {
					guard->setCurrentUser(m_users[i]);
					return true;
				}
			}

		}
		return false;
	}






	/* View methods */
	/**
	* Notice how the View methods are restricted to do just simple operations, without much knowledge for
	* the surrounding infrastructure. They are responsible for:
	* i) showing information to the user
	* ii) getting response from them.
	* iii) simply calling methods depending on the response
	* The *means* by which they succeed in accomplishing visualization may be changed, e.g.
	* we may want to use some graphical interface of else. Having such separation allows us to change
	* only their implementation, avoiding changes to any other part of the system
	*
	* Last note: We are not creating any copies of the original objects
	*
	* We can improve the behaviour and allowed options for the use as much as we want
	*/

	/**
	* WORKFLOW (Normal user) Simple version
	* - index view -> products list view
	* - products list view -> product details
	* - order details -> order | index view
	*/
	// ----------
	/**
	* Забележете, че View (страници) методите са ограничени до това да извършват съвсем прости опреции без да
	* притежават особено знание за обграждащата ги инфраструктура. Те се грижат за:
	* i) показване на информацията на потребителя (в момента използва ме конзолата като средство за визуализация)
	* ii) за регистриране на "отговор" от тях
	* iii) да използват конкретни методи в зависимост от този отговор
	*/

	/**
	* Поток на Работа (Обикновен потребител)
	* * Начална страница   --> Списък продукти                   (накрая просто премини към детайли на продукт)
	* * Списък продукти    -- id --> Детайли за продукт          (при въведен идентификатор, премини към детайли на продукт)
	* * Детайли за продукт -- Y --> Поръчка на продукт | -- N --> Начална страница    (ако отговори с "Y" го прати страницата за поръчки, иначе при "N" върни към начална страница)
	* * Поръчка на продукт --> Начална страница                  (накрая просто премини към начална страница)
	*
	*
	* Поток на Работа (Администратор)
	* * Начална страница --> ?                   (?)
	* TODO
	*/





private:
	/* data */
	Product * m_products[MAX_PRODUCTS_COUNT];
	int m_productsCount;

	Order* m_orders[MAX_ORDERS_COUNT];
	int m_ordersCount;

	User* m_users[MAX_USERS_COUNT];
	int m_usersCount;

};
