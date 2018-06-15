#pragma once

#include <chrono>
#include <vector>
#include <iostream>
#include <string>

namespace engine {

	class Clock {

		bool timerIsRunning;
		static std::chrono::high_resolution_clock timer;
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;
		std::string currentTask;


	public:

		void StartTimer(std::string task);
		void EndTimer();

	};
}