#include "Window.h"
#include "SDL/SDL.h"
#include "Logger.h"
#include "SystemManager.h"
#include <GL\glew.h>

namespace engine {

	Window::Window() :
		System(ESystemType::ST_WINDOW) {}
		Window::~Window(){}


		bool Window::Init() {

			
			InitSDL();
			
			m_window = SDL_CreateWindow("Engine Window", 100, 100, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

			if (!m_window) {

				Logger::Log("Failed To Init Window", ELogTypes::LT_Error); 
				return false;
			}
			
			SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
			
			// create double buffer
			// draw things on back buffer to the screen
			// screen buffer that was on the screen becomes the back buffer
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			
			


			return true;
		}
		void Window::Update() {

			SDL_GL_SwapWindow(m_window);

		}
		void Window::Draw() const {


		}
		bool Window::Shutdown() {
			
			return ShutdownSDL();
		}
		bool Window::InitSDL() {

			if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {

				Logger::Log("Failed To Init SDL", ELogTypes::LT_Error);
				return false;
			}

			//disable vsync
			//SDL_GL_SetSwapInterval(0);

			return true;
		}

		bool Window::ShutdownSDL() {

;
			
			SDL_FreeSurface(m_screenSurface);
			m_screenSurface = nullptr;

			SDL_DestroyWindow(m_window);
			m_window = nullptr;
			
			SDL_Quit();
			Logger::Log("Closed SDL");
			return true;
		}
}