// Praktikum-Homework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"BickieShop.h"
#include"View.h"
#include"RouteController.h"
#include"Guard.h"
#include"User.h"
#define warnings(disable)


//  NOTE
// TODO: NOT ENTIRE USER INPUT IS VALIDATED IF ENTERED UNEXPECTED CHAR -> may lead to program crash
// EditAccountView is fully validated
// If registered user does not have setted up address, and try to order, view asking for address i shown
// the address from the order is auto saved in profile
// If registerd user have setted up address, the user is NOT asked for address, while ordering
// The address is NOT validated by any form // id for data manipulation are fully protected agains illegal access
// and input validated 
// Guest users are always asked for shipping address ;)


// All possible combinations of views to construct and show page, 
//depending on user input and account type(admin ot user)
/*

View:showMainView->Route:IndexView()| Route:LoginView()| Route:RegisterView()| Route:StartView()
View:showIndexView->Route:ProductsListView()
View:showProductsListView->Route:lodOff() | Route:ProfileView() | Route:AdminMenuView() | Route:ProductDetailsView(answer)
View:showProductDetailsView->Route:OrderView | Route:IndexView()| Route:IndexView()
View:showErrorView-> return to call function
View:showMessageView->return to call function
View:showMessageViewNL ->return to call function
View:showMainView-> Route:IndexView()| Route:LoginView()|Route:RegisterView()|Route:StartView()
View:showLoginView->Route:loginUser()
View:showEditProfileView-> return to call function
View:showProfileView-> Route:indexView() | Route:editProfile()| Route:ProfileView()
View:showAskForAddressView-> return to call function
View:showOrderViewLogged()->Route:addOrderLogged()
View:showOrdersView-> return to call function
View:showAdminMenuView->Route:AllOrdersView| Route:EditOrder() | Route:AllccountsView()| Route:EditAccount()|Route:IndexView()|View:showErrorView()|Route:AdminMenuView()
View:showEditOrderView-> return to function call
View:showUsersListView->return to function call
View:showEditUserView->return to function call
View:showOrderView-> Route:addOrder()
View:showRegisterView()->Route:registerUser()

Route:ShowStartView -> View:showMainView
Route:StartView-> View:showIndexView() | showMainView()
Route:LoginView->View:showLoginView()| View:showErrorView()
Route:lodOff()->View:showMainView()
Route:IndexView()->View:showIndexView()
Route:ProductsListView()-> View->showProductsListView()
Route:ProductDetailsView-> View:showErrorView()|View->showIndexView()| View:showProductDetailsView
Route:OrderView->View:showOrderView()|View:showOrderViewLogged()
Route:RegisterView->showRegisterView()
Route:ProfileView->View:showProfileView()|View:showErrorView()| IndexView()
Route:editProfile->View:showEditProfileView()|View:showMessageViewNL()|Route:ProfileVIew()
Route:addOrder->View:showMessageView()|View:ShowMessageViewNL()|View:ShowIndexView()|View:ShowErrorView()
Route:addOrderLogged->View:showAskForAddressView()|View:showMessageViewNL()|View:showMessageView()|View:showIndexView()|View:showIndeView()
Route:registerUser->View:showMessageView()|View:showMainView()
Route:loginUser->View:showMessageView()|View:showMessageViewNL()|View:showIndexView()|View:showMainView()
// admin section
Route:AdminMenuView->View:showAdminMenuView()|View:showErrorView()|View:showIndexView()
Route:AllOrdersView->View:showMessageNL()|showIndexView()|View:showOrdersView()|View:showAdminMenuView()
Route:EditOrder->View:showEditOrderView()|View:showErrorView()|Route:AllOrdersView|View:showMessageViewNL()
Route:AllAcocuntsView->View:showUsersListView()|View:AdminMenuView()
Route:EditAccount->View:showEditUserView()|View:showErrorView()|View:showMessageViewNL()|Route:AllAccountsView()


*/
// To write comment in language different from the official of programmers- English is very bad
// Наличните потребители би било хубаво да пазим във база данни, в случая ще ги пазим в магазина
// BickieShop инстанцията ще играе ролята на нашата база данни, над която чрез методи на класа 
// симулираме извършването на заявки (може да се направи подобно на ORM - заявките да се извършват чрез методи на моделите)
// Информацията за вписаният потребител пазим в инстанция на Guard класа
// Има клас със разписани operator = и копи конструтор - order class
// Повечето критични за програма проверки са изнесени в RouteController
// Идеята : при модел клиент сървър, не може да се разчита на валидацията на views 
// Views валидирът на машината на клиента 

int main()
{
	User* user = new User();
	Guard* guard = new Guard(user);
	BickieShop* shop = new BickieShop();
	View* view = new View();
	RouteController* route = new RouteController(guard, shop);
	view->setRoute(route);
	route->setView(view);
	shop->addProduct((char*)"aome", 2.0, (char*)"The some of some.");
	shop->addProduct((char*)"bant Some", 10.0, (char*)"Quite expensive version of Some.");
	shop->addUser("Pesho", "pesho@gmail.com", "asd", "admin");
	shop->addOrder(2,(char*)"tuka nqkude", 0);
	shop->addOrder(1, (char*)"tamm",0);
	shop->findOrderById(4)->changeStatus();
	route->StartView();

    return 0;
}

