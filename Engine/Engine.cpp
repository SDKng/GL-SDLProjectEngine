#include "Engine.h"
#include "Logger.h"
#include <iostream>
#include <SDL\SDL.h>
#include <GL\glew.h>
#include "EngineTypes.h"
#include "SystemManager.h"
#include "Window.h"
#include "ShaderProgram.h"
#include "GameObject.h"
#include "MeshData.h"
#include "MeshComponent.h"

#include <chrono>
#include <Windows.h>
#include <vector>

namespace engine {

	// SHADERS LETS GO
	const char* vertexShaderSource =

		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos; \n"
		""
		"void main() \n"
		"{ \n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f); \n"
		"}\0";

	const char* fragmentShaderSource =

		"#version 330 core\n"
		"out vec4 FragColor; \n"
		""
		"void main() {\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.0f, 1.0);"
		"}\0";


	float vertices[] = {

		0.5f, 0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	unsigned indices[] = {

		0, 1, 3,
		1, 2, 3
	};

	MeshData md (std::vector<float>(vertices, vertices + sizeof (vertices) / sizeof (vertices[0])),
		std::vector<int>(indices, indices + sizeof(indices) / sizeof(indices[0])));

	ShaderProgram sp(vertexShaderSource, fragmentShaderSource);

	MeshComponent mc(&md, &sp);

	GameObject go;

	Engine::~Engine() {

		SystemManager::GetInstance().Shutdown();
	}

	int Engine::Init()
	{
		Logger::Log("Engine Initializing...");

		if (SystemManager::GetInstance().init()) {
		
			md.Init();
			sp.Init();

			mc.Init();

			go.AddConponent(&mc);
		
			return 2;
		}
		return 0;
	}
	
	//main loop
	void Engine::Run() {

		bool quit = false;
		SDL_Event e;
		
		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);

		while (!quit) {

			
			//FPS COUNTER
			static uint64_t frameCounter = 0;
			static double elapsedSeconds = 0.0;
			static std::chrono::high_resolution_clock clock;
			static auto t0 = clock.now();

			++frameCounter;
			auto t1 = clock.now();
			auto deltaTime = t1 - t0;
			t0 = t1;

			elapsedSeconds += deltaTime.count() * 1e-9;
			if (elapsedSeconds > 1.0f) {

				char buffer[500];
				auto fps = frameCounter / elapsedSeconds;
				sprintf_s(buffer, 500, "FPS: %f\n", fps);

				std::cout << buffer << std::endl;
				frameCounter = 0;
				elapsedSeconds = 0.0;
			
			}
			//FPS COUNTER END

			while (SDL_PollEvent(&e) != 0) {

				switch (e.type) {

				case SDL_QUIT: 
					quit = true;
					break;
				
				default:
					break;

				}
			}
			SystemManager::GetInstance().Update();
			go.Update();
			
			SystemManager::GetInstance().Draw();
			go.Draw();


			// remove this
			//glEnableClientState(GL_COLOR_ARRAY);
			//glBegin(GL_QUADS);
			//glColor3f(1.0f, 0.0f, 1.0f);
			//glVertex2f(0, 0);
			//glVertex2f(0, 1);
			//glVertex2f(1, 1);
			//glVertex2f(1, 0);
			//glEnd();
		}
	}
}	