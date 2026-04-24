#include <string>
#include <vector>
#include"Time.h"
#include"User.h"

class Recipe
{
    friend bool operator==(const Recipe &r1, const Recipe &r2);
    friend ostream& operator <<(ostream&,const Recipe&);

private:
    int id;
    string name;
    vector<pair<string, string> > ingredients;
    string instructions;
    Time prep_time;
    int likes;
    double ratings;
    int ratingCount;
    string addedBy;

public:
    Recipe(string,vector<pair<string, string> >,string, int, double,User, int, int, int);
    
    void addRatings(double);
    void addIngredients(const string &, const string &);
    void removeIngredients(const string &);
    void increaseLikes();
    string getRecipeName() const;
    string getInstructions() const;
    int getLikes() const;
    double getRatings() const;
    int getRatingCount() const;
    string getAddedBy() const;
    const vector<pair<string, string> >& getIngredients() const;
    const Time& getPrepTime() const;
    int getId() const;
    void setId(int i);
};