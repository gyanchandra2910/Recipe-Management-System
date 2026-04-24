#include<string>
using namespace std;

class User
{
    friend istream& operator>>(istream&,User&);
    
    private:
        int id;
        string username;
        string email;
        string password;

    public:
        User(string="alice",string="alice@gmail.com",string="alice@45");
        string getUsername() const;
        string getEmail() const;
        string getPass() const;
        int getId() const;
        void setId(int i);
        void setName(const string& n);
        void setPass(const string& p);
        void setEmail(const string& e);
        void setUserToNull();
};