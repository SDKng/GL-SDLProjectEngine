#pragma once

#ifndef _LOGGER_H
#define _LOGGER_H
#include "Singleton.h"
#include "EngineTypes.h"

namespace engine {

	class Logger : public Singleton<Logger> {

	private:
		
		ELogTypes m_currentLevel;
		
		
		friend Singleton;
	protected:
		
		Logger() : m_currentLevel(ELogTypes::LT_Everything)  {}

	public:

		static void Log (const char* message, ELogTypes l = ELogTypes::LT_Everything);
		static ELogTypes GetCurrentLogLevel();
		static void SetCurrentLogLevel(ELogTypes l);
	};

}
#endif //! _LOGGER_H