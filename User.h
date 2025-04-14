#include<string>
using namespace std;

class User
{
    friend istream& operator>>(istream&,User&);
    
    private:
        string username;
        string email;
        string password;

    public:
        User(string="alice",string="alice@gmail.com",string="alice@45");
        string getUsername();
};