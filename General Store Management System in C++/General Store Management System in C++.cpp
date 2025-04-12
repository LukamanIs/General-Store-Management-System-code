#include <iostream>
#include <fstream>

using namespace std;

class temp {
	string itemID, itemName;
	int itemQuantity, ItemPrice;
	fstream file;
    public:
		void addProduct(void);
		void viewProduct(void);
		void buyProduct(void);
}obj;

int main() {

	char choice;

	cout << "press 1 --> Start shoping";
	cout << "press 0 __> Exit:";
	cin >> choice;
	switch (choice)
	{
	case 'A':
		
		break;
	case 1:

		break;
	case 0:
		system("exit");
		break;

	default:
		cout << "Invalide Selection...!";
		break;
	}



	return 0;
}


void temp::addProduct() {


}

void temp::viewProduct() {


}

void temp::buyProduct() {


}