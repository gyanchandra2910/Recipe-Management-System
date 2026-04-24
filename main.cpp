#include "Recipe.h"
#include <iostream>

using namespace std;

// Forward declarations from utility.cpp
void verifyDBConnection();
int handleSignup(User &u);
int handleLogin(User &u);
void test(User &u);

int main()
{
    verifyDBConnection();

    int choice;
    while(true)
    {
        cout<<"Enter 1 to login into our app"<<endl;
        cout<<"Enter 2 to sign up"<<endl;
        cout<<"Enter 3 to exit"<<endl;
        cin>>choice;

        if(choice == 3) break;
        else if (choice == 1)
        {
            User u;
            if (handleLogin(u)) {
                test(u);
            }
        }
        else if (choice == 2)
        {
            User u;
            if (handleSignup(u) == 0) {
                test(u);
            }
        }
        else {
            cout << "Invalid choice" << endl;
        }
    }
    return 0;
}