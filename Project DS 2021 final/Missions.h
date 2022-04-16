#pragma once
#include <iostream>
#include "PriorityQueue.h"
#include "Queue.h"
using namespace std;
template<typename T>
class Missions
{
	int FD; //formulation day
	char MissionType;
	int missionID; //lessa msh 3rfeen ynf3 n7otaha wala l2
	int TargetLoc; //target location
	int MissionDuration;
	int Significance;
	int WD; //waitingdays till the mission gets assigned to a rover
	int CD; //complition day 
	int ED; //execution day = 2(trip)+mission duration

	//lesa nshouf assign criteria felmain wala class
	//PriorityQueue<Missions> EmergencyMissions;
	//Queue<Missions> PolarMissions;
public:


	Missions();
	Missions(const Missions<T>& m);
	Missions(int fd, char missiontype, int targetLoc, int significance, int missionduration, int ID);
	void setFD(int fd);
	void setMissionType(char missiontype);
	void setTargetLocation(int targetLoc);
	void setSignificance(int significance);
	void setMissionDuration(int missionduration);
	void setmissionID(int ID);
	void setWD(int wd);
	void setCD(int cd);
	void setED(int ed);
	char getMissionType();
	int getTargetLocation();
	int getSignificance();
	int getFD();
	int getCD();
	int getED();
	int getWD();
	int getmissionID();
	int getMissionDuration();
	void incrementWD();
	float getPriorityeq();

	~Missions();
};



template<typename T>
Missions<T>::Missions()
{
}
template<typename T>
inline Missions<T>::Missions(const Missions<T>& m)
{
	FD = m.FD;
	MissionType = m.MissionType;
	missionID = m.missionID; //lessa msh 3rfeen ynf3 n7otaha wala l2
	TargetLoc = m.TargetLoc; //target location
	MissionDuration = m.MissionDuration;
	Significance = m.Significance;
	WD = m.WD; //waitingdays till the mission gets assigned to a rover
	CD = m.CD;
	ED = m.ED;

}
template<typename T>
Missions<T>::Missions(int fd, char missiontype, int targetLoc, int significance, int missionduration, int ID)
{
	FD = fd;
	MissionType = missiontype;
	missionID = ID;
	TargetLoc = targetLoc; //target location
	MissionDuration = missionduration;
	Significance = significance;
	WD = 0;//intially
}
//can need another constructor
/*Missions::Missions()
{

}
*/
template<typename T>
void Missions<T>::setFD(int fd)
{
	FD = fd;
}
template<typename T>
void Missions<T>::setMissionType(char missiontype)
{
	MissionType = missiontype;
}
template<typename T>
void Missions<T>::setTargetLocation(int targetloc)
{
	TargetLoc = targetloc;
}
template<typename T>
void Missions<T>::setSignificance(int significance)
{
	Significance = significance;
}
template<typename T>
void Missions<T>::setMissionDuration(int missionduration)
{
	MissionDuration = missionduration;
}
template<typename T>
void Missions<T>::setmissionID(int ID)
{
	missionID = ID;
}
template<typename T>
inline void Missions<T>::setWD(int wd)
{
	WD = wd;
}
template<typename T>
inline void Missions<T>::setCD(int cd)
{
	CD = cd;
}
template<typename T>
inline int Missions<T>::getWD()
{
	return WD;
}
template<typename T>
inline void Missions<T>::setED(int ed)
{
	ED = ed;
}
template<typename T>
char Missions<T>::getMissionType()
{
	return MissionType;
}
template<typename T>
int Missions<T>::getTargetLocation()
{
	return TargetLoc;
}
template<typename T>
int Missions<T>::getSignificance()
{
	return Significance;
}
template<typename T>
inline int Missions<T>::getFD()
{
	return FD;
}
template<typename T>
inline int Missions<T>::getCD()
{
	return CD;
}
template<typename T>
inline int Missions<T>::getED()
{
	return ED;
}
template<typename T>
inline int Missions<T>::getmissionID()
{
	return missionID
		;
}
template<typename T>
inline int Missions<T>::getMissionDuration()
{
	return MissionDuration;
}
template<typename T>
inline void Missions<T>::incrementWD()
{
	WD++;
}
template<typename T>
inline float Missions<T>::getPriorityeq()
{
	return (TargetLoc * MissionDuration) / (FD * Significance);
}
template<typename T>
Missions<T>::~Missions()
{

}
