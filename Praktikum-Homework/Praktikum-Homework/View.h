#pragma once
#include<iostream>
#include"Product.h"
#include"Order.h"
#include"User.h"

using namespace std;

class RouteController;
class View {
	RouteController* routeC;
public:
	View();
	void setRoute(RouteController* route);
	void showIndexView();
	void showRegisterView();
	void showProductsListView( Product** products, int count);
	void showProductDetailsView(Product* product);
	void showOrderView(Product* product);
	void showErrorView(const char* message);
	void showMessageView(const char* message);
	void showMessageViewNL(const char* message ="");
	void showMainView();
	void showLoginView();
	void showEditProfileView(char name[70], char address[70]);
	void showProfileView(char*name, char* address);
	void showAskForAddressView(char[70]);
	void showOrderViewLogged(Product * product);
	void showAllUserOrders(Order** items, int n);
	// Admin views
	//void showEditProductView(Product& product); // TODO
	void showOrdersView( Order** orders,int n);        
	void showAdminMenuView();
	void showEditOrderView(int* id, int * n);
	void showUsersListView(User**, int count);
	void showEditUserView(int* id, bool * n);
	
	// ...


};



