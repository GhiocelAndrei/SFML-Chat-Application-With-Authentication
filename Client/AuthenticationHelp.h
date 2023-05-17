#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>

using namespace std;

class AuthenticationSystem{
    string loggedInUserId;

public:
    string Run();
    void Registration(); 
    void Login();
    void ForgotPassword();
};
