#include <iostream>
#include <fstream>
#include "clsLoginScreen.h"
using namespace std;

#include "clsUser.h"
int main()
{

    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }

    return 0;
}
