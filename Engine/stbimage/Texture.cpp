#include "Texture.h"
#include "..\Logger.h"

#include <GL\glew.h>
#include <iostream>

#include "stb_image.h"



namespace engine {

	Texture::Texture(const std::string& texturePath) :
		path(texturePath)
	{

		glGenTextures(1, &m_id);

		
	}
	Texture::~Texture() {


	}

	bool Texture::Init() {

		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);

		if (data) {

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {

			Logger::Log("Error Loading Texture", ELogTypes::LT_Error);
		}

		free(data);
		
		glGenerateMipmap(GL_TEXTURE_2D);
		return true;
	}

	bool Texture::Shutdown() {

		return true;
	}

	void Texture::Use() {

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

}