#pragma once
#include"Guard.h"
#include"BickieShop.h"


//#include"GLOBAL.h"


//class Views {
//
//public: 
//	Views();
//	void setRoute(RouteController* route);
//	void showIndexView();
//	void showRegisterView();
//	void showProductsListView(Product** products, int count);
//	void showProductDetailsView(Product* product);
//	void showOrderView(Product* product);
//	void showErrorView(const char* message);
//	void showMessageView(const char* message);
//};





// TODO: CREATE REQUEST CLASS , VALIDATE THE REQUEST , CREATE AUTH GUARD CLASS , AND THEN INJECT IN ROUTERCONTROller
class View;
class RouteController {
private:
	Guard * guard;
	//Product* product;
	View* viewP;
	BickieShop* shop;


public:


	RouteController(Guard * _guard, BickieShop * _shop);
	void setView(View* view);

	void StartView();
	void LoginView();
	void lodOff();
	void ProductsListView();

	void IndexView();

	void ProductDetailsView(int id);

	void OrderView(Product* product);

	void RegisterView();
	
	void ProfileView();
	void editProfile();

	void addOrder(int id, char * address);
	void addOrderLogged(int id);

	void registerUser(const char * name, const char * email, const char * password);

	void loginUser(const char * email, const char * password);
	void AdminMenuView();
	void AllOrdersView(char n);
	void EditOrder();
	void AllAccountsView();
	void EditAccount();
	void showAllUserOrders();
	void deleteOrder(int c);
};
