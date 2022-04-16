#pragma once
#include"EventClass.h"
#include "Rovers.h"
#include"FormulationEvent.h"
#include <fstream>
#include <string>
#include"UI.h"
template <typename T>
class FormulationEvent;

template <typename T>
class UI;

template <typename T>

class MarsStation
{
	int day = 1;
	int interfacemode = 0;
	int missionsassigned = 0; //no of missions the rover took before getting checkup
	float TotalNoOfMissions = 0.0;
	int totalemgmiss = 0, totalpolmiss = 0;
	float totalwaitingdays = 0.0, totalexcutiondays = 0.0;
	int numberofemergencyrovers, numberofpolarrovers;
	int createRID = 0;

	//UI<T> UIobj;
	PriorityQueue<Missions<T>*> WaitingEmergencyMissions;
	Queue<Missions<T>*> WaitingPolarMissions;
	PriorityQueue<EventClass*> ListOfEventPtrs;
	Queue<Rovers<T>*> AvailableEmergRovers;
	Queue<Rovers<T>*> AvailablePolarRovers;
	PriorityQueue<Missions<T>*> InExcutionMissions;
	PriorityQueue<Rovers<T>*> InExcutionRovers;
	Queue<Missions<T>*> CompletedMissions;
	Queue<Rovers<T>*> UnderCheckEmergRovers;
	Queue<Rovers<T>*> UnderCheckPolarRovers;

	Queue<Rovers<T>*> InmaintenanceRovers;




public:
	MarsStation();
	MarsStation(int interfacemode);
	void addtoemergencymiss(Missions<T>* emergenmiss, int sig);
	void addtopolarmiss(Missions<T>* polarmiss);
	void load();
	void fillingmissionslists();
	void assignment();
	void OutputFile();
	void setDay(int d);
	void UIinterface();
	bool checkifcompleted();
	int Getday();
	Queue<T> UIinteractivemode();

	//======================================================================//

	//================================================================= =//


	~MarsStation();
};

template<typename T>
inline MarsStation<T>::MarsStation()
{
}

template<typename T>
MarsStation<T>::MarsStation(int im)
{
	interfacemode = im;
}

template<typename T>
void MarsStation<T>::load()
{
	int speedofpolarrovers, speedofemergencyrovers;
	int numbeforechechup, polarcheckupdur, emergencycheckupdur;
	int numofevents;
	char eventtype, missiontype;
	int eventday, ID, missionduration, significance, TargetLoc;
	ifstream inFile;
	inFile.open("Input File_1.txt");

	//checking for errors
	if (inFile.fail())
	{
		cerr << "Error opening file" << endl;
		exit(1);
	}

	inFile >> numberofpolarrovers >> numberofemergencyrovers;
	inFile >> speedofpolarrovers >> speedofemergencyrovers;
	inFile >> numbeforechechup >> polarcheckupdur >> emergencycheckupdur;
	inFile >> numofevents;



	for (int i = 0; i < numberofpolarrovers; i++)
	{
		Rovers<T>* PolarRover = new Rovers<T>('P', polarcheckupdur, speedofpolarrovers, numbeforechechup, createRID);
		AvailablePolarRovers.enqueue(PolarRover);
		createRID++;
	}


	for (int i = 0; i < numberofemergencyrovers; i++)
	{
		Rovers<T>* EmergencyRover = new Rovers<T>('E', emergencycheckupdur, speedofemergencyrovers, numbeforechechup, createRID);
		AvailableEmergRovers.enqueue(EmergencyRover);
		createRID++;
	}

	for (int i = 0; i < numofevents; i++)
	{
		inFile >> eventtype >> missiontype >> eventday >> ID >> TargetLoc >> missionduration >> significance;
		EventClass* TempEventpointer = new FormulationEvent<T>(eventday, missiontype, TargetLoc, significance, missionduration, ID, this);

		ListOfEventPtrs.insert(TempEventpointer, eventday);
	}
	inFile.close();


}

template<typename T>
void MarsStation<T>::addtoemergencymiss(Missions<T>* emergenmiss, int sig)
{
	WaitingEmergencyMissions.insert(emergenmiss, sig);
}
template<typename T>
void MarsStation<T>::addtopolarmiss(Missions<T>* polarmiss)
{
	WaitingPolarMissions.enqueue(polarmiss);
}
template<typename T>
void MarsStation<T>::fillingmissionslists()
{
	EventClass* TempEventpointer = new FormulationEvent<T>;
	while (ListOfEventPtrs.peek(TempEventpointer))
	{
		if (TempEventpointer->getfd() == day)
		{
			ListOfEventPtrs.dequeue(TempEventpointer);
			TempEventpointer->Execute();
		}
		else
		{
			break;
		}
	}
}

