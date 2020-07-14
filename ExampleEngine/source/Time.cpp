#include "Time.h"

Time::Time()
{
	
}

Time::~Time()
{

}

void Time::Start()
{
	StartTime = steady_clock::now();
}

float Time::GetTimeSinceStart()
{
	//gets the duration in seconds
	return duration<float>(steady_clock::now() - StartTime).count();
}
