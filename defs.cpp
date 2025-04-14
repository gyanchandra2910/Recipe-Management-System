#include "Recipe.h"

//Time class(definitions)
Time::Time(int hour, int minutes, int seconds)
{
    if ((hour < 0 || hour > 23) || (minutes < 0 || minutes > 59) || (seconds < 0 || seconds > 59))
    {
        this->hour = 0;
        this->minutes = 30;
        this->seconds = 0;
    }
    else
    {
        this->hour = hour;
        this->minutes = minutes;
        this->seconds = seconds;
    }
}


ostream& operator<<(ostream& out, const Time& t) 
{
    out << t.hour << " hours, "<< t.minutes << " minutes, "<< t.seconds << " seconds";

    return out;
}


//recipe class(definitions)
Recipe::Recipe(string name, vector<pair<string, string> > ingredients, string instructions, int likes, int ratings,User user, int hour, int minutes, int seconds)
    : prep_time(hour, minutes, seconds)
{
    this->name = name;
    this->ingredients = ingredients;
    this->instructions = instructions;
    this->likes = likes;
    this->ratings = ratings;
    this->addedBy = user.getUsername();
    ratingCount = 1;
}

void Recipe::addRatings(double addedRating)
{
    ratingCount++;
    ratings = (ratings * ratingCount + addedRating) / (ratingCount + 1); // increases ratingCount and increases ratings and calculates average
}

void Recipe::addIngredients(const string &takeIngredient, const string &quantity) // adds ingredients based on user input
{
    ingredients.push_back(make_pair(takeIngredient, quantity));
}

void Recipe::removeIngredients(const string &removeIngredients) // removes ingredients based on user input
{
    for (int i = 0; i < ingredients.size(); i++)
    {
        if (ingredients[i].first == removeIngredients)
        {
            ingredients.erase(ingredients.begin() + i);
            break;
        }
    }
}

void Recipe::increaseLikes() // increase likes
{
    likes++;
}

string Recipe::getRecipeName()
{
    return name;
}

ostream& operator <<(ostream &out,const Recipe& r)
{
    out << "============================" << endl;
    out << "       Recipe Details       " << endl;
    out << "============================" << endl;
    out << "🍲 Recipe Name: " << r.name << endl;
    out << "----------------------------" << endl;

    out << "🥄 Ingredients:" << endl;
    out << "----------------------------" << endl;
    out << "Name     |     Quantity"<< endl;
    out << "----------------------------" << endl;
    for (int i = 0; i < r.ingredients.size(); i++) 
    {
        out<<r.ingredients[i].first<< "\t\t" <<r.ingredients[i].second << endl;
    }
    out << "----------------------------" << endl;

    out << "📖 Preparation Time:" << endl;
    out << "----------------------------" << endl;
    out << r.prep_time<< endl;
    out << "----------------------------" << endl;

    out << "📖 Cooking Instructions:" << endl;
    out << "----------------------------" << endl;
    out << r.instructions << endl;
    out << "----------------------------" << endl;

    out << "👍 Likes: " << r.likes <<endl;
    out << "----------------------------" << endl;
    out<<"⭐ Average Rating: " << r.ratings << endl;
    out << "----------------------------" << endl;
    out << "👤 Added By: " << r.addedBy << endl;
    out << "============================" << endl;

    return out;
}



bool operator==(const Recipe &r1, const Recipe &r2)// Print the common ingredient
{
    cout << "The common Ingredients in the given two recipes are:" << endl;
    bool checkCommon = false;

    for (int i = 0; i < r1.ingredients.size(); ++i)
    {
        for (int j = 0; j < r2.ingredients.size(); ++j)
        {
            if (r1.ingredients[i].first == r2.ingredients[j].first)
            {
                cout << r1.ingredients[i].first << endl; 
                checkCommon = true;
            }
        }
    }

    if (checkCommon == false)
    {
        cout << "No common ingredients." << endl;
    }

    return checkCommon;
}



//User class(definitions)

User::User(string username,string email,string pass)
{
    this->username=username;
    this->email=email;
    this->password=pass;
}

string User::getUsername()
{
    return username;
}

istream& operator>>(istream& in, User& u) 
{
    in>>u.username;
    in>>u.email;
    in>>u.password;

    return in;
}
