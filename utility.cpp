#include "Recipe.h"
#include <mysql.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <sstream>

using namespace std;

const char *DB_HOST = "localhost";
const char *DB_USER = "root";
const char *DB_PASS = "Gyan123@";
const char *DB_NAME = "recipe_db";

MYSQL* conn = nullptr;
vector<Recipe> recipes;

template <typename T>
void bubbleSortRecipes(vector<Recipe> &recipes, T (Recipe::*member)() const)
{
    bool swapped;
    for (int i = 0; i < recipes.size() - 1; ++i)
    {
        swapped = false;
        for (int j = 0; j < recipes.size() - i - 1; ++j)
        {
            if ((recipes[j].*member)() < (recipes[j + 1].*member)())
            {
                swap(recipes[j], recipes[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void connectDB() {
    if (conn == nullptr) {
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0)) {
            cerr << "MySQL Connection Error: " << mysql_error(conn) << endl;
            conn = nullptr;
        }
    }
}

void verifyDBConnection() {
    connectDB();
    if (conn) {
        cout << "Database connected successfully!" << endl;
    } else {
        cout << "Failed to connect to database. Please check credentials in utility.cpp" << endl;
        exit(1);
    }
}

void fetchRecipes() {
    recipes.clear();
    if (!conn) connectDB();
    if (!conn) return;

    string query = "SELECT r.id, r.name, r.instructions, r.prep_time, r.likes, r.ratings, r.ratingCount, u.username, u.email, i.name, i.quantity "
                   "FROM Recipes r "
                   "JOIN Users u ON r.added_by_user_id = u.id "
                   "LEFT JOIN Ingredients i ON r.id = i.recipe_id "
                   "ORDER BY r.id;";

    if (mysql_query(conn, query.c_str())) {
        cerr << "Fetch Error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res) return;

    MYSQL_ROW row;
    int current_recipe_id = -1;
    vector<pair<string, string> > current_ingredients;
    
    string r_name, r_inst, r_prep, u_name, u_email;
    int r_likes, r_rcount;
    double r_ratings;

    while ((row = mysql_fetch_row(res))) {
        int id = atoi(row[0]);
        if (id != current_recipe_id) {
            if (current_recipe_id != -1) {
                int h = 0, m = 0, s = 0;
                sscanf(r_prep.c_str(), "%d %d %d", &h, &m, &s);
                User u(u_name, u_email, "");
                Recipe r(r_name, current_ingredients, r_inst, r_likes, r_ratings, u, h, m, s);
                r.setId(current_recipe_id);
                recipes.push_back(r);
            }
            current_recipe_id = id;
            r_name = row[1] ? row[1] : "";
            r_inst = row[2] ? row[2] : "";
            r_prep = row[3] ? row[3] : "0 0 0";
            r_likes = row[4] ? atoi(row[4]) : 0;
            r_ratings = row[5] ? atof(row[5]) : 0.0;
            r_rcount = row[6] ? atoi(row[6]) : 1;
            u_name = row[7] ? row[7] : "";
            u_email = row[8] ? row[8] : "";
            current_ingredients.clear();
        }
        
        if (row[9] && row[10]) {
            current_ingredients.push_back(make_pair(row[9], row[10]));
        }
    }
    
    if (current_recipe_id != -1) {
        int h = 0, m = 0, s = 0;
        sscanf(r_prep.c_str(), "%d %d %d", &h, &m, &s);
        User u(u_name, u_email, "");
        Recipe r(r_name, current_ingredients, r_inst, r_likes, r_ratings, u, h, m, s);
        r.setId(current_recipe_id);
        recipes.push_back(r);
    }

    mysql_free_result(res);
}

bool login(const string &username, const string &password, User &u) {
    if (!conn) connectDB();
    if (!conn) return false;

    string query = "SELECT id, username, email FROM Users WHERE username = ? AND password = ?";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) return false;

    if (mysql_stmt_prepare(stmt, query.c_str(), query.length())) {
        mysql_stmt_close(stmt);
        return false;
    }

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username.c_str();
    bind[0].buffer_length = username.length();

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)password.c_str();
    bind[1].buffer_length = password.length();

    if (mysql_stmt_bind_param(stmt, bind)) {
        mysql_stmt_close(stmt);
        return false;
    }

    if (mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return false;
    }

    MYSQL_BIND res_bind[3];
    memset(res_bind, 0, sizeof(res_bind));

    int user_id;
    char res_user[255];
    char res_email[255];
    unsigned long len_user, len_email;

    res_bind[0].buffer_type = MYSQL_TYPE_LONG;
    res_bind[0].buffer = &user_id;

    res_bind[1].buffer_type = MYSQL_TYPE_STRING;
    res_bind[1].buffer = res_user;
    res_bind[1].buffer_length = sizeof(res_user);
    res_bind[1].length = &len_user;

    res_bind[2].buffer_type = MYSQL_TYPE_STRING;
    res_bind[2].buffer = res_email;
    res_bind[2].buffer_length = sizeof(res_email);
    res_bind[2].length = &len_email;

    mysql_stmt_bind_result(stmt, res_bind);

    if (mysql_stmt_fetch(stmt) == 0) {
        u.setId(user_id);
        u.setName(string(res_user, len_user));
        u.setEmail(string(res_email, len_email));
        u.setPass(password);
        mysql_stmt_close(stmt);
        return true;
    }

    mysql_stmt_close(stmt);
    return false;
}

void signUp(User &u) {
    if (!conn) connectDB();
    if (!conn) return;

    string query = "INSERT INTO Users (username, email, password) VALUES (?, ?, ?)";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) return;

    if (mysql_stmt_prepare(stmt, query.c_str(), query.length())) {
        mysql_stmt_close(stmt);
        return;
    }

    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind));

    string username = u.getUsername();
    string email = u.getEmail();
    string password = u.getPass();

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username.c_str();
    bind[0].buffer_length = username.length();

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)email.c_str();
    bind[1].buffer_length = email.length();

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)password.c_str();
    bind[2].buffer_length = password.length();

    if (mysql_stmt_bind_param(stmt, bind)) {
        mysql_stmt_close(stmt);
        return;
    }

    if (mysql_stmt_execute(stmt)) {
        cerr << "SignUp Error: Username might already exist." << endl;
        u.setUserToNull();
    } else {
        u.setId(mysql_stmt_insert_id(stmt));
        cout << "\nUser details have been saved to database.\n" << endl;
    }

    mysql_stmt_close(stmt);
}

