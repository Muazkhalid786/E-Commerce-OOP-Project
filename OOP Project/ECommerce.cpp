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
protected:
    string productName;
    static int productId;
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
        //  productId = id;
        productPrice = price;
        productQty = qty;
    }
    int getquantity()
    {
        return productQty;
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
class Electronic : public Product
{
private:
    string Warr;

public:
    Electronic() {}
    Electronic(string name, int id, int price, int qty, string type)
    {
        productId = id;
        productName = name;
        productPrice = price;
        productQty = qty;
        Warr = type;
    }
    friend istream &operator>>(istream &is, Electronic &p)
    {
        ifstream in("product.txt");
        int id, price, qty;
        string name, warr;
        while (in >> id >> name >> price >> qty >> warr)
        {
        }
        p.productId = id + 1;
        cout << "Product Name: ";
        is >> p.productName;

        cout << "Product Price: ";
        is >> p.productPrice;
        cout << "Enter Warranty: ";
        is >> p.Warr;
        cout << "Product Quantity: ";
        is >> p.productQty;
        return is;
    }
    void add()
    {

        fstream product("product.txt", ios::app);
        product << productId << "\t" << productName << "\t" << productPrice << "\t" << productQty << "\t" << Warr << endl;
        product.close();
    }
};
int Product::productId = 0;
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
        ofstream cart("cart.txt");
        int ID, PRICE, QTY;
        string Name, type;
        ifstream product("product.txt");

        while (product >> ID >> Name >> PRICE >> QTY >> type)
        {
            if (choice == ID)
            {
                if (qty > QTY)
                {
                    cout << "You can't enter more than " << QTY << endl;
                    return;
                }
                else
                {
                    cart << ID << "\t" << Name << "\t" << PRICE << "\t" << qty << "\t"
                         << "\t" << type << endl;
                    Electronic Temp(Name, ID, PRICE, qty, type);
                    products[index] = Temp;
                    index++;
                    totalPrice += (PRICE * qty);
                    totalItems += qty;
                    cout << "Added in cart" << endl;
                }
            }
        }
        product.close();
    }

    void placeOrder()
    {
        ofstream outfile("product.txt", ios::app);
        ifstream infile("product.txt");
        ofstream tempfile("temp.txt", ios::app);

        int ID, PRICE, QTY;
        string Name, type;

        while (infile >> ID >> Name >> PRICE >> QTY >> type)
        {
            for (int i = 0; i < index; i++)
            {
                if (Name == products[i].getProductName())
                {
                    int remainingQty = QTY - products[i].getquantity();
                    if (remainingQty >= 0)
                    {
                        tempfile << ID << "\t" << Name << "\t" << PRICE << "\t" << remainingQty << "\t" << type << endl;
                        break;
                    }
                    else
                    {
                        cout << "Insufficient quantity available for product: " << Name << endl;
                    }
                }
                else
                {
                    tempfile << ID << "\t" << Name << "\t" << PRICE << "\t" << QTY << "\t" << type << endl;
                }
            }
        }

        infile.close();
        outfile.close();
        tempfile.close();

        remove("product.txt");
        rename("temp.txt", "product.txt");

        totalItems = 0;
        totalPrice = 0;
        index = 0;

        cout << "Order placed successfully!" << endl;
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
class Sport : public Product
{
private:
    string Brand;

public:
    Sport() {}
    friend istream &operator>>(istream &is, Sport &p)
    {
        ifstream in("product.txt");
        int id, price, qty;
        string name, warr;
        while (in >> id >> name >> price >> qty >> warr)
        {
        }
        p.productId = id + 1;
        cout << "Product Name: ";
        is >> p.productName;

        cout << "Product Price: ";
        is >> p.productPrice;
        cout << "Enter Brand: ";
        is >> p.Brand;
        cout << "Product Quantity: ";
        is >> p.productQty;
        return is;
    }
    void add()
    {

        fstream product("product.txt", ios::app);
        product << productId << "\t" << productName << "\t" << productPrice << "\t" << productQty << "\t" << Brand << endl;
        product.close();
    }
};
class Fashion : public Product
{
private:
    string Material;

public:
    Fashion() {}
    friend istream &operator>>(istream &is, Fashion &p)
    {
        ifstream in("product.txt");
        int id, price, qty;
        string name, material;
        while (in >> id >> name >> price >> qty >> material)
        {
        }
        p.productId = id + 1;
        cout << "Product Name: ";
        is >> p.productName;

        cout << "Product Price: ";
        is >> p.productPrice;
        cout << "Enter Material: ";
        is >> p.Material;
        cout << "Product Quantity: ";
        is >> p.productQty;
        return is;
    }
    void add()
    {

        fstream product("product.txt", ios::app);
        product << productId << "\t" << productName << "\t" << productPrice << "\t" << productQty << "\t" << Material << endl;
        product.close();
    }
};
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
    int ch;
    string name, email, pass;
    string name1, email1, pass1;
    string productId, productName, productPrice, productQty, type;
    do
    {

        cout << "Enter Choice: ";
        cin >> ch;
    } while (ch > 3 || ch < 0);
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
        cout << "1 - Show products " << endl;
        cout << "2 - Add Product to Cart " << endl;
        cout << "3 - Show Cart " << endl;
        cout << "4 - Show Cart Details" << endl;
        cout << "5 - Place order" << endl;

        cout << "6 - Logout" << endl;
        if (is_admin)
        {
            cout << "7 - Add Product" << endl;
        }
        cin >> ch;

        if (ch == 1)
        {
            system("cls");
            ifstream infile("product.txt");

            if (!infile.is_open())
            {
                cout << "Error" << endl;
            }

            int choi;
            cout << "Category:" << endl;
            cout << "1- Electronic" << endl;
            cout << "2- Fashion" << endl;
            cout << "3- Sports" << endl;
            do
            {
                cout << "Enter Choice: ";
                cin >> choi;
            } while (choi > 3);
            if (choi == 1)
            {
                cout << "=================================================================================================" << endl;
                cout << "Id" << setw(20) << "Amount" << setw(20) << "Quantity" << setw(18) << "Name" << setw(18) << "Warranty" << endl;
                cout << "=================================================================================================" << endl;

                while (infile >> productId >> productName >> productPrice >> productQty >> type)
                {
                    // replace(productName.begin(), productName.end(), '_', ' ');

                    cout << productId << setw(20) << productPrice << setw(20) << productQty << setw(20) << productName << setw(18) << type << endl;
                }
                infile.close();
            }
            if (choi == 2)
            {

                cout << "=================================================================================================" << endl;
                cout << "Id" << setw(20) << "Amount" << setw(20) << "Quantity" << setw(18) << "Name" << setw(18) << "Material" << endl;
                cout << "=================================================================================================" << endl;

                while (infile >> productId >> productName >> productPrice >> productQty >> type)
                {
                    // replace(productName.begin(), productName.end(), '_', ' ');

                    cout << productId << setw(20) << productPrice << setw(20) << productQty << setw(20) << productName << setw(18) << type << endl;
                }
                infile.close();
            }
            if (choi == 3)
            {

                cout << "=================================================================================================" << endl;
                cout << "Id" << setw(20) << "Amount" << setw(20) << "Quantity" << setw(18) << "Name" << setw(18) << "Brand" << endl;
                cout << "=================================================================================================" << endl;

                while (infile >> productId >> productName >> productPrice >> productQty >> type)
                {
                    // replace(productName.begin(), productName.end(), '_', ' ');

                    cout << productId << setw(20) << productPrice << setw(20) << productQty << setw(20) << productName << setw(18) << type << endl;
                }
                infile.close();
            }
        }

        else if (ch == 2)
        {
            int qty;
            int choice;
            cout << "Enter Poduct ID: ";
            cin >> choice;
            cout << "Enter Quantity: ";
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
        else if (ch == 5)
        {
            cart.placeOrder();
        }
        else if (ch == 7 && is_admin)
        {
            int choi;
            cout << "Category:" << endl;
            cout << "1- Electronic" << endl;
            cout << "2- Fashion" << endl;
            cout << "3- Sports" << endl;
            do
            {
                cout << "Enter Choice: ";
                cin >> choi;
            } while (choi > 3);
            if (choi == 1)
            {
                Electronic E;
                cin >> E;
                E.add();
            }
            if (choi == 2)
            {
                Fashion F;
                cin >> F;
                F.add();
            }
            if (choi == 3)
            {
                Sport s;
                cin >> s;
                s.add();
            }
        }
        else if (ch == 6)
        {
            return 0;
        }
    }

    return 0;
}
