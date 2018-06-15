#pragma once

#include "Resource.h"
#include <string>


namespace engine {

	class ShaderProgram : public Resource {

	private:

		int m_id;

		std::string m_vertexSource;
		std::string m_fragmentSource;

	public:

		ShaderProgram(const std::string& vertexSource, const std::string &fragmentSource);
		~ShaderProgram();

		bool Init() override;

		bool Shutdown() override;

		void Use();
	};
}