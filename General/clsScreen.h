#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t" << CurrentUser.UserName << endl;
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout << "\t\t\t\t\tUser:" << CurrentUser.UserName << endl;
        cout << "\t\t\t\t\t" << clsDate::DateToString(clsDate()) << endl;
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            cout << "\t\t\t\t\t  You don't have access to this option";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;

        }
        else
            return true;

    }
};

