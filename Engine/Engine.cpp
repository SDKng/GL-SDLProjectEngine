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
#include "stbimage\stb_image.h"
#include "..\Engine\stbimage\Texture.h"

#include <chrono>
#include <Windows.h>
#include <vector>

namespace engine {

	// SHADERS LETS GO
	const char* vertexShaderSource =

		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos; \n"
		"layout (location = 1) in vec3 aColor; \n"
		"layout (location = 2) in vec2 aTexCoord; \n"
		"uniform mat4 transform; \n"
		"out vec3 ourColor; \n"
		"out vec2 TexCoord; \n"
		"void main() \n"
		"{ \n"
		"	gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f); \n"
		"	ourColor = aColor; \n"
		"	TexCoord = aTexCoord; \n"
		"}\0";

	const char* fragmentShaderSource =
		"#version 330 core\n"
		"in vec2 TexCoord; \n"
		"in vec3 ourColor; \n"
		"out vec4 FragColor; \n"
		"uniform sampler2D texture1; \n"
		"void main() {\n"
		"	FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0); \n"
		"}\0";


	float vertices[] = {

		//pos					colours					uvs
		0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,		0.0f, 0.5f, 0.0f,		1.0f, 0.0f,
	   -0.5f, -0.5f, 0.0f,		0.4f, 0.0f, 0.6f,		0.0f, 1.0f,
	   -0.5f, 0.5f, 0.0f,		0.0f, 0.2f, 0.2f,		1.0f, 1.0f
	};

	unsigned indices[] = {

		0, 1, 3,
		1, 2, 3
	};

	//float texCoords[] = {

	//	0.0f, 0.0f, //lower left
	//	1.0f, 1.0f, //lower right
	//	0.0f, 1.0f, //top left
	//	1.0f, 1.0f  //top right
	//};

	MeshData md (std::vector<float>(vertices, vertices + sizeof (vertices) / sizeof (vertices[0])),
		std::vector<int>(indices, indices + sizeof(indices) / sizeof(indices[0])));

	ShaderProgram sp(vertexShaderSource, fragmentShaderSource);

	Texture tex("trump.jpg");

	MeshComponent mc(&md, &sp, &tex);

	GameObject go;

	int width, height, nrChannels;
	unsigned char* data = stbi_load("trump.jpg", &width, &height, &nrChannels, 0);

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
			tex.Init();

			go.AddConponent(&mc);
		
			return 2;
		}
		return 0;
	}
	
	//main loop
	void Engine::Run() {
		
		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);

		while (!SystemManager::GetInstance().GetSystem<InputSystem>()->WasCloseRequested()) {

			
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

			
			SystemManager::GetInstance().Update();
			go.Update();
			
			SystemManager::GetInstance().Draw();
			go.Draw();

			InputSystem* input = SystemManager::GetInstance().GetSystem<InputSystem>();
		
			if (input->WasKeyPressed(SDLK_SPACE)) {

				std::cout << "Pressing Space" << std::endl;
			}
			
			if (input->IsKey(SDLK_w)) {

				go.Translate(0.0f, 0.0005f, 0.0f);
			}
			if (input->IsKey(SDLK_s)) {

				go.Translate(0.0f, -0.0005f, 0.0f);
			}
			if (input->IsKey(SDLK_a)) {

				go.Translate(-0.0005f, 0.0f, 0.0f);
			}
			if (input->IsKey(SDLK_d)) {

				go.Translate(0.0005f, 0.0f, 0.0f);
			}
		}
	}
}	