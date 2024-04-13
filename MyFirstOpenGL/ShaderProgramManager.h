#pragma once
#include "ShaderProgram.h"

#define SHADERPROGRAM_MANAGER ShaderProgramManager::Instance()

class ShaderProgramManager {
private:

	ShaderProgramManager()
	{
		// CUBE & ORTHOHEDRON COMPILAR SHADERS & PROGRAM
		ShaderProgram shaderProgramCube; 

		shaderProgramCube.LoadVertexShader("VS_Transform.glsl");
		shaderProgramCube.LoadFragmentShader("FS_YellowOrange.glsl");
		compiledPrograms.push_back(shaderProgramCube.CreateProgram(shaderProgramCube));




		// PYRAMID COMPILAR SHADERS & PROGRAM
		ShaderProgram shaderProgramPyramid;

		shaderProgramPyramid.LoadVertexShader("VS_Transform.glsl");
		shaderProgramPyramid.LoadFragmentShader("FS_Semaphore.glsl");
		compiledPrograms.push_back(shaderProgramPyramid.CreateProgram(shaderProgramPyramid));
	}

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