template<typename T>
void MarsStation<T>::assignment() //wla nrga3ha bool
{

	//============================================================================//
	while (!InmaintenanceRovers.isEmpty())//finishing maintainance and going back to available 
	{
		Rovers<T>* temproversobj = new Rovers<T>;
		InmaintenanceRovers.peek(temproversobj);
		if (temproversobj->Ismaintened())
		{
			InmaintenanceRovers.dequeue(temproversobj);
			if (temproversobj->getRoverType() == 'E')
			{
				AvailableEmergRovers.enqueue(temproversobj);
			}
			else
			{
				AvailablePolarRovers.enqueue(temproversobj);
			}
			Queue<Rovers<T>*> tempqueue;
			while (!InmaintenanceRovers.isEmpty())
			{
				InmaintenanceRovers.dequeue(temproversobj);
				temproversobj->incrementmaintainancecounter();
				tempqueue.enqueue(temproversobj);
			}
			while (tempqueue.dequeue(temproversobj))
			{
				InmaintenanceRovers.enqueue(temproversobj);
			}

		}
	}

	//============================================================================//


	while (!UnderCheckEmergRovers.isEmpty())
	{
		Rovers<T>* temproversobj = new Rovers<T>;
		UnderCheckEmergRovers.peek(temproversobj);
		if (temproversobj->Ischeckedup())
		{
			UnderCheckEmergRovers.dequeue(temproversobj);
			temproversobj->resetnumofmissions();
			AvailableEmergRovers.enqueue(temproversobj);
		}
		Queue<Rovers<T>*> tempqueue;
		while (!UnderCheckEmergRovers.isEmpty())
		{
			UnderCheckEmergRovers.dequeue(temproversobj);
			temproversobj->incrementcheckupcounter();
			tempqueue.enqueue(temproversobj);
		}
		while (tempqueue.dequeue(temproversobj))
		{
			UnderCheckEmergRovers.enqueue(temproversobj);
		}
		break;

	}

	while (!UnderCheckPolarRovers.isEmpty())
	{
		Rovers<T>* temproversobj = new Rovers<T>;
		UnderCheckPolarRovers.peek(temproversobj);
		if (temproversobj->Ischeckedup())
		{
			UnderCheckPolarRovers.dequeue(temproversobj);
			temproversobj->resetnumofmissions();
			AvailablePolarRovers.enqueue(temproversobj);
		}

		Queue<Rovers<T>*> tempqueue;
		while (!UnderCheckPolarRovers.isEmpty())
		{
			UnderCheckPolarRovers.dequeue(temproversobj);
			temproversobj->incrementcheckupcounter();
			tempqueue.enqueue(temproversobj);

		}
		while (tempqueue.dequeue(temproversobj))
		{
			UnderCheckPolarRovers.enqueue(temproversobj);
		}
		break;

	}


	Missions<T>* tempmissobj = new Missions<T>;
	while (!WaitingEmergencyMissions.isEmpty())
	{
		Rovers<T>* temprover = new Rovers<T>;
		if (AvailableEmergRovers.dequeue(temprover))
		{
			WaitingEmergencyMissions.dequeue(tempmissobj);
			//Missions<T>* tempmissptr = new Missions<T>(tempmissobj);
			//Missions<T>* tempmissptr =&tempmissobj;   //lesa hant2kd
			temprover->setMission(tempmissobj);
			temprover->incrementnumofmission();
			//temprover->setneedcheckcounter(missionsassigned);
			temprover->setExecDay(); //??
			tempmissobj->setCD(tempmissobj->getWD() + tempmissobj->getFD() + tempmissobj->getED());
			InExcutionMissions.insert(tempmissobj, tempmissobj->getCD());
			InExcutionRovers.insert(temprover, tempmissobj->getCD());
		}
		else if (AvailablePolarRovers.dequeue(temprover))
		{
			WaitingEmergencyMissions.dequeue(tempmissobj);
			//Missions<T>* tempmissptr = new Missions<T>(tempmissobj);
			temprover->setMission(tempmissobj);
			temprover->incrementnumofmission();
			//temprover->setneedcheckcounter(missionsassigned);
			temprover->setExecDay();
			tempmissobj->setCD(tempmissobj->getWD() + tempmissobj->getFD() + tempmissobj->getED());
			InExcutionMissions.insert(tempmissobj, tempmissobj->getCD());//ed or cd????
			InExcutionRovers.insert(temprover, tempmissobj->getCD());//msh 3arfeen el priority sa7 kda wala elmafrood 3l ED
		}
		else if (InmaintenanceRovers.dequeue(temprover))
		{
			WaitingEmergencyMissions.dequeue(tempmissobj);
			//Missions<T>* tempmissptr = new Missions<T>(tempmissobj);
			temprover->setMission(tempmissobj);
			temprover->SetSpeedtoHalf();
			temprover->incrementnumofmission();
			//temprover->setneedcheckcounter(missionsassigned);
			temprover->setExecDay();
			tempmissobj->setCD(tempmissobj->getWD() + tempmissobj->getFD() + tempmissobj->getED());
			InExcutionMissions.insert(tempmissobj, tempmissobj->getCD());//ed or cd????
			InExcutionRovers.insert(temprover, tempmissobj->getCD());
		}

		else
		{
			Queue<Missions<T>*> tempqueue;
			while (!WaitingEmergencyMissions.isEmpty())
			{
				WaitingEmergencyMissions.dequeue(tempmissobj);
				tempmissobj->incrementWD();
				tempqueue.enqueue(tempmissobj);
			}
			while (tempqueue.dequeue(tempmissobj))
			{
				WaitingEmergencyMissions.insert(tempmissobj, tempmissobj->getSignificance()); //lesa nshouf significance wla 7aga tani
			}
			break;
		}
	}
	while (!WaitingPolarMissions.isEmpty())
	{
		Rovers<T>* temprover = new Rovers<T>;
		if (AvailablePolarRovers.dequeue(temprover))
		{
			WaitingPolarMissions.dequeue(tempmissobj);
			//Missions<T>* tempmissptr = new Missions<T>(tempmissobj);
			temprover->setMission(tempmissobj);
			temprover->incrementnumofmission();
			//temprover->setneedcheckcounter(missionsassigned);
			temprover->setExecDay();
			tempmissobj->setCD(tempmissobj->getWD() + tempmissobj->getFD() + tempmissobj->getED());
			InExcutionMissions.insert(tempmissobj, tempmissobj->getCD());
			InExcutionRovers.insert(temprover, tempmissobj->getCD());//msh 3arfeen el priority sa7 kda wala elmafrood 3l ED
		}
		else if (InmaintenanceRovers.dequeue(temprover))
		{
			if (temprover->getRoverType() == 'P')
			{
				WaitingEmergencyMissions.dequeue(tempmissobj);
				//Missions<T>* tempmissptr = new Missions<T>(tempmissobj);
				temprover->setMission(tempmissobj);
				temprover->SetSpeedtoHalf();
				temprover->incrementnumofmission();
				//temprover->setneedcheckcounter(missionsassigned);
				temprover->setExecDay();
				tempmissobj->setCD(tempmissobj->getWD() + tempmissobj->getFD() + tempmissobj->getED());
				InExcutionMissions.insert(tempmissobj, tempmissobj->getCD());//ed or cd????
				InExcutionRovers.insert(temprover, tempmissobj->getCD());
			}

		}

		else
		{
			Queue<Missions<T>*> tempqueue;
			while (!WaitingPolarMissions.isEmpty())
			{
				WaitingPolarMissions.dequeue(tempmissobj);
				tempmissobj->incrementWD();
				tempqueue.enqueue(tempmissobj);

			}
			while (tempqueue.dequeue(tempmissobj))
			{
				WaitingPolarMissions.enqueue(tempmissobj);
			}
			break;

		}

	}
	while (!InExcutionMissions.isEmpty())
	{
		//======================================================================================================//

		if (day == 23 || day==19 || day==67)//break days "all rovers should go back to station imidiatley !!! "
		{
			Rovers<T>* temprover = new Rovers<T>;
			InExcutionMissions.dequeue(tempmissobj);
			EventClass* TempEventpointer = new FormulationEvent<T>((day+1), tempmissobj->getMissionType(), tempmissobj->getTargetLocation(), tempmissobj->getSignificance(), tempmissobj->getMissionDuration(), tempmissobj->getmissionID(), this);
			ListOfEventPtrs.insert(TempEventpointer, day+1);
			InExcutionRovers.dequeue(temprover);
			if (temprover->getRoverType() == 'E')
			{
				UnderCheckEmergRovers.enqueue(temprover);
			}
			else
			{
				UnderCheckPolarRovers.enqueue(temprover);
			}
		}


		//=============================================================================================================//


		Rovers<T>* temprover = new Rovers<T>;
		InExcutionMissions.peek(tempmissobj);
		if (day == tempmissobj->getCD())
		{
			InExcutionMissions.dequeue(tempmissobj);
			CompletedMissions.enqueue(tempmissobj);
			InExcutionRovers.dequeue(temprover);
			Missions<T>* tempmissptr = new Missions<T>;
			tempmissptr = nullptr;
			temprover->setMission(tempmissptr);
			if (temprover->getneedcheckcount() == temprover->getnoofmissionsbeforecheck())
			{
				char typee;
				typee = temprover->getRoverType();
				if (typee == 'E')
				{
					UnderCheckEmergRovers.enqueue(temprover);
				}
				else if (typee == 'P')
				{
					UnderCheckPolarRovers.enqueue(temprover);
				}
			}
			else if ((tempmissobj->getTargetLocation()) >= 1000)//elrover tele3 mission atwal mn 1000km 
			{
				InmaintenanceRovers.enqueue(temprover);
			}

			else
			{
				char typee;
				typee = temprover->getRoverType();
				if (typee == 'E')
				{
					AvailableEmergRovers.enqueue(temprover);
				}
				else if (typee == 'P')
				{
					AvailablePolarRovers.enqueue(temprover);
				}
			}
		}
		else break; //????
	}
	/*Missions<T> miss;
	WaitingEmergencyMissions.peek(miss);
	cout<<miss.getmissionID()<<endl;
	InExcutionMissions.peek(miss);
	cout << miss.getmissionID()<<endl;
	*/

}
template<typename T>
inline Queue<T> MarsStation<T>::UIinteractivemode()
{
	Missions<T>* missobj = new Missions<T>;
	Rovers<T>* roversobj = new Rovers<T>;
	Queue<int> data;
	//counters---->
	int CounterCompletedMissions = 0;
	int CounterCheckEmergRovers = 0;
	int CounterUnderCheckPolarRovers = 0;
	int CounterAvailableEmergRovers = 0;
	int CounterAvailablePolarRovers = 0;
	int CounterInExcutionMissions = 0;
	int CounterInExcutionRovers = 0;
	int CounterWaitingEmergencyMissions = 0;
	int CounterWaitingPolarMissions = 0;
	int counteremergcompletedmiss = 0;
	int counterpolarcompletedmiss = 0;
	int counterinexcemergmiss = 0;
	int counterinexcpolarmiss = 0;

	Queue<Missions<T>*>* TempCompletedMissions = new Queue<Missions<T>*>(CompletedMissions);
	Queue<Rovers<T>*>* TempUnderCheckEmergRovers = new Queue<Rovers<T>*>(UnderCheckEmergRovers);
	Queue<Rovers<T>*>* TempUnderCheckPolarRovers = new Queue<Rovers<T>*>(UnderCheckPolarRovers);
	Queue<Rovers<T>*>* TempAvailableEmergRovers = new Queue<Rovers<T>*>(AvailableEmergRovers);
	Queue<Rovers<T>*>* TempAvailablePolarRovers = new Queue<Rovers<T>*>(AvailablePolarRovers);
	PriorityQueue<Missions<T>*>* TempInExcutionMissions = new PriorityQueue<Missions<T>*>(InExcutionMissions);
	PriorityQueue<Rovers<T>*>* TempInExcutionRovers = new PriorityQueue<Rovers<T>*>(InExcutionRovers);
	PriorityQueue<Missions<T>*>* TempWaitingEmergencyMissions = new PriorityQueue<Missions<T>*>(WaitingEmergencyMissions);
	Queue<Missions<T>*>* TempWaitingPolarMissions = new Queue<Missions<T>*>(WaitingPolarMissions);

	Queue<Missions<T>*>* CountingCompletedMissions = new Queue<Missions<T>*>(CompletedMissions);
	Queue<Rovers<T>*>* CountingCheckEmergRovers = new Queue<Rovers<T>*>(UnderCheckEmergRovers);
	Queue<Rovers<T>*>* CountingUnderCheckPolarRovers = new Queue<Rovers<T>*>(UnderCheckPolarRovers);
	Queue<Rovers<T>*>* CountingAvailableEmergRovers = new Queue<Rovers<T>*>(AvailableEmergRovers);
	Queue<Rovers<T>*>* CountingAvailablePolarRovers = new Queue<Rovers<T>*>(AvailablePolarRovers);
	PriorityQueue<Missions<T>*>* CountingInExcutionMissions = new PriorityQueue<Missions<T>*>(InExcutionMissions);
	PriorityQueue<Rovers<T>*>* CountingInExcutionRovers = new PriorityQueue<Rovers<T>*>(InExcutionRovers);
	PriorityQueue<Missions<T>*>* CountingWaitingEmergencyMissions = new PriorityQueue<Missions<T>*>(WaitingEmergencyMissions);
	Queue<Missions<T>*>* CountingWaitingPolarMissions = new Queue<Missions<T>*>(WaitingPolarMissions);


	data.enqueue(day);   //1

	while (CountingWaitingEmergencyMissions->dequeue(missobj))
	{
		CounterWaitingEmergencyMissions++;
	}
	while (CountingWaitingPolarMissions->dequeue(missobj))
	{
		CounterWaitingPolarMissions++;
	}
	data.enqueue(CounterWaitingEmergencyMissions + CounterWaitingPolarMissions);   //2
	data.enqueue(CounterWaitingEmergencyMissions); //3
	data.enqueue(CounterWaitingPolarMissions); //4
	while (TempWaitingEmergencyMissions->dequeue(missobj))
	{
		data.enqueue(missobj->getmissionID());  //Id's of waiting missions   //5

	}

	while (TempWaitingPolarMissions->dequeue(missobj))
	{
		data.enqueue(missobj->getmissionID());  //6
	}
	while (CountingInExcutionMissions->dequeue(missobj))
	{
		CounterInExcutionMissions++;
	}
	Queue<Rovers<T>*> TempInExcutionEmergencyRovers;
	Queue<Rovers<T>*> TempInExcutionPolarRovers;
	while (TempInExcutionRovers->dequeue(roversobj))
	{
		if (roversobj->getRoverType() == 'E')
		{
			TempInExcutionEmergencyRovers.enqueue(roversobj);
			counterinexcemergmiss++;
		}
		else
		{
			TempInExcutionPolarRovers.enqueue(roversobj);
			counterinexcpolarmiss++;
		}
	}
	data.enqueue(CounterInExcutionMissions); //7
	data.enqueue(counterinexcemergmiss); //8
	data.enqueue(counterinexcpolarmiss);//9
	while (TempInExcutionEmergencyRovers.dequeue(roversobj))
	{

		Missions<T>* misse = roversobj->getMission();
		data.enqueue(misse->getmissionID());  //10
		data.enqueue(roversobj->getID());     //11

	}
	while (TempInExcutionPolarRovers.dequeue(roversobj))
	{

		Missions<T>* misse = roversobj->getMission();
		data.enqueue(misse->getmissionID());  //12
		data.enqueue(roversobj->getID());     //13
	}
	while (CountingAvailableEmergRovers->dequeue(roversobj))
	{
		CounterAvailableEmergRovers++;
	}
	while (CountingAvailablePolarRovers->dequeue(roversobj))
	{
		CounterAvailablePolarRovers++;
	}
	data.enqueue(CounterAvailableEmergRovers + CounterAvailablePolarRovers); //14
	data.enqueue(CounterAvailableEmergRovers); //15
	data.enqueue(CounterAvailablePolarRovers); //16
	while (TempAvailableEmergRovers->dequeue(roversobj))
	{
		data.enqueue(roversobj->getID()); //17
	}
	while (TempAvailablePolarRovers->dequeue(roversobj))
	{
		data.enqueue(roversobj->getID()); //18
	}

	while (CountingCheckEmergRovers->dequeue(roversobj))
	{
		CounterCheckEmergRovers++;
	}
	while (CountingUnderCheckPolarRovers->dequeue(roversobj))
	{
		CounterUnderCheckPolarRovers++;
	}
	data.enqueue(CounterCheckEmergRovers + CounterUnderCheckPolarRovers); //19
	data.enqueue(CounterCheckEmergRovers);//20
	data.enqueue(CounterUnderCheckPolarRovers);//21
	while (TempUnderCheckEmergRovers->dequeue(roversobj))
	{
		data.enqueue(roversobj->getID()); //22
	}
	while (TempUnderCheckPolarRovers->dequeue(roversobj))
	{
		data.enqueue(roversobj->getID()); //23
	}
	//====================================================//
	Queue<Missions<T>*> TempCompletedEmergencyMissions;
	Queue<Missions<T>*> TempCompletedPolarMissions;

	while (CountingCompletedMissions->dequeue(missobj))
	{
		CounterCompletedMissions++;
	}
	data.enqueue(CounterCompletedMissions); //24
	while (TempCompletedMissions->dequeue(missobj))
	{
		if (missobj->getMissionType() == 'E')
		{
			TempCompletedEmergencyMissions.enqueue(missobj);
			counteremergcompletedmiss++;
		}
		else
		{
			TempCompletedPolarMissions.enqueue(missobj);
			counterpolarcompletedmiss++;
		}
	}
	data.enqueue(counteremergcompletedmiss);  //25
	data.enqueue(counterpolarcompletedmiss);   //26
	while (TempCompletedEmergencyMissions.dequeue(missobj))
	{
		data.enqueue(missobj->getmissionID()); //27
	}
	while (TempCompletedPolarMissions.dequeue(missobj))
	{
		data.enqueue(missobj->getmissionID()); //28
	}
	return data;
}


