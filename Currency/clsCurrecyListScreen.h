#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
class clsCurrecyListScreen :protected clsScreen
{
private:
    static void _PrintCurrencyRecordLine(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << setw(12) << left << Currency.CurrencyCode();
        cout << "| " << setw(30) << left << Currency.Country();
        cout << "| " << setw(30) << left << Currency.CurrencyName();
        cout << "| " << setw(20) << left << Currency.Rate();
    }
public:
    static void ShowCurrencyList()
    {
        vector <clsCurrency> vCurrencys = clsCurrency::GetCurrenciesList();
        string Title = "\t  Currency List Screen";
        string SubTitle = "\t    (" + to_string(vCurrencys.size()) + ") Currency(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(12) << "Currency Code";
        cout << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(30) << "Currency Name";
        cout << "| " << left << setw(20) << "Rate";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
        if (vCurrencys.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        else
            for (clsCurrency Currency : vCurrencys)
            {
                _PrintCurrencyRecordLine(Currency);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }
};

