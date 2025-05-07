#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen :protected clsScreen
{

private:

    static  bool _Login()
    {
        bool LoginFaild = false;
        short CountLogin = 0;
        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                CountLogin++;
                cout << "\nInvlaid Username/Password!\n\n";
                cout << "You have " << 3 - CountLogin << " tries left...\n";
                cout << "Please try again...\n";
            }
            if (CountLogin >= 3)
            {
                cout << "\nYou have entered wrong username/password 3 times, please try again later...\n";
                system("pause>0");
                return false;
            }
            

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);
        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenue();
        return true;
    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();
    }

};

