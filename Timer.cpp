#include"Timer.h"
#include<cstdio>

Timer::Timer() { reset(); }

long Timer::time_passed_milli()
{
	return (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _start)).count();
}
void Timer::reset()
{
	_start = std::chrono::system_clock::now();
}
void Timer::start()
{
	_start = std::chrono::system_clock::now();
}

#if 0
int main(int argc, char* argv[])
{
	Timer timer;
	int send_time = 0;
	int timer_adjust_piece = 0;
	timer.start();
	LOG("timer test begin ...\n");
	int millisec_passed;
	while (true)
	{
		millisec_passed = timer.time_passed_milli();
		if (millisec_passed < 1000 - timer_adjust_piece && send_time < SEND_FREQ_MAX)
		{
			++send_time;
		}
		else if (millisec_passed >= 1000 - timer_adjust_piece)
		{
			printf("send frequency: %d hz\n", send_time);
			timer.reset();
			send_time = 0;
			timer_adjust_piece = millisec_passed - 1000 + timer_adjust_piece;
		}
	}
	return 1;
}
#endif