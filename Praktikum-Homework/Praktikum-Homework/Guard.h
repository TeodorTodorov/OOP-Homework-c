#pragma once
#include<iostream>
#include"User.h"
class Guard {
	User* currentUser;
	User* guestAccount;
public:
	Guard(User* user) {
		currentUser = user;
		guestAccount = user;
	}
	void setCurrentUser(User* user) {
		currentUser = user;
	}
	void logOff() {
		currentUser = guestAccount;
	}
	 User* getCurrentUser() {
		return currentUser;
	}
	bool isAdmin() {
		char * userRole = currentUser->getRole();
		if (std::strcmp(userRole, "admin")==0) {
			return true;
		}
		return false;
	}

	bool isGuest() {
		char * userRole = currentUser->getRole();
		if (std::strcmp(userRole, "guest") == 0) {
			return true;
		}
		return false;
	}
	bool isUser() {
		char * userRole = currentUser->getRole();
		if (std::strcmp(userRole, "user")==0) {
			return true;
		}
		return false;
	}


	~Guard();

};