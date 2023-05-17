#include "ServerHelp.h"

int main(int argc, char *argv[])
{
    // Disable buffering
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);

    Server server(2524);
    server.Run();
    return 0;
}
