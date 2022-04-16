#pragma once
#include "Missions.h"

//template <typename T>
class EventClass
{
private:
	int eventday;
	int missionID;
	//Missions mission;
public:
	EventClass(); //lessa m3mlnhash
	virtual void Execute() = 0;
	virtual int getfd() = 0;
	void setID(int idd);
	void seteventday(int ed);
	int getmissionid();
	int geteventday();
	~EventClass();
};


EventClass::EventClass()
{
	eventday = 0;
	missionID = 0;
}

inline void EventClass::setID(int idd)
{
	missionID = idd;
}


inline void EventClass::seteventday(int ed)
{
	eventday = ed;
}

inline int EventClass::getmissionid()
{
	return missionID;
}


inline int EventClass::geteventday()
{
	return eventday;
}

EventClass::~EventClass()
{
}

