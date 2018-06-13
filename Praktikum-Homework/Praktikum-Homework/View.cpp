#include "stdafx.h"
#include"View.h"
#include"RouteController.h"
#include"User.h"
#include <windows.h>
View::View() {
	routeC = NULL;
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 24;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
};

void View::setRoute(RouteController* _route) {
	routeC = _route;
	
};

void View::showIndexView()
{
	cout << endl;
	cout << "Hello and prego! This is our small seduction shop where anyone can find their threats!" << endl;

	// TODO improve with more complex logic
	// Choose what to do:
	// - orders
	// - products list
	// - something else...
	routeC->ProductsListView();
};

void View::showProductsListView( Product** products, int count)
{
	cout << endl;
	cout << "Here's a list of our sinful chocolate enjoyments:" << endl;

	for (int i = 0; i < count; ++i) {
		cout << "<------>" << endl;
		cout << "Product id: " << products[i]->getId() << endl;
		cout << "Name: " << products[i]->getName() << endl;
		cout << "Price: " << products[i]->getPrice() << endl;
		/// Description is visible only from the detailed view
		cout << ">------<" << endl;
	}

	int answer;
	cout << "Do you what to buy anything? Choose a product to see details (by id). Use -1 for Profile, Use -2 for Admin, -3 All orders Use '0' for exit:" << endl;
	cin >> answer;

	// could be shortened to: !answer
	if (answer == 0) {
		cout << "loggind off";
		routeC->lodOff();
	}else 
		if (answer == -1) {
			cout << "Going to Profile...";
			routeC->ProfileView();
		}
	if (answer == -2) {
		cout << "Going to Admin...";
		routeC->AdminMenuView();
	}
	if (answer == -3) {
		cout << "Going to Orders list...";
		routeC->showAllUserOrders();
	}
	else {
		// XXX could a product by the id be missing? What should we do?
		// Възможно ли е продукт с конкретен идентификатор да липсва?
		routeC->ProductDetailsView(answer);
	}
};

void View::showProductDetailsView(Product* product)
{
	cout << endl;
	cout << "======" << endl;
	cout << "===== " << product->getName() << " =====" << endl;
	cout << "Details : " << product->getDescription() << endl;
	cout << "Price: " << product->getPrice() << endl;

	char answer;
	cout << "Do you want to buy it (y/n)?" << endl;
	cin >> answer;

	// Some logic for the buying. Is this user intuitive?
	switch (answer) {
	case 'Y':
	case 'y':
		cout << "Going to order view..." << endl;
		routeC->OrderView(product);
		break;
	case 'N':
	case 'n':
		cout << "Going back to main..." << endl;
		routeC->IndexView();
	default:
		cout << "Bad option" << endl;
		routeC->IndexView();
	}
};
void View::showErrorView(const char* message) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	cout << message;
	SetConsoleTextAttribute(hConsole, 15);
};
void View::showMessageView(const char* message) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 9);
	cout << message;
	SetConsoleTextAttribute(hConsole, 15);
}
void View::showMessageViewNL(const char * message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 9);
	cout << message << endl;
	SetConsoleTextAttribute(hConsole, 15);
}
void View::showMainView()
{
	cout << "============ ============= ==============" << endl;
	cout << "Hello Candy Lover, choose and action" << endl;
	cout << "[1]: continue as GUEST" << endl;
	cout << "[2] login" << endl;
	cout << "[3] registre" << endl;
	char choice;
	cin >> choice;
	cout << " i read :" << choice << endl;
	if (choice == '1') {
		routeC->IndexView();
	}
	else if (choice == '2') {
		routeC->LoginView(); 
	}
	else if (choice == '3') {
		routeC->RegisterView();
	}
	else {
		routeC->StartView();
	}
}
void View::showLoginView()
{
	cout << endl;
	cout << "============ ============= ==============" << endl;
	cout << "You are about to LOGIN: " << endl;

	char email[70];
	char password[70];

	cout << "Please enter your email:" << endl;
	cin.ignore();
	cin.getline(email, 70, '\n');
	cout << "Please enter your password:" << endl;

	cin.getline(password, 70, '\n');
	routeC->loginUser(email, password);
}
void View::showEditProfileView(char name[70], char address[70]) {
	cout << "Enter your credentials:" << endl;
	
	cout << "New Name:";
	cin.ignore();
	cin.getline(name, 70, '\n');
	cout << "New Address:";
	cin.getline(address, 70, '\n');
	
}
void View::showProfileView(char* name, char* address)
{
	cout << endl;
	cout << "============ ============= ==============" << endl;
	cout << "This is your profile " << endl;
	cout << "Name:" << name << endl << "Address:";
	if (address != nullptr) {
		cout << address << endl;
	}
	cout << "To edit your name and address type 2, to return to index page type 1: ";
	char c; cin >> c;
	if (c =='1')
	{
		routeC->IndexView();
	}
	else if (c == '2')
	{
		routeC->editProfile();
	}
	else {
		showErrorView("no such option");
		routeC->ProfileView();
	}
	

}
void View::showAskForAddressView(char buffer[70])
{
	cout << "============ ============= ==============" << endl;
	cout << "give me your adddress to place your order:";
	

	
	/// Get rid of any extra characters: https://stackoverflow.com/a/1744756
	cin.ignore();
	cin.getline(buffer, 70, '\n');
	
}
;

