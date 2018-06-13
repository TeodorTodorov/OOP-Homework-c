#include "stdafx.h"
#include"RouteController.h"
#include"View.h"

RouteController::RouteController(Guard* _guard, BickieShop* _shop) {
	this->guard = _guard;

	//this->product = product;
	this->shop = _shop;
}
void RouteController::setView(View * view)
{
	viewP = view;
}
void RouteController::StartView() {
	if (!this->guard->isGuest()) {
		viewP->showIndexView();
	}
	else {
		viewP->showMainView();
	}

}
void RouteController::LoginView()
{
	if (this->guard->isGuest()) {
		viewP->showLoginView();
	}
	else {
		viewP->showErrorView("Logiview controller error");
	}
}
void RouteController::lodOff()
{
	guard->logOff();
	viewP->showMainView();
}
void RouteController::IndexView() {
	if (true) {
		viewP->showIndexView();
	}
}
void RouteController::ProductsListView() {
	if (true) {
		viewP->showProductsListView(shop->getProductsList(), shop->getProductCount());
	}
}
  
void RouteController::ProductDetailsView(int id) {
	if (id > -1) {

	}
	else {
		viewP->showErrorView("wrong id");
		viewP->showIndexView();
	}
	if (shop->findProductById(id) != nullptr) {
		viewP->showProductDetailsView(shop->findProductById(id));
	}
	else {
		viewP->showErrorView("there is no product with that id");
		IndexView();
	}
}

void RouteController::OrderView(Product* product) {
	if (guard->isGuest())
	{
		viewP->showOrderView(product);
	}
	else {
		viewP->showOrderViewLogged(product);
	}

}
void RouteController::RegisterView() {
	viewP->showRegisterView();
}

void RouteController::ProfileView()
{
	if (!guard->isGuest())
	{
		char* name = guard->getCurrentUser()->getName();
		char* address = guard->getCurrentUser()->getAddress();

		viewP->showProfileView(name, address);
	}
	else {
		viewP->showErrorView("you are logged as a guest you could not edit your profile");
		IndexView();
	}

}

void RouteController::editProfile()
{
	char  name[70]; char address[70];
	viewP->showEditProfileView(name, address);
	guard->getCurrentUser()->setAddress(address);
	guard->getCurrentUser()->setName(name);
	viewP->showMessageViewNL("Profile updates");
	ProfileView();



}

void RouteController::addOrder(int id, char* address) {
	if (id > -1) {
		shop->addOrder(id, address, guard->getCurrentUser()->getId());
		viewP->showMessageViewNL();
		viewP->showMessageView("Your order will be shipped to:");
		viewP->showMessageViewNL(address);
		viewP->showIndexView();
	}
	else {
		viewP->showErrorView("wrong id");
		viewP->showIndexView();

	}

}
void RouteController::addOrderLogged(int id)
{
	if (guard->isUser() || guard->isAdmin())
	{
		if (guard->getCurrentUser()->getAddress() == nullptr) {
			char buf[70];
			viewP->showAskForAddressView(buf);
			guard->getCurrentUser()->setAddress(buf);
		}
		shop->addOrder(id, guard->getCurrentUser()->getAddress(), guard->getCurrentUser()->getId());
		viewP->showMessageViewNL();
		viewP->showMessageView("Your order will be shipped to:");
		viewP->showMessageViewNL(guard->getCurrentUser()->getAddress());
		viewP->showMessageViewNL("WE PLACE YOUR ORDER .. Redirect to index...");
		viewP->showIndexView();


	}
	else {
		viewP->showErrorView("addOrderLogged Error");
		viewP->showIndexView();
	}
}
void RouteController::registerUser(const  char*name, const char* email, const char* password) {
	const char* role = "user";
	shop->addUser(name, email, password, role);
	viewP->showMessageView("You are register successfull");
	viewP->showMainView();

}

