#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#define SHADER_PROGRAM ShaderProgram::Instance()

class ShaderProgram {
private:

	ShaderProgram() = default;

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator =(const ShaderProgram&) = delete;

public:

	std::vector<GLuint> compiledPrograms;

	GLuint vertexShader;
	GLuint geometryShader;
	GLuint fragmentShader;

	inline static ShaderProgram& Instance()
	{
		static ShaderProgram shaderProgram;
		return shaderProgram;
	}

	//Funcion que devolvera una string con todo el archivo leido
	std::string Load_File(const std::string& filePath);

	GLuint LoadFragmentShader(const std::string& filePath);

	GLuint LoadGeometryShader(const std::string& filePath);

	GLuint LoadVertexShader(const std::string& filePath);

	//Función que dado un struct que contiene los shaders de un programa generara el programa entero de la GPU
	GLuint CreateProgram(const ShaderProgram& shaders);
};