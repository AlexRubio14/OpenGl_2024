#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class ShaderProgram {
private:

public:

	GLuint vertexShader;
	GLuint geometryShader;
	GLuint fragmentShader;

	ShaderProgram()
	{
		vertexShader = 0;
		geometryShader = 0;
		fragmentShader = 0;
	};


	//Funcion que devolvera una string con todo el archivo leido
	std::string Load_File(const std::string& filePath);

	GLuint LoadFragmentShader(const std::string& filePath);

	GLuint LoadGeometryShader(const std::string& filePath);

	GLuint LoadVertexShader(const std::string& filePath);

	//Función que dado un struct que contiene los shaders de un programa generara el programa entero de la GPU
	GLuint CreateProgram(const ShaderProgram& shaders);
};