void RouteController::loginUser(const char * email, const char * password)
{
	if (shop->authUser(email, password, guard)) {
		viewP->showMessageView("WELCOME");
		viewP->showMessageView(guard->getCurrentUser()->getName());
		viewP->showMessageViewNL();
		viewP->showIndexView();
	}
	else {
		viewP->showMessageView("Wrong Credentials... Redirect to start page");
		viewP->showMessageViewNL();
		viewP->showMainView();
	}


	// ===========ADMIN SECTION =================
	// ADD ADMIN GUARD T|o methods below


}

void RouteController::AdminMenuView()
{

	if (guard->isAdmin())
	{
		viewP->showAdminMenuView();
	}
	else {
		// display error message
		viewP->showErrorView("YOU ARE NOT ADMIN BITCH");
		viewP->showIndexView();
	}

}

void RouteController::AllOrdersView(char n)
{
	if (guard->isAdmin())
	{
		if (n == '0') {
		}
		if (n == '1') {

			shop->SortOrdersByStatus();
		}
		if (n == '6') {
			shop->SortOrdersByProductName();
		}
	}
	else {
		viewP->showMessageViewNL("You do not have the rights");
		viewP->showIndexView();
	}
	viewP->showMessageView("Orders are");
	viewP->showOrdersView(shop->getOrdersList(), shop->getOrderCount());
	viewP->showAdminMenuView();

}

void RouteController::EditOrder()
{
	if (guard->isAdmin()) {
		int id;
		int n;
		viewP->showEditOrderView(&id, &n);
		if (shop->findOrderById(id) != nullptr)
		{
			if (((int)shop->findOrderById(id)->getStatus() + n) <= 3)
			{
				for (int i = 0; i < n; i++)
				{
					shop->findOrderById(id)->changeStatus();
				}
			}
			else
			{
				viewP->showErrorView("Incorrect change size");
				AllOrdersView('0');
			}
		}
		else {
			viewP->showErrorView("Incorrect order id");
			AllOrdersView('0');
		}

	}
	viewP->showMessageViewNL("Order edited");
	AllOrdersView('0');
}

void RouteController::AllAccountsView()
{
	viewP->showUsersListView(shop->getUsersList(), shop->getUsersCount());
	AdminMenuView();
}

void RouteController::EditAccount()
{
	int id;
	bool admin;
	viewP->showEditUserView(&id, &admin);
	if (shop->findUserById(id) != nullptr) {

		if (admin == true) {
			shop->findUserById(id)->setRole("admin");
			viewP->showMessageViewNL("User edited successfull");
		}
		else {
			shop->findUserById(id)->setRole("user");
			viewP->showMessageViewNL("User edited successfull");
		}

	}

	else {
		viewP->showErrorView("incorrect id ;)");
	}

	AllAccountsView();
}

void RouteController::showAllUserOrders()
{
	if (guard->isUser() || guard->isAdmin())
	{
		Order** orders = new Order*[shop->getOrderCount()];
		int ordersSize = shop->filterUserOrders(orders, guard->getCurrentUser()->getId());
		viewP->showAllUserOrders(orders, ordersSize);
		delete[] orders;

	}
	else {
		viewP->showErrorView("Only for logged user");
		IndexView();
	}
}

void RouteController::deleteOrder(int c)
{
	if (guard->isUser() || guard->isAdmin()) {
		Order* order = shop->findOrderById(c);
		if (order != nullptr)
		{
			if (order->getUserId() == guard->getCurrentUser()->getId())
			{
				shop->removeOrder(c);
				viewP->showMessageViewNL("Order removed successfull");
				showAllUserOrders();
			}
			else {
				viewP->showErrorView("this is not of your orders!");
				showAllUserOrders();
			}
		}
		else {
			viewP->showErrorView("Order with that id does not exist");
			showAllUserOrders();
		}
	}
	else {
		// error log
		//should not have acces to here
		// flash error message
	}

}
