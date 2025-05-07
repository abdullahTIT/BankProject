#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
#include "clsCurrecyListScreen.h"
#include "clsFindCurrency.h"
#include "clsUpdatateCurrencyScreen.h"
#include "clsCurrencyCalculatorScreen.h"
class clsCurrencyMenue : protected clsScreen
{
private:
    enum enCurrencyMenueOptions {
        eShowCurrencyList = 1, eFindCurrency = 2, eUpdateCurrency = 3,
        eCurrencyCalculator = 4, eMainMenue = 5
    };
    static short _ReadCurrencyMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }
    static void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Menue...\n";
        system("pause>0");
        ShowCurrencyMenue();
        // Call the main menu function here
    }


    static void _ShowCurrencyList()
    {
        clsCurrecyListScreen::ShowCurrencyList();
    }

    static void _FindCurrency()
    {
        clsFindCurrency::ShowFindCurrencyScreen();
    }
    static void _UpdateCurrency()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }
    static void _CurrencyCalculator()
    {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }
    
    
    static void _PerformCurrencyMenueAction(enCurrencyMenueOptions Option)
    {
        switch (Option)
        {
        case enCurrencyMenueOptions::eShowCurrencyList:
            system("cls");
            _ShowCurrencyList();
            _GoBackToMainMenue();

            break;
        case enCurrencyMenueOptions::eFindCurrency:
            system("cls");
            _FindCurrency();
            _GoBackToMainMenue();
            break;
        case enCurrencyMenueOptions::eUpdateCurrency:
            system("cls");
            _UpdateCurrency();
            _GoBackToMainMenue();
            break;
        case enCurrencyMenueOptions::eCurrencyCalculator:
            system("cls");
            _CurrencyCalculator();
            _GoBackToMainMenue();
            break;
        case enCurrencyMenueOptions::eMainMenue:
            // Go back to main menu
            break;
        }
    }

public:
    static void ShowCurrencyMenue()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pShowCurrency))
        {
            return;
        }
        system("cls");
        _DrawScreenHeader("\t\tCurrency Menue");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tCurrency Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Currency List\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency\n";
        cout << setw(37) << left << "" << "\t[3] Update Currency\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformCurrencyMenueAction(enCurrencyMenueOptions(_ReadCurrencyMenueOption()));
    }

};

