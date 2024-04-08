#include "GLManager.h"

void GLManager::InitializeVaoAndVbo(GLuint& vao, GLuint& vbo, int numVaos, int numVbos)
{

	//Definimos cantidad de vao a crear y donde almacenarlos 
	glGenVertexArrays(numVaos, &vao);

	//Indico que el VAO activo de la GPU es el que acabo de crear
	glBindVertexArray(vao);

	//Definimos cantidad de vbo a crear y donde almacenarlos
	glGenBuffers(numVbos, &vbo);

	//Indico que el VBO activo es el que acabo de crear y que almacenará un array. Todos los VBO que genere se asignaran al último VAO que he hecho glBindVertexArray
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void GLManager::VboConfiguration(GameObject* gameObject, int numVbo, int dimensions)
{
	//Ponemos los valores en el VBO creado
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * gameObject->GetVertexs().size(), gameObject->GetVertexs().data(), GL_STATIC_DRAW);

	//Indicamos donde almacenar y como esta distribuida la información
	glVertexAttribPointer(numVbo, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(GLfloat), (GLvoid*)0);

	//Indicamos que la tarjeta gráfica puede usar el atributo 0
	glEnableVertexAttribArray(numVbo);

	//Desvinculamos VBO
	glBindBuffer(GL_ARRAY_BUFFER, numVbo);
}

void GLManager::VaoDesconfiguration(int numVao)
{
	//Desvinculamos VAO
	glBindVertexArray(numVao);
}