template <typename T>
void MarsStation<T>::OutputFile()
{
	ofstream Save;
	Save.open("OutputFile_1.txt");
	if (Save.fail())
	{
		cerr << "error opening file" << endl;
		exit(1);
	}
	Missions<T>* tempmissobj = new Missions<T>;
	Save << "CD  " << "ID  " << "FD  " << "WD  " << "ED  " << endl;
	while (CompletedMissions.dequeue(tempmissobj))
	{
		TotalNoOfMissions++;
		Save << tempmissobj->getCD() << "   " << tempmissobj->getmissionID() << "   " << tempmissobj->getFD() << "   " << tempmissobj->getWD() << "   " << tempmissobj->getED() << "   " << endl;
		totalwaitingdays = totalwaitingdays + tempmissobj->getWD();
		totalexcutiondays = totalexcutiondays + tempmissobj->getED();
		if (tempmissobj->getMissionType() == 'E')
		{
			totalemgmiss++;
		}
		else if (tempmissobj->getMissionType() == 'P')
		{
			totalpolmiss++;
		}
	}
	while (WaitingPolarMissions.dequeue(tempmissobj))
	{
		totalwaitingdays = totalwaitingdays + tempmissobj->getWD();
	}
	Save << "Missions: " << TotalNoOfMissions << "[P: " << totalpolmiss << ",E: " << totalemgmiss << "]" << endl;
	Save << "Rovers: " << (numberofemergencyrovers + numberofpolarrovers) << "[P: " << numberofpolarrovers << ",E: " << numberofemergencyrovers << "]" << endl;
	Save << "AVG wait = " << (totalwaitingdays / TotalNoOfMissions) << ", AVG exc = " << (totalexcutiondays / TotalNoOfMissions) << endl;
	Save.close();
}


