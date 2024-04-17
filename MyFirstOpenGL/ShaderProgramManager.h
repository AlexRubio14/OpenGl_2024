#pragma once
#include "ShaderProgram.h"

#define SHADERPROGRAM_MANAGER ShaderProgramManager::Instance()

class ShaderProgramManager {
private:

	ShaderProgramManager();

	ShaderProgramManager(const ShaderProgramManager&) = delete;
	ShaderProgramManager& operator =(const ShaderProgramManager&) = delete;

public:

	inline static ShaderProgramManager& Instance()
	{
		static ShaderProgramManager shaderProgramManager;
		return shaderProgramManager;
	}

	std::vector<GLuint> compiledPrograms;

	void DeletePrograms();
};