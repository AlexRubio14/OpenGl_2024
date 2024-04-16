#include "ShaderProgramManager.h"

ShaderProgramManager::ShaderProgramManager()
{
		// CUBE PROGRAM
		ShaderProgram shaderProgramCube;

		shaderProgramCube.LoadVertexShader("VS_Cubes.glsl");
		shaderProgramCube.LoadFragmentShader("FS_YellowOrange.glsl");
		compiledPrograms.push_back(shaderProgramCube.CreateProgram(shaderProgramCube));

		// ORTHOHEDRON PROGRAM

		ShaderProgram shaderProgramOrthohedron;

		shaderProgramOrthohedron.LoadVertexShader("VS_Cubes.glsl");
		shaderProgramOrthohedron.LoadFragmentShader("FS_YellowOrange.glsl");
		compiledPrograms.push_back(shaderProgramOrthohedron.CreateProgram(shaderProgramOrthohedron));


		// PYRAMID PROGRAM
		ShaderProgram shaderProgramPyramid;

		shaderProgramPyramid.LoadVertexShader("VS_Pyramid.glsl");
		shaderProgramPyramid.LoadFragmentShader("FS_Semaphore.glsl");
		compiledPrograms.push_back(shaderProgramPyramid.CreateProgram(shaderProgramPyramid));
}

void ShaderProgramManager::DeletePrograms()
{
	for (int i = 0; i < compiledPrograms.size(); i++) {
		
		glDeleteProgram(compiledPrograms[i]);
	}
}