template<typename T>
inline void MarsStation<T>::setDay(int d)
{
	day = d;
}

template<typename T>
inline void MarsStation<T>::UIinterface()
{
	UI<T> UIobj(interfacemode, this);
	UIobj.Interfacefunction();
}




template<typename T>
inline bool MarsStation<T>::checkifcompleted()
{
	if (AvailableEmergRovers.isEmpty() && AvailablePolarRovers.isEmpty() && InExcutionRovers.isEmpty() && UnderCheckEmergRovers.isEmpty() && UnderCheckPolarRovers.isEmpty() && InmaintenanceRovers.isEmpty())
		return true;

	if (WaitingEmergencyMissions.isEmpty() && WaitingPolarMissions.isEmpty() && InExcutionMissions.isEmpty() && ListOfEventPtrs.isEmpty() && UnderCheckEmergRovers.isEmpty() && UnderCheckPolarRovers.isEmpty() && InmaintenanceRovers.isEmpty())
		return true;

	if (!(WaitingPolarMissions.isEmpty()) && InExcutionRovers.isEmpty() && UnderCheckEmergRovers.isEmpty() && UnderCheckPolarRovers.isEmpty()  && InExcutionMissions.isEmpty() && ListOfEventPtrs.isEmpty() &&  AvailablePolarRovers.isEmpty() && InmaintenanceRovers.isEmpty())
		return true;

		return false;
}

template<typename T>
inline int MarsStation<T>::Getday()
{
	return day;
}



template <typename T>
MarsStation<T>::~MarsStation()
{

}


