#pragma once
#include<iostream>
class Product {
public:
	Product(int id, char* name, double price, char* desciption)
		: m_id(id)
		, m_price(price)
	{
		// simply copy of the restricted in size name
		setName(name);

		// dynamic...
		setDescription(desciption);
	}
	~Product()
	{
		delete[] m_description;
	}

	/*
	* Mutators and selectors
	*/
	int getId() const
	{
		return m_id;
	}

	double getPrice() const
	{
		return m_price;
	}

	void setPrice(double price)
	{
		m_price = price;
	}

	char* getName() const
	{
		return (char*)m_name;
	}
	void setName(char* name)
	{
		strcpy(m_name, name);
	}

	char* getDescription() const
	{
		return m_description;
	}
	void setDescription(char* description)
	{
		// Now lets see how we manage dynamic string
		// should be safe even if nullptr: https://stackoverflow.com/a/6731484
		delete[] m_description;
		// + 1 for the '\0' character
		m_description = new char[strlen(description) + 1];
		strcpy(m_description, description);
	}

private:
	/* data */
	int m_id;
	double m_price;
	char m_name[100];
	char* m_description;
};