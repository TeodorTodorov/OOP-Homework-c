#pragma once
#include<iostream>
enum OrderStatus {
	SHIPPED,
	WAITING,
	DELIVERED
};

/// Represents a customer's order in our shop
class Order {
public:
	Order(int id, int productId, char* address, int userId)
		: m_id(id)
		, m_productId(productId), 
		m_user_id(userId)
	{

		//m_status = OrderStatus::WAITING;
		m_status = WAITING;

		// manage simple dynamic string
		m_address = new char[strlen(address) + 1];
		strcpy(m_address, address);
	}
	Order(const Order& ot);
	~Order()
	{
		
	}

	// XXX not implemented
	char* getAddress() const;
	int getProductId() const;
	int getId() const;
	int getUserId() const;
	OrderStatus getStatus() const;
	Order& operator = ( const Order& ot);

	// Go to next possible status
	void changeStatus();

private:
	int m_user_id;
	int m_id;
	char* m_address;
	int m_productId;
	OrderStatus m_status;
	void copy(const Order& ot);
};