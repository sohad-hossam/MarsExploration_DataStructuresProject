#pragma once
#include "MarsStation.h"
template <typename T>
class MarsStation;
template <typename T>
class FormulationEvent :public EventClass
{
	MarsStation<T>* marsptr;
	char Miissiontype;
	int TargetLoc;
	int Significance;
	int Missionduration;


public:
	FormulationEvent(int fd, char missiontype, int targetLoc, int significance, int missionduration, int ID,
		MarsStation<T>* ptr);
	FormulationEvent();
	int getfd();
	void Execute();
	~FormulationEvent();
};


template <typename T>
FormulationEvent<T>::FormulationEvent(int fd, char missiontype, int targetLoc, int significance, int missionduration, int ID,
	MarsStation<T>* ptr)
{
	setID(ID);
	seteventday(fd);
	//eventday =fd;
	//missionID = ID;
	Miissiontype = missiontype;
	TargetLoc = targetLoc;
	Significance = significance;
	Missionduration = missionduration;
	marsptr = ptr;
}
template<typename T>
FormulationEvent<T>::FormulationEvent()
{
}
template<typename T>
int FormulationEvent<T>::getfd()
{
	return geteventday();
}
template <typename T>
void FormulationEvent<T>::Execute()
{
	Missions<T>* missions = new Missions<T>(getfd(), Miissiontype, TargetLoc, Significance, Missionduration, getmissionid());

	if (missions->getMissionType() == 'E')
	{
		marsptr->addtoemergencymiss(missions, missions->getPriorityeq());
	}
	else if (missions->getMissionType() == 'P')
	{
		marsptr->addtopolarmiss(missions);
	}
}
template <typename T>
FormulationEvent<T>::~FormulationEvent()
{

}

