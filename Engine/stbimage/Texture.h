#pragma once

#include "../Resource.h"
#include <string>


namespace engine {

	class Texture : public Resource {

	private:

		unsigned int m_id;

		int m_width, m_height, m_channels;

		std::string path;

	public:

		Texture(const std::string& texturePath);
		~Texture();

		bool Init() override;

		bool Shutdown() override;

		void Use();

		inline unsigned int GetID() const { return m_id; }
	};
}