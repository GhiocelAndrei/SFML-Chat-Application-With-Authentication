#include "AuthenticationHelp.h"

#ifdef _WIN32
    const string clearCommand = "cls";
#elif __linux__
    const string clearCommand = "clear";
#elif __APPLE__
    const string clearCommand = "clear";
#else
    const string clearCommand = ""; // Unsupported operating system
#endif

string AuthenticationSystem::Run()
{
    cout<<"\t\t\t            Welcome to Andrei's Chatt App \n\n";
    cout<<"\t\t\t _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n";
    cout<<"\t | Press 1 to LOGIN                    |\n";
    cout<<"\t | Press 2 to REGISTER                 |\n";
    cout<<"\t | Press 3 if you forgot your PASSWORD |\n";
    cout<<"\t | Press 4 to EXIT                     |\n";
    cout<<"\n\t\t\t Please enter your choice :";

    int option;
    cin>>option;
    cout<<endl;
    switch(option)
    {
        case 1:
            Login();
            break;

        case 2:
            Registration();
            break;

        case 3:
            ForgotPassword();
            break;

        case 4:
            cout<<"\t\t\t Have a great day ! \n\n";
            break;

        default:
            if (!clearCommand.empty()) 
            {
                system(clearCommand.c_str());
            }
            cout<<"\t\t\t Please select from the options given above \n\n";
            Run();
    }

    return loggedInUserId;
}

void AuthenticationSystem::Registration()
{
    string registrationUserId, registrationPassword;

    if (!clearCommand.empty()) 
    {
        system(clearCommand.c_str());
    }

    cout<<"\t\t\t Enter the username :";
    cin>>registrationUserId;
    cout<<"\t\t\t Enter the password :";
    cin>>registrationPassword;

    ofstream f1("users.txt", ios::app);
    f1<<registrationUserId<<" "<<registrationPassword<<endl;

    if (!clearCommand.empty()) 
    {
        system(clearCommand.c_str());
    }
    cout<<"\n\t\t\t Registration is successfull ! \n";
    Run();
} 

void AuthenticationSystem::Login()
{
    bool correctCredentials = false;
    string userId, password, userIdIterator, passwordIterator;
    if (!clearCommand.empty()) 
    {
        system(clearCommand.c_str());
    }

    cout<<"\t\t\t Please enter the username and password : \n";
    cout<<"\t\t\t USERNAME :";
    cin>>userId;
    cout<<"\t\t\t PASSWORD :";
    cin>>password;

    ifstream input("users.txt");
    while(input>>userIdIterator>>passwordIterator)
    {
        if(userId == userIdIterator && password == passwordIterator)
        {
            correctCredentials = true;
            loggedInUserId = userId;
            if (!clearCommand.empty()) 
            {
                system(clearCommand.c_str());
            }
            break;
        }
    }

    input.close();

    if(correctCredentials == true)
    {
        cout<<"Welcome "<<userId<<" ! Thanks for loggin in ! \n";
    }
    else
    {
        cout<<"\n LOGIN ERROR !\n Please check your username and password\n";
        Run();
    }
}

void AuthenticationSystem::ForgotPassword()
{
    if (!clearCommand.empty()) 
    {
        system(clearCommand.c_str());
    }
    
    string userId, userIdIterator, passwordIterator;
    bool foundUser = false;
    cout<<"Please enter your username :";
    cin>>userId;

    ifstream input("users.txt");
    while(input>>userIdIterator>>passwordIterator)
    {
        if(userId == userIdIterator)
        {
            foundUser = true;
            if (!clearCommand.empty()) 
            {
                system(clearCommand.c_str());
            }
            break;
        }
    }

    input.close();

    if(foundUser == true)
    {
        cout<<"Your password is :"<<passwordIterator<<endl;
    }
    else
    {
        cout<<"\n Recover password failed ! There isn't any user registered with username :"<<userId<<endl;
    }

    Run();
}