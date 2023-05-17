#include "ClientHelp.h"
#include "AuthenticationHelp.h"

int main(int argc, char * argv[])
{
    // Disable buffering
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);

    AuthenticationSystem authenticator;
    string userId = authenticator.Run();
    
    Client client(userId);
    client.Connect("localHost", 2524);
    client.Run();
    return 0;
}
