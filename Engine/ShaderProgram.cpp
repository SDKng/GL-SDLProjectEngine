#include "ShaderProgram.h"
#include <GL\glew.h>
#include <iostream>

namespace engine {

	ShaderProgram::ShaderProgram(const std::string &vertexSource, const std::string &fragmentSource) :
		m_vertexSource(vertexSource), m_fragmentSource(fragmentSource)
	{
	
		

	}
	
	ShaderProgram::~ShaderProgram() {
	
	

	}

	bool ShaderProgram::Init() {

		//compile vertex shaders
		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexShaderSource = m_vertexSource.c_str();
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		// errors?
		int success;
		char infolog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {

			glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
			std::cout << "Error compiling vertex shader: " << infolog << std::endl;
		
			return false;
		}

		//compile fragment shaders
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragmentShaderSource = m_fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		// errors?
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {

			glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
			std::cout << "Error compiling fragment shader: " << infolog << std::endl;
		
			return false;
		}


		// PROGRAM - links the shaders
		m_id = glCreateProgram();
		// attaching the shaders
		glAttachShader(m_id, vertexShader);
		glAttachShader(m_id, fragmentShader);
		glLinkProgram(m_id);
		//errors?
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (!success) {

			glGetProgramInfoLog(m_id, 512, NULL, infolog);
			std::cout << "Error linking shader program: " << infolog << std::endl;
	
			return false;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return true;
	}
	
	bool ShaderProgram::Shutdown() {

		return true;
	}
	
	
	
	void ShaderProgram::Use() {

		glUseProgram(m_id);

	}
}
