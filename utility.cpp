#include "Recipe.h"
#include <fstream>
#include <algorithm>
#include <time.h>
using namespace std;

// Function tempelates to filter/sort recipes on basis of likes/ratings(int,double)
template <typename T>
void bubbleSortRecipes(vector<Recipe> &recipes, T Recipe::*member)
{
    bool swapped;
    for (int i = 0; i < recipes.size() - 1; ++i)
    {
        swapped = false;
        for (int j = 0; j < recipes.size() - i - 1; ++j)
        {
            if (recipes[j].*member < recipes[j + 1].*member)
            {
                swap(recipes[j], recipes[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// signup function
void signUp(User &u)
{
    cout << "Enter details(username,password)" << endl;
    cin >> u;
    ofstream out("user.txt", ios::app);
    if (login(u.getUsername(), u.getPass()))
    {
        cout << "User already Exists! Please Login." << endl;
        u.setUserToNull();
        return;
    }
    if (!out)
    {
        cerr << "Error while opening file for saving user data." << endl;
        return;
    }
    out << u << endl;
    out.close();
    cout << endl;
    cout << "User details have been saved to file." << endl;
    cout << endl;
}

// login function
bool login(const string &username, const string &password)
{
    ifstream in("user.txt");
    if (!in)
    {
        cerr << "Error opening file for reading." << endl;
        return false;
    }
    User u;
    while (in >> u)
    {
        if (u.getUsername() == username && u.getPass() == password)
        {
            return true;
        }
    }
    return false;
}

// checks for if reciped added or not
bool isRecipeAdded(const string &rName)
{
    ifstream in("recipeName.txt");
    if (!in)
    {
        cerr << "Error opening file for reading." << endl
             << endl;
        return false;
    }
    string recipeName;
    while (getline(in, recipeName))
    {
        if (recipeName == rName)
        {
            return true;
        }
    }
    return false;
}

// handler for signup when already existing user signup
int handleSignup(User &u)
{
    signUp(u);
    if (u.getUsername() == " ")
    {
        return 1;
    }
    cout << "Hello " << u.getUsername() << " Welcome! to our Recipe App" << endl;
    return 0;
}

// handler function for login
int handleLogin(User &u)
{
    string name, password;
    cout << "Enter username: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> password;
    cout << endl;

    if (login(name, password))
    {
        cout << "Login successful!" << "Welcome back " << name << endl
             << endl;
        ;
        u.setName(name);
        u.setPass(password);
        return 1;
    }
    else
    {
        cout << "Invalid username or password." << endl
             << endl;
        return 0;
    }
}

// test function which is used on both login and signup so made as a function to redcue code size
void test(User &u)
{
    int choice2;
    while (true)
    {
        int choice2;
        cout << "Enter 1 to add your Recipe" << endl;
        cout << "Enter 2 to display all recipe" << endl;
        cout << "Enter 3 to search and display particular recipe" << endl;
        cout << "Enter 4 to display common ingredients between two recipe" << endl;
        cout << "Enter 5 to sort/filter recipes based on likes/ratings" << endl;
        cout << "Enter 6 to get recipe of the day" << endl;
        cout << "Enter 7 to break" << endl;

        cin >> choice2;
        switch (choice2)
        {
        case 1:
        {
            cin.ignore();
            string name;
            cout << "Enter name of recipe: ";
            getline(cin, name);

            vector<pair<string, string>> ingredients;

            int numIngredients;
            cout << "Enter number of ingredients: ";
            cin >> numIngredients;
            cin.ignore();

            for (int i = 0; i < numIngredients; ++i)
            {
                string ingredientName, ingredientQuantity;
                cout << "Enter ingredient name: ";
                getline(cin, ingredientName);
                cout << "Enter ingredient quantity: ";
                getline(cin, ingredientQuantity);
                ingredients.push_back(make_pair(ingredientName, ingredientQuantity));
            }

            cout << "Enter cooking-instructions: ";
            string instruct;
            getline(cin, instruct);

            cout << "Enter preparation time (hours minutes seconds): ";
            int h, m, s;
            cin >> h >> m >> s;

            Recipe r1(name, ingredients, instruct, 10, 4, u, h, m, s);

            ofstream out("addedRecipe.txt", ios::app);
            if (!out)
            {
                cerr << "Error opening file for writing." << endl;
                return;
            }
            if (isRecipeAdded(r1.getRecipeName()))
            {
                cout << "This Recipe already exist.please have a look at all recipes" << endl;
                continue;
            }

            out << r1;
            recipes.push_back(r1);
            out.close();

            ofstream out2("recipeName.txt", ios::app);
            if (!out2)
            {
                cerr << "Error opening file for writing Recipe data." << endl;
                return;
            }
            out2 << endl;
            out2 << r1.getRecipeName();
            out2.close();
            cout << "Your Recipe got added" << endl;
            cout << r1;
            break;
        }

        case 2:
        {
            cout << "Recipes available here:" << endl;
            int size = recipes.size();
            for (int i = 0; i < size; i++)
            {
                cout << recipes[i];
                cout << endl;
            }
            break;
        }
        case 6:
        {
            if (recipes.empty())
            {
                cout << "No recipes available!" << endl;
                break;
            }

            srand(time(0));                            // Seed the random number generator
            int randomIndex = rand() % recipes.size(); // Generate a random index

            cout << "Recipe of the Day: " << endl;
            cout << recipes[randomIndex] << endl; // Display the randomly selected recipe
            break;
        }
        case 3:
        {
            cout << "Enter the name of the recipe to be displayed:" << endl;
            string name;
            cin.ignore();
            getline(cin, name);

            int size = recipes.size(), i;
            for (i = 0; i < size; i++)
            {
                if (recipes[i].getRecipeName() == name)
                {
                    cout << recipes[i];

                    int input;
                    while (true)
                    {
                        cout << "Enter 1 to give a rating to this recipe." << endl;
                        cout << "Enter 2 to like this recipe." << endl;
                        cout << "Enter 3 to add more ingredients to this recipe" << endl;
                        cout << "Enter 4 to remove ingredients to this recipe" << endl;
                        cout << "Enter 5 to exit to the main menu." << endl;

                        cin >> input;
                        if (input == 1)
                        {
                            double rating;
                            cout << "Enter the rating between 0 to 5): ";
                            cin >> rating;

                            if (rating >= 0 && rating <= 5)
                            {
                                recipes[i].addRatings(rating);
                                cout << "Thank you. Your rating was added" << endl;
                                cout << recipes[i];
                            }
                            else
                            {
                                cout << "Invalid rating.Enter a value between 0 and 5." << endl;
                            }
                        }
                        else if (input == 2)
                        {
                            recipes[i].increaseLikes();
                            cout << "Recipe liked." << endl;
                            cout << recipes[i];
                        }
                        else if (input == 3)
                        {
                            string ingredient, quantity;
                            cout << "Enter the name of ingredient and its quantity" << endl;
                            cin.ignore();
                            getline(cin, ingredient);
                            getline(cin, quantity);
                            if (recipes[i].getAddedBy() != u.getUsername())
                            {
                                cout << "You don't have permission to edit." << endl;
                            }
                            else
                            {
                                cout << "Ingredient added" << endl;
                                recipes[i].addIngredients(ingredient, quantity);
                                cout << recipes[i] << endl;
                            }
                        }
                        else if (input == 4)
                        {
                            cout << "Enter name of ingredient to be removed" << endl;
                            string ingredient;
                            cin.ignore();
                            getline(cin, ingredient);
                            if (recipes[i].getAddedBy() != u.getUsername())
                            {
                                cout << "You don't have permission to edit." << endl;
                            }
                            else
                            {
                                cout << "Ingredient removed" << endl;
                                recipes[i].removeIngredients(ingredient);
                                cout << recipes[i] << endl;
                            }
                        }
                        else if (input == 5)
                        {
                            break;
                        }
                        else
                        {
                            cout << "Invalid choice" << endl;
                        }
                    }
                    break;
                }
            }

            if (i == size)
                cout << "No Recipe found" << endl;

            break;
        }

        case 4:
        {
            cout << "Enter the name of the 1st recipe: ";
            string name1;
            cin.ignore();
            getline(cin, name1);

            cout << "Enter the name of the 2nd recipe: ";
            string name2;
            getline(cin, name2);

            int flag1 = -1, flag2 = -1;

            for (int i = 0; i < recipes.size(); i++)
            {
                if (recipes[i].getRecipeName() == name1)
                {
                    flag1 = i;
                }
                if (recipes[i].getRecipeName() == name2)
                {
                    flag2 = i;
                }

                if (flag1 != -1 && flag2 != -1)
                {
                    break;
                }
            }

            if (flag1 != -1 && flag2 != -1)
            {
                if (recipes[flag1] == recipes[flag2])
                {
                }
                else
                {
                    cout << "These recipes have no common ingredients." << endl
                         << endl;
                }
            }

            else
            {
                cout << "Either one or both recipes are not found." << endl;
                cout << endl;
            }

            break;
        }
        case 5:
        {
            int choose;
            cout << "Enter 1 to filter based on likes(decreasing order)" << endl;
            cout << "Enter 2 to filter based on ratings(decreasing order)" << endl;
            cin >> choose;
            while (true)
            {
                if (choose == 1)
                {
                    bubbleSortRecipes(recipes, &Recipe::likes);
                    cout << "Sorted by likes:\n";
                    for (int i = 0; i < recipes.size(); i++)
                    {
                        cout << recipes[i];
                    }
                    break;
                }
                else if (choose == 2)
                {
                    bubbleSortRecipes(recipes, &Recipe::ratings);
                    cout << "Sorted by ratings:\n";
                    for (int i = 0; i < recipes.size(); i++)
                    {
                        cout << recipes[i];
                    }
                    break;
                }
                else
                {
                    cout << "wrong choice" << endl;
                }
            }
            break;
        }
        }

        if (choice2 == 7)
        {
            break;
        }
    }
}
