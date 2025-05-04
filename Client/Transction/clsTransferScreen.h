
#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
class clsTrasferScreen : protected clsScreen
{
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

public:
    static void ShowTransfer()
    {
        _DrawScreenHeader("\t   Transfer Screen");
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);
        string AccountNumber2 = "";
        cout << "\nPlease enter AccountNumber to transfer? ";
        cin >> AccountNumber2;
        while (!clsBankClient::IsClientExist(AccountNumber2))
        {
            cout << "\nClient with [" << AccountNumber2 << "] does not exist.\n";
            AccountNumber2 = _ReadAccountNumber();
        }
        clsBankClient Client2 = clsBankClient::Find(AccountNumber2);
        _PrintClient(Client2);
        double Amount = 0;
        cout << "\nPlease enter Transfer amount? ";
        Amount = clsInputValidate::ReadDblNumber();
        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client1.AccountBalance < Amount)
            {
                cout << "\nInsufficient Balance.\n";
                return;
            }
            Client1.Withdraw(Amount);
            Client2.Deposit(Amount);
            cout << "\nTransaction Completed Successfully.\n";
            cout << "\nNew Balance of [" << Client1.FullName() << "] is [" << Client1.AccountBalance << "]\n";
            cout << "\nNew Balance of [" << Client2.FullName() << "] is [" << Client2.AccountBalance << "]\n";
        }
        else
        {
            cout << "\nTransaction Cancelled.\n";
        }
    }

};

