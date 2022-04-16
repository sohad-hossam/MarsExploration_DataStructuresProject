// Project DS 2021 final.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MarsStation.h"

using namespace std;

int main()
{
	int day = 1;
	int mofopp;
	int goon = 1;
	cout << "Enter mode of operation: " << endl;
	cout << "Enter 1 for Interactive mode" << endl;
	cout << "Enter 2 for Step by Step mode" << endl;
	cout << "Enter 3 for Silent mode" << endl;
	cin >> mofopp;
	MarsStation<int> m(mofopp);
	m.load();
	do
	{
		m.fillingmissionslists();
		m.assignment();
		if (mofopp == 1)
		{
			m.UIinterface();
			cout << "Press any number to continue: " << endl;
			cin >> goon;
		}
		if (mofopp == 2)
		{
			m.UIinterface();
		}
		day++;
		m.setDay(day);

	} while (!(m.checkifcompleted()));
	if (mofopp == 3)
	{
		m.UIinterface();
	}
	m.OutputFile();
	return 0;
}

