#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;


struct Product {
    int id;
    string name;
    int price;
};


struct CartItem {
    int productID;
    Product Name;
    int quantity;
};


class Customer {
private:
    string name;
    string address;
    string phoneNumber;

public:
    Customer() = default;

    Customer(string n, string a, string p)
        : name(n), address(a), phoneNumber(p) {
    }

    void displayInfo() const {
        cout << "Customer Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phoneNumber << endl;
    }

    string getName() const { return name; }
    string getAddress() const { return address; }
    string getPhoneNumber() const { return phoneNumber; }
};


class StoreBase {
public:
    void Display_Products() {
        cout << "Displaying products from StoreBase.\n";
    }
};





class shipzy_store : public StoreBase {
private:
    vector<Product> products = {
        {111, "Smart Watch", 200},
        {222, "Bluetooth Speaker", 300},
        {333, "Power Bank", 60},
        {444, "Wireless Mouse", 140},
        {555, "LED Lamp", 100}
    };

    vector<CartItem> cart;

public:
    void run() {
        int Num;
        while (true) {
            cout << "\n====================================\n";
            cout << " Welcome to your Shipzy Store \n";
            cout << "====================================\n";
            cout << "    Menu:\n";
            cout << "1: Create Account\n";
            cout << "2: Login\n";
            cout << "3: Display All Products\n";
            cout << "4: Search Product by Name\n";
            cout << "5: Buy Products\n";
            cout << "6: Cancel Products\n";
            cout << "7: Calculate Total\n";
            cout << "8: Forgot Password\n";
            cout << "9: Exit Store\n";
            cout << "------------------------------------\n";
            cout << "Powered by: Shrouk Saeed\n";
            cout << "====================================\n";
            cout << "Enter your choice: ";
            
            if (!(cin >> Num)) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore();

            switch (Num) {
            case 1:
                Create_Account();
                break;
            case 2:
                Login();
                break;
            case 3:
                Display_Products();
                break;
            case 4: {
                string productName;
                cout << "Enter product name to search: ";
                getline(cin, productName);
                Display_Products(productName);
                break;
            }
            case 5:
                Buy_Products();
                break;
            case 6:
                Cancel_Products();
                break;
            case 7:
                Calculate_Total();
                break;
            case 8:
                Forgot_Password();
                break;
            case 9:
                cout << "Thank you for visiting Shipzy Store\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        }
    }

    void Create_Account() {
        char username[100], password[100], email[100];
        string address, phone;

        cout << "Enter your username: ";
        cin.getline(username, sizeof(username));

        cout << "Enter your email: ";
        cin.getline(email, sizeof(email));

        if (strstr(email, "@gmail.com") == nullptr) {
            cout << "Invalid email format. Must include '@gmail.com'\n";
            return;
        }

        cout << "Enter your password (min 8 characters): ";
        cin.getline(password, sizeof(password));
        if (strlen(password) < 8) {
            cout << "Password is too short.\n";
            return;
        }

        cout << "Enter your address: ";
        getline(cin, address);
        cout << "Enter your phone number: ";
        getline(cin, phone);

        Customer newCustomer(username, address, phone);

        ofstream file("data.txt", ios::app);
        file << username << " " << email << " " << password << " " << address << " " << phone << endl;
        file.close();

        cout << "Account created successfully!\n";
        newCustomer.displayInfo();
    }

    void Login() {
        string username, password, email, storedUsername, storedPassword, storedEmail, skip1, skip2;

        cout << "Enter your username: ";
        getline(cin, username);
        cout << "Enter your email: ";
        getline(cin, email);
        cout << "Enter your password: ";
        getline(cin, password);

        ifstream file("data.txt");
        if (!file) {
            cout << "Error: Could not open the file!" << endl;
            return;
        }

        bool loginSuccess = false;
        while (file >> storedUsername >> storedEmail >> storedPassword >> skip1 >> skip2) {
            if (storedUsername == username && storedPassword == password && storedEmail == email) {
                loginSuccess = true;
                break;
            }
        }
        file.close();

        if (loginSuccess) {
            cout << "Login successful!\n";
        }
        else {
            cout << "Invalid username or password.\n";
        }
    }


    void Display_Products() {
        cout << "\nAvailable Products:\n----------------------------\n";
        for (const auto& product : products) {

            cout << "Product ID: " << product.id
                << " | Name: " << product.name
                << " | Price: $" << product.price << "\n";
        }

        cout << "----------------------------\n";
    }


    void Display_Products(const string& productName) {
        cout << "Searching for product: " << productName << endl;

        for (const auto& product : products) {
            if (product.name == productName) {
                cout << "ID: " << product.id << " | Name: " << product.name << " | Price: $" << product.price << endl;
                return;
            }
        }
        cout << "Product not found.\n";
    }



    void Buy_Products() {
        int productID, quantity;
        char addMore = 'y';

        while (addMore == 'y' || addMore == 'Y') {
            cout << "Enter the Product ID you want to buy: ";
            cin >> productID;
            cout << "Enter the quantity: ";
            cin >> quantity;

            bool found = false;
            for (const auto& product : products) {
                if (product.id == productID) {
                    cart.push_back({ productID, product, quantity });
                    cout << product.name << " (x" << quantity << ") added to your cart.\n";
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Invalid Product ID.\n";
            }

            cout << "Add another product? (y/n): ";
            cin >> addMore;
        }

        int total = 0;
        for (const auto& item : cart) {
            for (const auto& product : products) {
                if (product.id == item.productID) {
                    total += product.price * item.quantity;
                }
            }
        }
        cout << "Total: $" << total << "\n\n";
    }

    void Cancel_Products() {
        if (cart.empty()) {
            cout << "Your cart is empty.\n";
            return;
        }

        cout << "Your cart contains:\n";
        for (int i = 0; i < cart.size(); ++i) {
            cout << i + 1 << " Product ID = " << cart[i].productID << "\n";
            cout << i + 1 << " Name = " << cart[i].Name.name << "\n";
            cout << i + 1 << " Quantity = " << cart[i].quantity << "\n";
        }

        int choice;
        cout << "Enter the number of the product you want to cancel: ";
        cin >> choice;

        if (choice < 1 || choice > cart.size()) {
            cout << "Invalid choice.\n";
            return;
        }

        CartItem* itemToDelete = &cart[choice - 1];
        cout << "Removing: Product ID = " << itemToDelete->productID
            << " , Name = " << itemToDelete->Name.name
            << ", Quantity = " << itemToDelete->quantity << "\n";

        cart.erase(cart.begin() + (choice - 1));
        cout << "Product removed from cart successfully.\n";

        int total = 0;
        for (const auto& item : cart) {
            for (const auto& product : products) {
                if (product.id == item.productID) {
                    total += product.price * item.quantity;
                }
            }
        }
        cout << "Total after removing: $" << total << "\n\n";
    }

    void Calculate_Total() {
        int total = 0;
        int totalQuantity = 0;
        int ShippingCosts = 100;

        for (const auto& item : cart) {
            for (const auto& product : products) {
                if (product.id == item.productID) {
                    total += product.price * item.quantity;
                    totalQuantity += item.quantity;
                }
            }
        }

        int grandTotal = total + ShippingCosts;

        cout << "===============================================\n";
        cout << "Total: $" << total << "\n";
        cout << "Shipping Costs: $" << ShippingCosts << "\n";
        cout << "Grand Total: $" << grandTotal << "\n";
        cout << "Total Quantities: " << totalQuantity << "\n";


        if (!cart.empty()) {
            CartItem lastItem = cart.back();
            cout << "Last Product ID: " << lastItem.Name.id << "\n";
            cout << "Name of Last Product: " << lastItem.Name.name << "\n";
            cout << "Price of Last Product: $" << lastItem.Name.price << "\n";
        }
        else {
            cout << "Cart is empty.\n";
        }

        cout << "===============================================\n";
    }


    void Forgot_Password() {
        string username, id, email, password, skip1, skip2;

        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your email: ";
        cin >> email;

        ifstream file("data.txt");

        bool found = false;
        while (file >> id >> email >> password >> skip1 >> skip2) {
            if (id == username) {
                found = true;
                break;
            }
        }
        file.close();

        if (found) {
            cout << "Account found! Your email is: " << email << "\n";
            cout << "Your password is: " << password << "\n";
        }
        else {
            cout << "Username not found.\n";
        }
    }
};


int main() {
    shipzy_store store;
    store.run();


    StoreBase* basePtr = &store;

    return 0;
}