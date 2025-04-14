# Recipe Management System
Object-Oriented Programming (OOP) based Recipe Management Application

---

## Indian Institute of Information Technology, Design & Manufacturing, Kancheepuram  
**PREPARED BY:**  
- **Gyan Chandra** – CS23I1053  

---

## 1. Project Overview
This Recipe Management System is developed using core Object-Oriented Programming (OOP) principles to create an efficient system for storing, retrieving, and managing recipe information.

### 1.1 Objective
The primary objective is to create a user-friendly Recipe Management Application that allows users to:
- Store and retrieve recipes
- Rate and like recipes
- Search for specific recipes 
- Manage recipe ingredients

This application leverages OOP concepts such as:
- **Encapsulation**  
- **Abstraction**  
- **Classes**  
- **Composition**  

The goal is to ensure modular and maintainable code.

### 1.2 Features Implemented
The following OOP features and techniques have been applied:

- **Encapsulation:**  
   Bundling data (attributes) and functions (behaviors) within a class. Each class (like Recipe or User) controls access to its data to maintain integrity and modularity.

- **Abstraction:**  
   Exposing only essential attributes and behaviors while hiding internal implementation details. Data members are private, accessed via public functions.

- **Classes and Composition:**  
   - Defined classes for Recipe, User, and Time.  
   - Composition shows a "has-a" relationship where Recipe includes a Time object.  

- **Function Templates:**  
   - Generic templates for sorting and filtering recipes based on likes and ratings.  
   - Code reusability and flexibility.  

- **File Handling:**  
   - Persistent storage for recipes and user data using text files.  
   - Ensures data is saved and retrieved even after restarting the application.  

- **User Authentication and Authorization:**  
   - Login and signup systems.  
   - Prevents duplicate accounts and ensures secure access.  

---

## 2. Class Architecture

### 2.1 **Recipe Class**  
```cpp
class Recipe {
private:
    string recipeName;
    vector<string> ingredients;
    string instructions;
    Time preparationTime;
    double ratings;
    int likes;
    int ratingCount;
    string addedBy;
    
public:
    // Methods for managing recipe data
    void addRatings(double);
    void addIngredients(string);
    void removeIngredients(string);
    void increaseLikes();
    string getRecipeName();
    // ... other methods
};
```
- Key data members are private.  
- Public methods provide controlled access.  

### 2.2 **User Class**  
```cpp
class User {
private:
    string username;
    string email;
    string password;
    
public:
    // Authentication and profile methods
    string getUsername();
    void setPassword(string);
    bool authenticate(string);
    // ... other methods
};
```
- Private members like `username` and `password` are accessible only through public methods.
- Ensures secure handling of user data.  

### 2.3 **Time Class**  
```cpp
class Time {
private:
    int hour;
    int minute;
    int second;
    
public:
    // Time manipulation methods
    void setTime(int, int, int);
    void getTime();
    // ... other methods
};
```
- Encapsulation of hour, minute, and second fields.  
- Included as a member of the `Recipe` class using composition.  

---

## 3. User Authentication System

### 3.1 **Signup Process**
- User selects Signup and enters a username and password.  
- System checks for duplicate usernames
- Credentials are saved to a file.  
- A welcome message confirms successful signup.  

### 3.2 **Login Process**
- User inputs credentials for login.  
- System validates against stored data
- If matched, displays "Login successful!"  

### 3.3 **Authorization Features**
- Prevents creating accounts with the same username.  
- Only recipe creators can modify their own recipes
- Secure credential storage

---

## 4. Advanced Features

### 4.1 **Function Templates**
Function templates enable generic programming for different data types and operations:  

```cpp
template <typename T>
void bubbleSortRecipes(vector<Recipe>& recipes, T Recipe::* field, bool ascending = false) {
    // Sorting implementation
}
```

- `bubbleSortRecipes()` sorts recipes by likes or ratings.  
- Works for both `int` (likes) and `double` (ratings).
- Optimized with early stopping using a swapped flag
- User can choose the sorting criterion.  

### 4.2 **Operator Overloading**
```cpp
// Output operator
ostream& operator<<(ostream& out, Recipe& recipe);

// Input operator
istream& operator>>(istream& in, Recipe& recipe);

// Comparison operator
bool operator==(Recipe& recipe1, Recipe& recipe2);
```

- **Overloaded `<<` Operator:** Displays recipe details in a formatted way.  
- **Overloaded `>>` Operator:** Takes input for data members in one go.  
- **Overloaded `==` Operator:** Compares recipes based on common ingredients.  
- **Function Overloading:** Multiple constructors for Recipe with different parameters.  

---

## 5. Recipe Management Features

### 5.1 **Modify Ingredients**
- `addIngredients()` – Adds ingredients to a recipe.  
- `removeIngredients()` – Removes ingredients from a recipe.  

**Authorization:**  
- Only logged-in users can modify their own recipes.  

### 5.2 **Social Features**
- **Increase Likes:** `increaseLikes()` – Adds 1 to the total likes.  
- **Add Ratings:** `addRatings()` – Updates average rating using:  
```
ratings = (ratings × ratingCount + addedRating) / (ratingCount + 1)
```
- **Find Common Ingredients:** Check if recipes share ingredients using overloaded `==` operator

### 5.3 **Recipe Discovery**
- Search functionality for finding specific recipes
- Sort recipes by popularity (likes) or quality (ratings)
- Recipe of the day feature (random selection)

---

## 6. Data Storage
The application uses file-based persistence:
- `user.txt` - Stores user credentials
- `recipeName.txt` - Stores recipe names
- `addedRecipe.txt` - Stores complete recipe details

This approach ensures data persistence between application sessions.

---

## 7. Building and Running

### Prerequisites
- C++ compiler (C++11 or higher)
- Standard Template Library (STL)

### Compilation
```bash
g++ main.cpp defs.cpp utility.cpp -o recipe_app
```

### Execution
```bash
./recipe_app
```

---

## 8. Future Enhancements
- Graphical user interface
- Recipe categorization and tags
- Nutritional information calculation
- Image support for recipes
- Import/export feature for recipe sharing

---
