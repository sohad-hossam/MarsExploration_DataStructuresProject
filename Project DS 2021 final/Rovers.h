#pragma once
#pragma once
#include <iostream>
#include "Missions.h"
using namespace std;

template <typename T>
class Missions;
template <typename T>
class Rovers
{
	char RoverType;
	int ChD; //Checkup duration
	int Speed;
	int numofmissionsbcheckup;
	int needcheckcounter;//for mission         hn3mlha if condition fl 7eta eli been rego3o mn list of inexcutionrovers to list of avilable rovers
	bool busy;
	int roverID;
	int checkupcounter;//for days of rovers
	//int ED; //excutionday = 2(trip)+mission duration
	Missions<T>* missionptr;
	int daysspentinmaintenance = 0; //each rover needs 2 days in maintenance


public:
	Rovers();
	Rovers(char type, int duration, int speed, int n, int ID);
	void setRoverType(char type);
	void setCheckupDuration(int duration);
	void setSpeed(int speed);
	void setMission(Missions<T>*& m);
	void setnumofmissionsbcheckup(int n);
	void setExecDay();
	void setneedcheckcounter(int cc);
	char getRoverType();
	int getCheckupDuration();
	int getSpeed();
	Missions<T>* getMission();
	//void makebusy();
	//bool IsAssigned();
	//int getExecDay();
	int getneedcheckcount();//passed taken in missions
	int getnoofmissionsbeforecheck();//elrakam eli hwa medehole
	int getcheckupcounter();
	void incrementcheckupcounter();
	bool Ischeckedup();
	int getID();
	void SetSpeedtoHalf();
	void incrementnumofmission();
	void incrementmaintainancecounter();
	void resetnumofmissions();
	bool Ismaintened();

	~Rovers();
};


template<typename T>
inline Rovers<T>::Rovers()
{
}

template <typename T>
Rovers<T>::Rovers(char type, int duration, int speed, int n, int ID)
{
	busy = 0;
	RoverType = type;
	ChD = duration;
	Speed = speed;
	numofmissionsbcheckup = n;
	missionptr = nullptr;
	checkupcounter = 0;
	roverID = ID;
}
template <typename T>
void Rovers<T>::setRoverType(char type)
{
	RoverType = type;
}
template <typename T>
void  Rovers<T>::setCheckupDuration(int duration)
{
	ChD = duration;
}
template <typename T>
void  Rovers<T>::setSpeed(int speed)
{
	Speed = speed;
}
template <typename T>
char  Rovers<T>::getRoverType()
{
	return RoverType;
}
template <typename T>
int  Rovers<T>::getCheckupDuration()
{
	return ChD;
}
template <typename T>
int  Rovers<T>::getSpeed()
{
	return Speed;
}
template <typename T>
void Rovers<T>::setMission(Missions<T>*& m)
{
	missionptr = m;
}
template<typename T>
void Rovers<T>::setnumofmissionsbcheckup(int n)
{
	numofmissionsbcheckup = n;
}
template<typename T>
inline void Rovers<T>::setExecDay()
{
	missionptr->setED(2 * (((missionptr->getTargetLocation()) / Speed) / 25) + missionptr->getMissionDuration());
}

template<typename T>
inline void Rovers<T>::setneedcheckcounter(int cc)
{
	needcheckcounter = cc;
}
template <typename T>
Missions<T>* Rovers<T>::getMission()
{
	return missionptr;
}
/*
template<typename T>
void Rovers<T>::makebusy()
{
	busy = true;
}

template<typename T>
bool Rovers<T>::IsAssigned()
{
	return busy;
}
*/

template<typename T>
inline int Rovers<T>::getneedcheckcount()
{
	return needcheckcounter;
}

template<typename T>
inline int Rovers<T>::getnoofmissionsbeforecheck()
{
	return numofmissionsbcheckup;
}

template<typename T>
inline int Rovers<T>::getcheckupcounter()
{
	return checkupcounter;
}

template<typename T>
inline void Rovers<T>::incrementcheckupcounter()
{
	checkupcounter++;
}

template<typename T>
inline bool Rovers<T>::Ischeckedup()
{
	if (checkupcounter == ChD)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
inline int Rovers<T>::getID()
{
	return roverID;
}

//==================================================//
template<typename T>
inline void Rovers<T>::SetSpeedtoHalf()
{
	Speed = Speed / 2;
}

template<typename T>
inline void Rovers<T>::incrementnumofmission()
{
	needcheckcounter++;
}

template<typename T>
inline void Rovers<T>::incrementmaintainancecounter()
{
	daysspentinmaintenance++;
}

template<typename T>
inline void Rovers<T>::resetnumofmissions()
{
	needcheckcounter = 0;
}

template<typename T>
inline bool Rovers<T>::Ismaintened()
{
	if (daysspentinmaintenance == 2)
	{
		return true;
	}
}

//===========================================//


template <typename T>
Rovers<T>::~Rovers()
{

}