void View::showOrderViewLogged(Product* product)
{
	cout << endl;
	cout << "============ orderViewLogged============= ==============" << endl;
	
	cout << "Total price: " << product->getPrice() << endl;

	

	
	/// Get rid of any extra characters: https://stackoverflow.com/a/1744756
	
	
	
	routeC->addOrderLogged(product->getId());


	// How about...?
	/* cout << "Please enter your name:" << endl; */
	/* cin.getline(buffer, 200, '\n'); */
}
void View::showAllUserOrders(Order** items, int n)
{
	cout << "============All your orders==============" << endl;
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "id: ";
		cout << items[i]->getId() << endl;
		cout << "product id: ";
		cout << items[i]->getProductId() << endl;
		cout << "Shipping address: ";
		cout << items[i]->getAddress() << endl;
		cout << "Order status: " << endl;
		switch (items[i]->getStatus())
		{
		case 1: cout << "SHIPPED"; break;
		case 2: cout << "WAITING"; break;
		case 3: cout << "DELIVERED"; break;
		default: 
			// program logic error
			/// error logger here
			break;
		}
		cout << endl;
		cout << "--------------------------------------" << endl;
	}
	cout << "Type -1 to return to index page, typе order id to cancel it ";
	int c;
	cin >> c;
	bool flag = true;
	while (flag) {
		if (c == -1)
		{
			flag = false;
			routeC->IndexView();
		}
		else {
			routeC->deleteOrder(c);
		}
	}
	
}
void View::showOrdersView(Order ** orders, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "Order" << endl;
		cout << endl;
		cout << "Order ID:"  << orders[i]->getId();
		cout << " Status:" << orders[i]->getStatus() << "  " << "ProdictId:" << orders[i]->getProductId() <<
			"  " << "Shipping Address:" << orders[i]->getAddress() << endl;
		cout << "----------------------------------" << endl;

	}
}
void View::showAdminMenuView()
{
	cout << endl;
	cout << "============ Admin view============= ==============" << endl;
	cout << "Enter 1 to display all orders"<< endl<<" enter 2 to display all oders sorted by status || "<<endl<<"6 to display all oders sorted by productName  ||  " << endl;
	cout << "Enter 3 Order edit mode  ||  " << endl << "Enter 4 to display all accounts  ||  " << endl;
	cout << "Enter 5 to Account edit mode" << endl;
	cout << "  ||  Enter 7 RETURN TO INDEX" << endl;
	char c;
	cin.ignore();
	cin >> c;
	switch (c) {
	case '1': routeC->AllOrdersView('0'); break;
	case '2': routeC->AllOrdersView('1'); break;
	case '6': routeC->AllOrdersView('6'); break;
	case '3': routeC->EditOrder(); break;
	case '4':  routeC->AllAccountsView(); break;
	case '5': routeC->EditAccount(); break;
	case '7':routeC->IndexView(); break;
	default: 
		showErrorView("no such a option");
		routeC->AdminMenuView();
	};

}
void View::showEditOrderView(int* id, int * n)
{
	
	cout << "Enter order id : "; cin >> *id; cout << endl;
	cout << "Enter status digit change: "; cin >> *n; cout<< endl;
}
void View::showUsersListView(User ** users, int count)
{
	cout << "===============Users List ==================" << endl;
	for (int i = 0; i < count; i++)
	{

		cout << "id:" << users[i]->getId() << " " << "name:" << users[i]->getName() << " ";
		cout << "address:" << " "; if (users[i]->getAddress() != nullptr) {
			cout << users[i]->getAddress();
		} cout << " " << "email:" << users[i]->getEmail() << " ";
			cout << "role:" << users[i]->getRole() << endl;
			cout << "-------------------------" << endl;
	}
}
void View::showEditUserView(int * id, bool * n)
{
	char admin;
	bool flag = true;
	cout << "Enter user id : "; cin >> *id; cout << endl;
	
	while (flag)
	{
		cout << "Enter 1 for admin, 0 for normal user: ";
		cin >> admin;
		if (admin == '1')
		{
			*n = true;
			flag = false;
		}
		else if (admin == '0') {
			*n = false;
			flag = false;
		}

	}
}
;




void View::showOrderView(Product* product)
{
	cout << endl;
	cout << "============ ============= ==============" << endl;
	cout << "You are about to buy: " << product->getName() << endl;
	cout << "Total price: " << product->getPrice() << endl;

	char buffer[200];

	cout << "Please enter your address:" << endl;
	/// Get rid of any extra characters: https://stackoverflow.com/a/1744756
	cin.ignore();
	cin.getline(buffer, 200, '\n');

	cout << "Great! We will contact you shortly to check you order. Thank you for choosing our shop!" << endl;
	routeC->addOrder(product->getId(), (char*)buffer);


	// How about...?
	/* cout << "Please enter your name:" << endl; */
	/* cin.getline(buffer, 200, '\n'); */
};

void View::showRegisterView() {
	// TODO REQUIRE UNIQUE EMAILS
	cout << endl;
	cout << "============ ============= ==============" << endl;
	cout << "You are about to REGISTER: " << endl;
	char name[70];
	char email[70];
	char password[70];

	cout << "Please enter your name:" << endl;
	/// Get rid of any extra characters: https://stackoverflow.com/a/1744756
	cin.ignore();
	cin.getline(name, 70, '\n');
	cout << "Please enter your email:" << endl;
	
	cin.getline(email, 70, '\n');
	cout << "Please enter your password:" << endl;
	
	cin.getline(password, 70, '\n');
	routeC->registerUser(name, email, password);


};

