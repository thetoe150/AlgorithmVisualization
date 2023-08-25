#include <Timer.hpp>
#include <chrono>
#include <ratio>

// HACK: easyto gef
// ISSUE: drfgdgsg 

using Clock = std::chrono::system_clock;
using namespace std::chrono;

Timer::Timer(std::string msg) : msg(msg)
{
	std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();
	this->m_begin = t1;
}

// TODO: need refector
Timer::~Timer()
{
    const auto t2 = std::chrono::system_clock::now();
	const auto micro_duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - this->m_begin);
	const std::chrono::duration<double, std::milli> duration = micro_duration;
	std::cout << msg << "\n - excute time: " << duration.count() << " ms" << std::endl;
}
// PERF: faster
