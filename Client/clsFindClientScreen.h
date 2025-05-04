#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsFindClientScreen :protected clsScreen
{
public:
    static void FindClient()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;
        }

        system("cls");
        _DrawScreenHeader("\t\tFind Client");
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        Client1.Print();
    }
};

