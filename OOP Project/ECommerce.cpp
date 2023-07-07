#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
using namespace std;

class Product
{
private:
    string productName;
    int productId;
    int productPrice;
    int productQty;

public:
    Product()
    {
    }
    void add()
    {

        fstream product("product.txt", ios::app);
        product << productId << "\t" << productName << "\t" << productPrice << "\t" << productQty << endl;
        product.close();
    }
    Product(string name, int id, int price, int qty)
    {
        productName = name;
        productId = id;
        productPrice = price;
        productQty = qty;
    }
    friend istream &operator>>(istream &is, Product &p)
    {
        ifstream in("product.txt");
        int id, price, qty;
        string name;
        while (in >> id >> name >> price >> qty)
        {
        }
        p.productId = id + 1;
        cout << "Product Name: ";
        is >> p.productName;

        cout << "Product Price: ";
        is >> p.productPrice;

        cout << "Product Quantity: ";
        is >> p.productQty;
        return is;
    }

    void getInfo()
    {
        cout << "Product Id: " << productId << endl;
        cout << "Product Name: " << productName << endl;
        cout << "Product Price: " << productPrice << endl;
        cout << "Product Qty: " << productQty << endl;
    }
    string getProductName()
    {
        return productName;
    }
};

class ShoppingCart
{
private:
    Product products[100];
    static int totalItems;
    static int index;
    static int totalPrice;

public:
    void showProducts()
    {

        for (int i = 0; i < index; i++)
        {
            products[i].getInfo();
        }
    }

    void addProduct(int choice, int qty)
    {
        int ID, PRICE, QTY;
        string Name;
        ifstream product("product.txt");

        while (product >> ID >> Name >> PRICE >> QTY)
        {
            if (qty > QTY)
            {
                cout << "You can't enter more than " << QTY << endl;
                return;
            }
            if (choice == ID)
            {
                Product Temp(Name, ID, PRICE, qty);
                products[index] = Temp;
                index++;
                totalPrice += PRICE;
                totalItems += qty;
            }
        }
        product.close();
    }

    void getTotalPrice()
    {
        cout << "Total Items in Cart: " << totalItems << endl;
        cout << "Total Cart Price: " << totalPrice << endl;
    }
};
int ShoppingCart::index = 0;
int ShoppingCart::totalPrice = 0;
int ShoppingCart::totalItems = 0;

class Person
{
private:
    string Pass;
    string Email;
    string Name;

public:
    Person()
    {
    }
    Person(string name, string pass, string email)
    {
        Pass = pass;
        Email = email;
        Name = name;
    }
    string getemail()
    {
        return Email;
    }
    string getname()
    {
        return Name;
    }
    string getpass()
    {
        return Pass;
    }
    friend istream &operator>>(istream &in, Person &obj)
    {
        cout << "Enter Name: ";
        in >> obj.Name;
        cout << "Enter Email: ";
        in >> obj.Email;
        cout << "Enter Password: ";
        in >> obj.Pass;
        return in;
    }
};

int main()
{
    fstream userfile("User.txt", ios::app);
    ShoppingCart cart;
    if (!userfile.is_open())
    {
        cout << "Failed to open file!" << endl;
        return 1;
    }
    cout << "----------------Menu----------------\n";
failed_case:
    bool login = false;
    cout << "1-Login\n";
    cout << "2-Register\n";
    cout << "Enter Choice: ";
    int ch;
    string name, email, pass;
    string name1, email1, pass1;
    string productId, productName, productPrice, productQty;
    cin >> ch;
    Person p1;
    bool loginSuccessful = false;
    system("cls");
    bool is_admin = false;
    if (ch == 1)
    {
        cout << "Enter Email:";
        cin >> email;
        cout << "Enter Pass:";
        cin >> pass;
        userfile.seekg(0, ios::beg);
        ifstream infile("User.txt");
        while (infile >> name1 >> email1 >> pass1)
        {

            if (email == email1 && pass == pass1)
            {
                if (email == "itzmajo786@gmail.com" || email == "11")
                {
                    is_admin = true;
                    cout << "Welcome Admin\n";
                }
                cout << "Login Successful\n";
                loginSuccessful = true;
                infile.close();
                break;
            }
        }

        if (!loginSuccessful)
        {
            cout << "Login Failed" << endl;
            goto failed_case;
        }
    }

    else if (ch == 2)
    {
        cin >> p1;
        userfile << p1.getname() << " ";
        userfile << p1.getemail() << " ";
        userfile << p1.getpass() << endl;
    }

    userfile.close();

    cout << "Welcome to Daraz CMD" << endl;
    while (loginSuccessful)
    {
        cout << "1 - Show All products " << endl;
        cout << "2 - Add Product to Cart " << endl;
        cout << "3 - Show Cart " << endl;
        cout << "4 - Show Cart Details" << endl;
        cout << "4 - Place order" << endl;
        if (is_admin)
        {
            cout << "5 - Add Product" << endl;
        }

        cout << "6 - Logout" << endl;
        cin >> ch;

        if (ch == 1)
        {
            system("cls");
            ifstream infile("product.txt");
            if (!infile.is_open())
            {
                cout << "Error" << endl;
            }
            cout << "===========================================================================" << endl;
            cout << "Id" << setw(20) << "Amount" << setw(20) << "Quantity" << setw(18) << "Name" << endl;
            cout << "===========================================================================" << endl;

            while (infile >> productId >> productName >> productPrice >> productQty)
            {
                // replace(productName.begin(), productName.end(), '_', ' ');

                cout << productId << setw(20) << productPrice << setw(20) << productQty << setw(20) << productName << endl;
            }
            infile.close();
        }

        else if (ch == 2)
        {
            int qty;
            int choice;
            cout << "Enter Poduct ID";
            cin >> choice;
            cout << "Enter Quantity";
            cin >> qty;
            cart.addProduct(choice, qty);
        }
        else if (ch == 3)
        {
            cart.showProducts();
        }
        else if (ch == 4)
        {
            cart.getTotalPrice();
        }
        else if (ch == 5 && is_admin)
        {

            Product p;
            cin >> p;
            p.add();
        }
        else if (ch == 6)
        {
            return 0;
        }
    }

    return 0;
}
