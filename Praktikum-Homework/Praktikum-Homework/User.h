#pragma once 
#include<iostream>
class User {
	int id;
	char* name;
	char* email;
	char* password;
	char* role;
	char* address;
public:
	User() {
		this->id = 0;
		this->name = nullptr;
		this->email = nullptr;
		this->password = nullptr;
		this->role = nullptr;
		this->address = nullptr;
		setName("guest");
		setEmail("guest");
		setPassword("guest");
		setRole("guest");
	}
	User(int id, const char*name, const char* email, const char* password, const char* role) {
		this->name = nullptr;
		this->email = nullptr;
		this->password = nullptr;
		this->role = nullptr;
		this->id = id;
		this->address = nullptr;
		setName(name);
		setEmail(email);
		setPassword(password);
		setRole(role);
	}
	int getId() const {
		return id;
	}
	char* getName()const {
		return name;
	}
	char* getEmail() const {
		return email;
	}
	char* getPassword()const {
		return password;
	}
	char* getRole() const {
		return role;
	}
	char* getAddress() const {
		return address;
	}

	void setName(const char* name) {

		if (strlen(name) <= 70) {
			if (this->name != nullptr) {
				delete[] this->name;
			}
			this->name = new char[strlen(name) + 1];
			strcpy(this->name, name);
		}
	}
	void setEmail(const char* email) {
		if (strlen(email) <= 70) {
			if (this->email != nullptr) {
				delete[] this->email;
			}
			this->email = new char[strlen(email) + 1];
			strcpy(this->email, email);
		}
	}
	void setPassword(const char* password) {
		if (strlen(password) <= 70) {
			if (this->password != nullptr) {
				delete[] this->password;
			}
			this->password = new char[strlen(password) + 1];
			strcpy(this->password, password);
		}
	}
	void setRole(const char* role) {
		if (strlen(role) <= 70) {
			if (this->role != nullptr) {
				delete[] this->role;
			}
			this->role = new char[strlen(role) + 1];
			strcpy(this->role, role);
		}
	}
	void setAddress(const char* address) {
		if (strlen(address) <= 70) {
			if (this->address != nullptr) {
				delete[] this->address;
			}
			this->address = new char[strlen(address) + 1];
			strcpy(this->address, address);
		}
	}
	~User() {
		delete[] name;
		delete[] email;
		delete[] password;
		delete[] role;
	}
};