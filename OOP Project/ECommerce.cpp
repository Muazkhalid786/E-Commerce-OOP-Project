#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
using namespace std;
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
    cin >> ch;
    Person p1;
    system("cls");
    if (ch == 1)
    {
        cout << "Enter Email:";
        cin >> email;
        cout << "Enter Pass:";
        cin >> pass;
        bool loginSuccessful = false;
        userfile.seekg(0, ios::beg);
        ifstream infile("User.txt");
        while (infile >> name1 >> email1 >> pass1)
        {

            if (email == email1 && pass == pass1)
            {
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
    return 0;
}
