#pragma once

#include <chrono>

using namespace std::chrono;

class Time{

public:
	Time();
	~Time();

	//assigns a time point value to StartTime
	void Start();

	//retrieves the duration between the time that this function is called and StartTime
	float GetTimeSinceStart();

private:
	//time point that gets assigned when Start() executes
	steady_clock::time_point StartTime; 
};