int handleSignup(User &u) {
    cout << "Enter details(username, email, password) separated by spaces:" << endl;
    string un, em, pw;
    cin >> un >> em >> pw;
    u.setName(un);
    u.setEmail(em);
    u.setPass(pw);
    signUp(u);
    if (u.getUsername() == "") {
        return 1;
    }
    cout << "Hello " << u.getUsername() << " Welcome! to our Recipe App" << endl;
    return 0;
}

int handleLogin(User &u) {
    string name, password;
    cout << "Enter username: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> password;
    cout << endl;

    if (login(name, password, u)) {
        cout << "Login successful! Welcome back " << name << endl << endl;
        return 1;
    } else {
        cout << "Invalid username or password." << endl << endl;
        return 0;
    }
}

void test(User &u) {
    int choice2;
    fetchRecipes(); // Initial fetch
    
    while (true) {
        cout << "Enter 1 to add your Recipe" << endl;
        cout << "Enter 2 to display all recipe" << endl;
        cout << "Enter 3 to search and display particular recipe" << endl;
        cout << "Enter 4 to display common ingredients between two recipe" << endl;
        cout << "Enter 5 to sort/filter recipes based on likes/ratings" << endl;
        cout << "Enter 6 to get recipe of the day" << endl;
        cout << "Enter 7 to break" << endl;

        cin >> choice2;
        switch (choice2) {
            case 1: {
                cin.ignore();
                string name;
                cout << "Enter name of recipe: ";
                getline(cin, name);

                vector<pair<string, string> > ingredients;
                int numIngredients;
                cout << "Enter number of ingredients: ";
                cin >> numIngredients;
                cin.ignore();

                for (int i = 0; i < numIngredients; ++i) {
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

                // Save to Database
                string query = "INSERT INTO Recipes (name, instructions, prep_time, added_by_user_id) VALUES (?, ?, ?, ?)";
                MYSQL_STMT *stmt = mysql_stmt_init(conn);
                if (!stmt) break;

                if (mysql_stmt_prepare(stmt, query.c_str(), query.length())) {
                    mysql_stmt_close(stmt);
                    break;
                }

                MYSQL_BIND bind[4];
                memset(bind, 0, sizeof(bind));

                string prep_time_str = to_string(h) + " " + to_string(m) + " " + to_string(s);
                int user_id = u.getId();

                bind[0].buffer_type = MYSQL_TYPE_STRING;
                bind[0].buffer = (char *)name.c_str();
                bind[0].buffer_length = name.length();

                bind[1].buffer_type = MYSQL_TYPE_STRING;
                bind[1].buffer = (char *)instruct.c_str();
                bind[1].buffer_length = instruct.length();

                bind[2].buffer_type = MYSQL_TYPE_STRING;
                bind[2].buffer = (char *)prep_time_str.c_str();
                bind[2].buffer_length = prep_time_str.length();

                bind[3].buffer_type = MYSQL_TYPE_LONG;
                bind[3].buffer = &user_id;

                if (mysql_stmt_bind_param(stmt, bind) || mysql_stmt_execute(stmt)) {
                    cerr << "Failed to insert recipe: " << mysql_stmt_error(stmt) << endl;
                    mysql_stmt_close(stmt);
                    break;
                }

                int recipe_id = mysql_stmt_insert_id(stmt);
                mysql_stmt_close(stmt);

                // Insert Ingredients
                string query_ing = "INSERT INTO Ingredients (recipe_id, name, quantity) VALUES (?, ?, ?)";
                MYSQL_STMT *stmt_ing = mysql_stmt_init(conn);
                mysql_stmt_prepare(stmt_ing, query_ing.c_str(), query_ing.length());

                MYSQL_BIND bind_ing[3];
                for (int i = 0; i < ingredients.size(); ++i) {
                    memset(bind_ing, 0, sizeof(bind_ing));
                    bind_ing[0].buffer_type = MYSQL_TYPE_LONG;
                    bind_ing[0].buffer = &recipe_id;

                    bind_ing[1].buffer_type = MYSQL_TYPE_STRING;
                    bind_ing[1].buffer = (char *)ingredients[i].first.c_str();
                    bind_ing[1].buffer_length = ingredients[i].first.length();

                    bind_ing[2].buffer_type = MYSQL_TYPE_STRING;
                    bind_ing[2].buffer = (char *)ingredients[i].second.c_str();
                    bind_ing[2].buffer_length = ingredients[i].second.length();

                    mysql_stmt_bind_param(stmt_ing, bind_ing);
                    mysql_stmt_execute(stmt_ing);
                }
                mysql_stmt_close(stmt_ing);

                Recipe r1(name, ingredients, instruct, 0, 0.0, u, h, m, s);
                r1.setId(recipe_id);
                recipes.push_back(r1);

                cout << "Your Recipe got added" << endl;
                cout << r1;
                break;
            }
            case 2: {
                fetchRecipes(); // refresh
                cout << "Recipes available here:" << endl;
                for (int i = 0; i < recipes.size(); i++) {
                    cout << recipes[i] << endl;
                }
                break;
            }
            case 6: {
                if (recipes.empty()) {
                    cout << "No recipes available!" << endl;
                    break;
                }
                srand(time(0));
                int randomIndex = rand() % recipes.size();
                cout << "Recipe of the Day: " << endl;
                cout << recipes[randomIndex] << endl;
                break;
            }
            case 3: {
                cout << "Enter the name of the recipe to be displayed:" << endl;
                string name;
                cin.ignore();
                getline(cin, name);
                
                int size = recipes.size(), i;
                for (i = 0; i < size; i++) {
                    if (recipes[i].getRecipeName() == name) {
                        cout << recipes[i];
                        break;
                    }
                }
                if (i == size) cout << "No Recipe found" << endl;
                break;
            }
            case 4: {
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
                    if (recipes[i].getRecipeName() == name1) flag1 = i;
                    if (recipes[i].getRecipeName() == name2) flag2 = i;
                }

                if (flag1 != -1 && flag2 != -1)
                {
                    if (recipes[flag1] == recipes[flag2]) {}
                    else { cout << "These recipes have no common ingredients." << endl << endl; }
                }
                else { cout << "Either one or both recipes are not found." << endl << endl; }
                break;
            }
            case 5: {
                int choose;
                cout << "Enter 1 to filter based on likes(decreasing order)" << endl;
                cout << "Enter 2 to filter based on ratings(decreasing order)" << endl;
                cin >> choose;
                if (choose == 1) {
                    bubbleSortRecipes(recipes, &Recipe::getLikes);
                    for (int i = 0; i < recipes.size(); i++) cout << recipes[i];
                } else if (choose == 2) {
                    bubbleSortRecipes(recipes, &Recipe::getRatings);
                    for (int i = 0; i < recipes.size(); i++) cout << recipes[i];
                }
                break;
            }
            case 7: return;
        }
    }
}
