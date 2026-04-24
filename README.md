# Recipe Management System
An Object-Oriented Programming (OOP) project built in C++ that uses a MySQL database.

---

## Indian Institute of Information Technology, Design & Manufacturing, Kancheepuram  
**PREPARED BY:**  
- **Gyan Chandra** – CS23I1053  
---

## 1. About the Project
This is a simple Recipe Management System built for my college OOPs project. It allows users to store, view, search, and rate recipes. Previously, the project used text files (`<fstream>`) to save data, but I have upgraded it to use a real **MySQL database** for better data management.

### Features
- **User Login & Signup:** Users can create an account and login. It uses MySQL to check if the user already exists.
- **Add Recipes:** Users can add new recipes, including the ingredients, cooking time, and instructions.
- **View Recipes:** You can see all the recipes in the database or search for a specific one.
- **Rate and Like:** You can like a recipe or give it a rating out of 5. The average rating is calculated mathematically.
- **Find Common Ingredients:** The project can compare two recipes to find matching ingredients.
- **Recipe of the Day:** It shows a random recipe every day.

---

## 2. Technical Details (OOPs Concepts Used)

I have used the following Object-Oriented Programming concepts in C++:
- **Classes & Objects:** Different classes like `User`, `Recipe`, and `Time` are used to organize the code.
- **Encapsulation:** Important data variables like `password` and `ratings` are kept `private` and accessed using public getters and setters.
- **Abstraction:** The complex database queries are hidden inside `utility.cpp`.
- **Composition:** The `Time` class is used as an object inside the `Recipe` class (a "has-a" relationship).
- **Function Templates:** I used `template <typename T>` to write a single bubble sort function that can sort recipes by both `likes` (integers) and `ratings` (doubles).
- **Operator Overloading:** I overloaded `<<` and `>>` to print objects directly using `cout`, and `==` to compare two recipes for common ingredients.

---

## 3. Database Architecture (MySQL)

Instead of using basic text files, the project now uses a normalized **MySQL** database called `recipe_db`.

The database has 3 tables:
1. **Users:** Stores `id`, `username`, `email`, and `password`.
2. **Recipes:** Stores `id`, `name`, `instructions`, `prep_time`, `likes`, `ratings`, and a foreign key `added_by_user_id`.
3. **Ingredients:** Because a recipe can have many ingredients, I made a separate table that stores `recipe_id`, `name`, and `quantity`.

I used **Prepared Statements** (`MYSQL_STMT`) so the database is secure from SQL injection, and **JOIN queries** to fetch all ingredients for a recipe at once.

---

## 4. How to Run This Project

### Requirements
- A 64-bit MinGW C++ compiler (`g++`)
- MySQL Server installed locally

### Setup Steps
1. Open MySQL and run the `schema.sql` file to create the tables.
2. Open `utility.cpp` and put your MySQL password where it says `const char *DB_PASS = "YourPassword";`
3. Double click on `build.bat` to compile the project.
4. Run `RecipeApp.exe` in your terminal or double-click it.
