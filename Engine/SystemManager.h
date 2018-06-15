#pragma once
#include "Singleton.h"
#include <vector>
#include <algorithm>
#include "Window.h"
#include "Graphics.h"

namespace engine {



	class SystemManager : public Singleton<SystemManager> {


		friend Singleton;

		std::vector<class System*> m_systems;

	protected:

		SystemManager();
	public:

		~SystemManager();

		bool init();
		void Update();
		void Draw() const;
		bool Shutdown();



		template<class T>
		T* GetSystem() const {

			//System* s = std::find_first_of(m_systems.begin(), m_systems.end(), [T](System * s) -> bool) {

			//	return dynamic_cast<T>(s) != nullptr;
			//};


			for (System* s : m_systems)
			{
				T* currentSystem = dynamic_cast<T*>(s);
				if (currentSystem)
					return currentSystem;
			}

			return nullptr;
		}

		inline const std::vector<class System*>& GetSystems() const
		{
			return m_systems;
		}
	};
}
	