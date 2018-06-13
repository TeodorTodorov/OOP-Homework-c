#include "stdafx.h"
#include "Order.h"
#include<iostream>

Order::Order(const Order& ot)
{
	copy(ot);
}

char * Order::getAddress() const
{
	return m_address;
}

int Order::getProductId() const
{
	return m_productId;
}

int Order::getId() const
{
	return this->m_id;
}

int Order::getUserId() const
{
	return m_user_id;
}

OrderStatus Order::getStatus() const
{
	return m_status;
}

Order & Order::operator=(const Order & ot)
{
	if (this != &ot) {
		delete[] m_address;
		copy(ot);
	}
	 
	return *this;
}

void Order::changeStatus()
{
	 m_status = (OrderStatus)((int)m_status + 1);
}

void Order::copy(const Order& ot)
{
	//char* mineaddress = m_address;
	m_address = new char[strlen(ot.getAddress()) + 1];
	std::strcpy(m_address, ot.getAddress());
	m_id = ot.getProductId();
	this->m_id = ot.m_id;
	this->m_productId = ot.m_productId;
	this->m_status = ot.m_status;
	this->m_user_id = ot.m_user_id;
	
}
