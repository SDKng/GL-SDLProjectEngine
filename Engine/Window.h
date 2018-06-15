#pragma once
#include "System.h"


struct SDL_Window;
struct SDL_Surface;

namespace engine {

	class Window : public System {

	public:

		SDL_Window* m_window;
		SDL_Surface* m_screenSurface;

		Window();
		~Window();

		bool Init() override;
		void Update() override;
		void Draw() const override;
		bool Shutdown() override;

	private:

		bool InitSDL();
		bool ShutdownSDL();


	};
}

