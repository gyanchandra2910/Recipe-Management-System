#include "Recipe.h"
int main()
{
    vector<Recipe> cont;

    User currentUser("rohit", "rohit@gmail.com", "12345678");

    vector<pair<string, string> > ingredients;
    ingredients.push_back(make_pair("Flour", "2 cups"));
    ingredients.push_back(make_pair("Milk", "1 cup"));

    Recipe recipe1("Pancakes", ingredients, "Mix ingredients and cook.", 5, 4, currentUser, 0, 15, 0);
    
    cont.push_back(recipe1);

    vector<pair<string, string> > ingredients2;
    ingredients2.push_back(make_pair("Bread", "2 slices"));
    ingredients2.push_back(make_pair("Cheese", "2 slices"));
    ingredients2.push_back(make_pair("Butter", "1 tbsp"));
    Recipe recipe2("Grilled Cheese Sandwich", ingredients2, "Butter bread and cook with cheese until golden brown.", 10, 5, currentUser, 0, 10, 0);

    cont.push_back(recipe2);

    vector<pair<string, string> > ingredients3;
    ingredients3.push_back(make_pair("Oats", "1 cup"));
    ingredients3.push_back(make_pair("Milk", "1 cup"));
    ingredients3.push_back(make_pair("Honey", "1 tbsp"));
    ingredients3.push_back(make_pair("Banana", "1 sliced"));
    Recipe recipe3("Overnight Oats", ingredients3, "Mix oats and milk. Refrigerate overnight. Top with honey and banana.", 7, 3, currentUser, 0, 8, 0);

    cont.push_back(recipe3);

    int choice;
    while(true)
    {
        cout<<"Enter 1 to login into our app"<<endl;
        cout<<"Enter 2 to exit"<<endl;
        cin>>choice;

        if(choice==2) break;
        else
        {
            User u;
            cout<<"Enter details(username,email,password)"<<endl;
            cin>>u;
            cout<<"Hello "<<u.getUsername()<<" Welcome! to our Recipe App"<<endl;
            cout<<endl;

            int choice2;

            while(true)
            {
                cout<<"Enter 1 to add your Recipe"<<endl;
                cout<<"Enter 2 to display all recipe"<<endl;
                cout<<"Enter 3 to search and display particular recipe"<<endl;
                cout<<"Enter 4 to display common ingredients between two recipe"<<endl;
                cout<<"Enter 5 to break"<<endl;

                cin>>choice2;
                switch(choice2)
                {
                    case 1:
                    {
                        cin.ignore();  
                        string name;
                        cout << "Enter name of recipe: ";
                        getline(cin, name);  

                        vector<pair<string, string> > ingredients;  

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

                        Recipe r1(name, ingredients, instruct,10, 4,u, h, m, s);
                        cont.push_back(r1);
                        cout<<"Your Recipe got added"<<endl;
                        cout<<r1;
                        break;

                    }

                    case 2:
                    {
                        cout<<"Recipes available here:"<<endl;
                        int size=cont.size();
                        for(int i=0;i<size;i++)
                        {
                            cout<<cont[i];
                            cout<<endl;
                        }
                        break;
                    }
                    case 3:
                    {
                        cout<<"Enter name of recipe to be displayed:"<<endl;
                        string name;
                        cin.ignore();
                        getline(cin,name);

                        int size=cont.size(),i;
                        for(i=0;i<size;i++)
                        {
                            if(cont[i].getRecipeName()==name)
                            {
                                cout<<cont[i];
                                break;
                            }
                        }
                        if(i==size)
                        cout<<"No Recipe found"<<endl;
                        break;
                    }

                    case 4:
                    {
                        
                    }
                }

                if(choice2==5)
                {
                    break;
                }
            }
        }
    }
}