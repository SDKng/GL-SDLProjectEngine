#pragma once

#include "Clock.h"

namespace engine {

	void Clock::StartTimer(std::string taskName) {
		
		if (!timerIsRunning) {

			startTime = timer.now();
			timerIsRunning = true;
			currentTask = taskName;
		}
		else { std::cout << "The timer for " << taskName << " is already running!" << std::endl; };
	}

	void Clock::EndTimer() {

		if (timerIsRunning) {
			
			/*endTime = timer.now();
			auto taskTime = endTime - startTime;
			std::cout << "Task: " << currentTask << " Took: " << taskTime(sec).count() << */
		};
	};
};
