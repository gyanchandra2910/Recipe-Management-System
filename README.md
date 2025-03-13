🍲 Recipe Management App
A C++ OOP-Based Project

📌 Overview
The Recipe Management App is a console-based C++ application designed to store, manage, and retrieve recipe information efficiently. It leverages core Object-Oriented Programming (OOP) principles like encapsulation, abstraction, inheritance, and polymorphism to create a modular, scalable, and maintainable application.

🎯 Objective
The primary goal of this project is to create a user-friendly application where users can:
✅ Store and manage recipes
✅ Authenticate and authorize users
✅ Sort and filter recipes based on various attributes
✅ Provide persistent storage using file handling

🚀 Features
1. Encapsulation and Abstraction
Classes for Recipe, User, and Time
Private attributes with public getter and setter functions
2. File Handling
Save and load recipe data from text files
Persistent storage for recipes and user data
3. User Authentication and Authorization
Secure signup and login
Prevents duplicate account creation
4. Function Templates
Bubble sort recipes by likes and ratings
Generic sorting using function templates
5. Operator and Function Overloading
<< and >> operators for recipe input and output
== operator to check common ingredients between recipes
Constructor overloading and copy constructors
6. Recipe Management
Add, modify, and delete recipes
Increase likes and update ratings
Check for duplicate recipes
7. Recipe of the Day
Randomly selects and displays a recipe
🏗️ Project Structure
plaintext
Copy
Edit
├── src
│   ├── main.cpp
│   ├── Recipe.cpp
│   ├── User.cpp
│   ├── Time.cpp
├── include
│   ├── Recipe.h
│   ├── User.h
│   ├── Time.h
├── data
│   ├── users.txt
│   ├── recipes.txt
├── README.md
├── Makefile
└── .gitignore
💻 Technologies Used
Language: C++
Concepts: OOP (Encapsulation, Abstraction, Inheritance, Polymorphism), File Handling
IDE: VS Code
