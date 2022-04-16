#pragma once
#include"EventClass.h"
#include "Rovers.h"
#include"MarsStation.h"
#include<iostream>
//#include <fstream>
#include"windows.h"
//#include"MarsStation.h"
using namespace std;

template <typename T>
class MarsStation;

template <typename T>
class UI
{
	int flag;
	//int dayy;
	MarsStation<T>* marsobj;
	int counter = 0;
	Missions<T> missobj;
	Rovers<T> roversobj;
	int goOn = 0;
	//===========================================================//
	//=============================================================//
public:
	UI(int flage, MarsStation<T>* m);
	void Interfacefunction();
	//void Interface();
	~UI();
};

template <typename T>
UI<T>::UI(int flage, MarsStation<T>* m)
{
	flag = flage;
	marsobj = m;
}
template<typename T>
inline void UI<T>::Interfacefunction()
{
	if (flag == 1 || flag == 2)
	{
		Queue<T>* Data = new Queue<T>(marsobj->UIinteractivemode());
		int x;
		Data->dequeue(x);  //1
		cout << "Current Day:" << " " << x << endl;
		Data->dequeue(x);  //2
		cout << x << " " << "Waiting Missions:" << " ";
		Data->dequeue(x); //emergencywaitingcount 3
		int countemergwaiting = x;
		Data->dequeue(x); //polarwaitingcount 4
		int countpolarwaiting = x;
		if (countemergwaiting != 0)
		{
			cout << "[";

			for (int i = 0; i < countemergwaiting - 1; i++)
			{
				Data->dequeue(x);    //5 emergwaiting
				cout << x << ",";
			}
			Data->dequeue(x);
			cout << x << "]";
		}
		if (countpolarwaiting != 0)
		{
			cout << "(";

			for (int i = 0; i < countpolarwaiting - 1; i++)
			{
				Data->dequeue(x);        //6 polar waiting
				cout << x << ",";
			}
			Data->dequeue(x);
			cout << x << ")";
		}
		cout << endl;
		cout << "-------------------------------------------------------------" << endl;
		Data->dequeue(x);  //7
		cout << x << " " << "In-Execution Missions/Rovers:" << " ";
		Data->dequeue(x); //inexc emerg missions 8
		int countinexcemergmiss = x;
		Data->dequeue(x); //inexc polar missions 9
		int countinexcpolarmiss = x;
		if (countinexcemergmiss != 0)
		{
			cout << "[";

			for (int i = 0; i < countinexcemergmiss - 1; i++)
			{
				Data->dequeue(x);     //10inexc emerg mission id
				cout << x << "/";
				Data->dequeue(x);     //11 inexc emerg rover id
				cout << x << ",";
			}
			Data->dequeue(x);
			cout << x << "/";
			Data->dequeue(x);
			cout << x << "]";
		}
		if (countinexcpolarmiss != 0)
		{
			cout << "(";

			for (int i = 0; i < countinexcpolarmiss - 1; i++)
			{
				Data->dequeue(x);     //12inexc polar mission id
				cout << x << "/";
				Data->dequeue(x);     //13 inexc polar rover id
				cout << x << ",";
			}
			Data->dequeue(x);
			cout << x << "/";
			Data->dequeue(x);
			cout << x << ")";
		}
		cout << endl;
		cout << "-------------------------------------------------------------" << endl;
		Data->dequeue(x);  //14 
		cout << x << " " << "Available Rovers:" << " ";
		Data->dequeue(x); //emergencyavailablerovercount 15
		int countemergavailablerover = x;
		Data->dequeue(x); //polaravailablerovercount 16
		int countpolaravailablerover = x;
		if (countemergavailablerover != 0)
		{
			cout << "[";

			for (int i = 0; i < countemergavailablerover - 1; i++)
			{
				Data->dequeue(x);    //17 available emerg rover id
				cout << x << ",";
			}
			Data->dequeue(x);
			cout << x << "]";
		}
		if (countpolaravailablerover != 0)
		{
			cout << "(";

			for (int i = 0; i < countpolaravailablerover - 1; i++)
			{
				Data->dequeue(x);        //18 available polar rover id
				cout << x << ",";
			}
			Data->dequeue(x);
			cout << x << ")";
		}
		cout << endl;
		cout << "-------------------------------------------------------------" << endl;
		Data->dequeue(x);  //19 
		cout << x << " " << "In-Checkup Rovers:" << " ";
		Data->dequeue(x); //emergencyundercheckrovercount 20
		int countemergundercheckrover = x;
		Data->dequeue(x); //polarundercheckrovercount 21
		int countpolarundercheckrover = x;
		if (countemergundercheckrover != 0)
		{
			cout << "[";

			for (int i = 0; i < countemergundercheckrover - 1; i++)
			{
				Data->dequeue(x);    //22 undercheck emerg rover id
				cout << x << ",";
			}
			Data->dequeue(x);
			cout << x << "]";
		}
		if (countpolarundercheckrover != 0)
		{
			cout << "(";

			for (int i = 0; i < countpolarundercheckrover - 1; i++)
			{
				Data->dequeue(x);        //23 undercheckpolar rover id
				cout << x << ",";
			}
			Data->dequeue(x);
			cout << x << ")";
		}
		cout << endl;
		cout << "-------------------------------------------------------------" << endl;
		Data->dequeue(x);  //24
		cout << x << " " << "Completed Missions:" << " ";
		Data->dequeue(x); //emergencycompletedmissioncount 25
		int countemergcompletedmiss = x;
		Data->dequeue(x); //polarcompletedmissioncount 26
		int countpolarcompletedmiss = x;
		if (countemergcompletedmiss != 0)
		{
			cout << "[";

			for (int i = 0; i < countemergcompletedmiss - 1; i++)
			{
				Data->dequeue(x);    //27 emerg completed mission id
				cout << x << ",";
			}
			Data->dequeue(x);
			cout << x << "]";
		}
		if (countpolarcompletedmiss != 0)
		{
			cout << "(";

			for (int i = 0; i < countpolarcompletedmiss - 1; i++)
			{
				Data->dequeue(x);        //28 polar completed mission id
				cout << x << ",";
			}
			Data->dequeue(x);
			cout << x << ")";
		}
		cout << endl;
		if (flag == 2)
		{
			Sleep(1000);
		}
	}
	else if (flag == 3)
	{
		cout << "Silent Mode" << endl;
		cout << "Simulation Started" << endl;
		cout << "Simulation ends, Output file created" << endl;
	}
	else
	{
		cout << "that's not an avilable interface mode" << endl;
	}
}

template <typename T>
UI<T>::~UI()
{

}
