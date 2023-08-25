#pragma once

#include <iostream>
#include <chrono>
#include <string>


class Timer
{
public:
	Timer(std::string);
	~Timer();
	std::string msg;
	std::chrono::time_point<std::chrono::system_clock> m_begin;
};
