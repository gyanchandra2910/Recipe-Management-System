#include <string>
#include <vector>
#include"Time.h"
#include"User.h"

class Recipe
{
    friend bool operator==(const Recipe &r1, const Recipe &r2);
    friend ostream& operator <<(ostream&,const Recipe&);

private:
    string name;
    vector<pair<string, string> > ingredients;
    string instructions;
    Time prep_time;
    int likes;
    int ratings;
    int ratingCount;
    string addedBy;

public:
    Recipe(string,vector<pair<string, string> >,string, int, int,User, int, int, int);
    
    void addRatings(double);
    void addIngredients(const string &, const string &);
    void removeIngredients(const string &);
    void increaseLikes();
    string getRecipeName();
};