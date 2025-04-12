#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

class Shop {
    string itemID, itemName;
    int itemQuantity, itemPrice;
    fstream file;
    int totalAmount = 0, quantity, itemRate;
    string searchID;
    char continueChoice;

public:
    void addProduct();
    void viewProducts();
    void buyProduct();
    void clearAllData();
} obj;

int main() {
    char choice;

    do {
        cout << "\n======= Welcome to the Shop =======\n";
        cout << "A - Add Product\n";
        cout << "1 - Start Shopping\n";
        cout << "C - Clear All Data\n";
        cout << "0 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        choice = tolower(choice);

        switch (choice) {
        case 'a':
            obj.addProduct();
            break;
        case '1':
            obj.viewProducts();
            obj.buyProduct();
            return 0; // End after shopping
        case 'c':
            obj.clearAllData();
            break;
        case '0':
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid selection. Please try again.\n";
            break;
        }

    } while (choice != '0');

    return 0;
}

void Shop::addProduct() {
    while (true) {
        cout << "\n=== Add a New Product ===" << endl;

        cout << "Enter Product ID: ";
        cin >> itemID;

        cin.ignore();
        cout << "Enter Product Name: ";
        getline(cin, itemName);

        cout << "Enter Product Quantity: ";
        while (!(cin >> itemQuantity)) {
            cout << "Invalid number. Try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "Enter Product Price: ";
        while (!(cin >> itemPrice)) {
            cout << "Invalid number. Try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        file.open("data.txt", ios::out | ios::app);
        if (!file) {
            cerr << "Error opening file for writing.\n";
            return;
        }

        file << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
        file.close();

        cout << "Product added successfully.\n";

        char addMore;
        while (true) {
            cout << "Do you want to add another product? (Y/N): ";
            cin >> addMore;
            addMore = tolower(addMore);
            cin.ignore(1000, '\n');

            if (addMore == 'y') {
                break;
            }
            else if (addMore == 'n') {
                cout << "Returning to main menu...\n";
                return;
            }
            else {
                cout << "Invalid input. Please enter Y or N.\n";
            }
        }
    }
}

void Shop::viewProducts() {
    cout << "\n=== Product List ===" << endl;
    file.open("data.txt", ios::in);

    if (!file) {
        cout << "No product data found.\n";
        return;
    }

    bool hasProducts = false;
    while (file >> itemID >> itemName >> itemQuantity >> itemPrice) {
        hasProducts = true;
        cout << "----------------------------------------\n";
        cout << "Product ID     : " << itemID << endl;
        cout << "Product Name   : " << itemName << endl;
        cout << "Quantity       : " << itemQuantity << endl;
        cout << "Product Price  : $" << itemPrice << endl;
    }

    if (!hasProducts) {
        cout << "No products available.\n";
    }

    file.close();
}

void Shop::buyProduct() {
    continueChoice = 'y';
    totalAmount = 0;

    ofstream receipt("temp.txt");
    receipt << "RECEIPT\n";
    receipt << "-------------------------------\n";

    while (tolower(continueChoice) == 'y') {
        file.open("data.txt", ios::in);
        ofstream updatedFile("temp_data.txt");

        if (!file || !updatedFile || !receipt) {
            cerr << "Error accessing files.\n";
            return;
        }

        cout << "\nEnter Product ID to buy: ";
        cin >> searchID;

        cout << "Enter Quantity: ";
        while (!(cin >> quantity)) {
            cout << "Invalid number. Try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        bool productFound = false;

        while (file >> itemID >> itemName >> itemQuantity >> itemPrice) {
            if (itemID == searchID) {
                productFound = true;

                if (quantity > itemQuantity) {
                    cout << "Not enough stock. Only " << itemQuantity << " available.\n";
                    updatedFile << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
                }
                else {
                    int remainingQty = itemQuantity - quantity;
                    int total = quantity * itemPrice;
                    totalAmount += total;

                    cout << "\n--- Payment Summary ---" << endl;
                    cout << "You bought " << quantity << " of " << itemName << endl;
                    cout << "Amount for this item: $" << total << endl;
                    cout << "Total so far: $" << totalAmount << endl;

                    receipt << "Item: " << itemName << endl;
                    receipt << "Quantity: " << quantity << endl;
                    receipt << "Unit Price: " << itemPrice << endl;
                    receipt << "Total: " << total << endl;
                    receipt << "-------------------------------\n";

                    updatedFile << itemID << "\t" << itemName << "\t" << remainingQty << "\t" << itemPrice << endl;
                }
            }
            else {
                updatedFile << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
            }
        }

        file.close();
        updatedFile.close();
        remove("data.txt");
        rename("temp_data.txt", "data.txt");

        if (!productFound) {
            cout << "Product ID not found.\n";
        }

        while (true) {
            cout << "Do you want to continue shopping? (Y/N): ";
            cin >> continueChoice;
            continueChoice = tolower(continueChoice);
            cin.ignore(1000, '\n');

            if (continueChoice == 'y' || continueChoice == 'n') {
                break;
            }
            else {
                cout << "Invalid input. Please enter Y or N.\n";
            }
        }
    }

    if (tolower(continueChoice) == 'n') {
        receipt << "Total Purchase Amount: $" << totalAmount << endl;
        receipt.close();

        cout << "\nThank you for shopping.\n";
        cout << "Total Purchase Amount: $" << totalAmount << endl;
        cout << "A receipt has been saved to 'temp.txt'.\n";
    }
}

void Shop::clearAllData() {
    file.open("data.txt", ios::out | ios::trunc);
    file.close();

    ofstream clearReceipt("temp.txt", ios::out | ios::trunc);
    clearReceipt.close();

    cout << "All product data has been cleared.\n";
}
