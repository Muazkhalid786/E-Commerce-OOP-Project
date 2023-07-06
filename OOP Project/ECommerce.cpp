#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
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
    cout << "----------------Menu----------------\n";
    cout << "1-Login\n";
    cout << "2-Register\n";
    system("cls");
}