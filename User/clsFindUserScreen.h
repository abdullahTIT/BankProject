#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
class clsFindUserScreen :protected clsScreen
{
public:
    static void FindUser()
    {
        system("cls");
        _DrawScreenHeader("\t\tFind User");
        string UserName = "";
        cout << "\nPlease Enter User Number: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUserName  is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(UserName);
        User.Print();
    }
};

