#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferLogScreen.h"

class clsTransctionScreen :protected clsScreen
{
private:
    enum enTransctionMenueOptions
    {
        eDeposit = 1, eWithdraw = 2, eTransfer = 3,
        eShowTotalBalance = 4,eShowTransferLog = 5, eGoBack = 6
    };
    static short _ReadTransctionMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }
    static  void _GoBackToTransction()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");
        ShowTransctionMenue();
    }
    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }
    static void _ShowWithdrawScreen()
    {
        clsWithDrawScreen::ShowWithdrawScreen();
    }
    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }
    static void _Transfer()
    {
        clsTransferScreen::ShowTransferScreen();
    }
   
    static void _ShowTransferLogScreen()
    {
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _PerfromTransctionMenu(enTransctionMenueOptions option)
    {
        switch (option)
        {
        case enTransctionMenueOptions::eDeposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransction();
            break;
        case enTransctionMenueOptions::eWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransction();
            break;
        case enTransctionMenueOptions::eShowTotalBalance:
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransction();
            break;
        case enTransctionMenueOptions::eTransfer:
            system("cls");
            _Transfer();
            _GoBackToTransction();
            break;
        case enTransctionMenueOptions::eShowTransferLog:
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransction();
            break;
        case enTransctionMenueOptions::eGoBack:

            break;
        default:
            break;
        }
      
    }

public:
    static void ShowTransctionMenue()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            return;
        }

        system("cls");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\tTransction Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "1. Deposit Money\n";
        cout << setw(37) << left << "" << "2. Withdraw Money\n";
        cout << setw(37) << left << "" << "3. Transfer Money\n";
        cout << setw(37) << left << "" << "4. Show Total Balance\n";
        cout << setw(37) << left << "" << "5. Show Transfer Log\n";
        cout << setw(37) << left << "" << "6. Go Back\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerfromTransctionMenu((enTransctionMenueOptions)_ReadTransctionMenueOption());
    }
};

