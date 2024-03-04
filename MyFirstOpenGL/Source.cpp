#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

struct ShaderProgram {

	GLuint vertexShader = 0;
};

void Resize_Window(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight) {

	//Definir nuevo tamaño del viewport
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);
}

// Funcion para cargar un archivo en memoria
std::string Load_File(const std::string& filepath)
{
	// Cargo archivo
	std::ifstream file(filepath);

	std::string fileContent;
	std::string line;

	// Lanzamos error si el archivo no se puede abrir
	if (!file.is_open())
	{
		std::cout << "No se ha podido abrir el archivo, a joderse. " << filepath << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Leemos el contenido y lo volcamos en memoria 
	while (std::getline(file, line))
	{
		fileContent += line + "\n";
	}

	// Cierro streaming de datos y devulvo el contenido
	file.close();
	return fileContent;
}

GLuint LoadVertexShader(const std::string& file)
{
	// Crear un vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Usamos la funcion creada nateriormente para leer el vertex shader y almacenarlo
	std::string sShaderCode = Load_File(file);
	const char* cShaderSource = sShaderCode.c_str();

	// Vinculamos el vertex shader con su codigo fuente
	glShaderSource(vertexShader, 1 /* cantidad de shaders que le paso */, &cShaderSource, nullptr /* si te paso un archivo hasta que punto debes leer*/);

	// Compilar el vertex shader
	glCompileShader(vertexShader);

	// Verificar estado del shader compilado
	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	// Si la compilamos ha sido exitosa devolvemos la referencia al vertex shader
	if (success)
	{
		return vertexShader;
	}
	else
	{
		// Obtenemos longitud del log
		GLint longLenght;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &longLenght);

		// Obtenemos el log
		std::vector<GLchar> errorLog(longLenght);
		glGetShaderInfoLog(vertexShader, longLenght, nullptr, errorLog.data());

		//Mostramos el log y finalizamos programa
		std::cout << "Se ha producido un error al cargar el vertex shader: " << errorLog.data() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

GLuint CreateProgram(const ShaderProgram& shaders)
{
	// Creamos programa de la GPU
	GLuint program = glCreateProgram();

	// Verificar si existe un vertex shader para adjuntarlo
	if (shaders.vertexShader != 0)
	{
		glAttachShader(program, shaders.vertexShader);
	}

	// Limpiar el programa
	glLinkProgram(program);

	// Obtener el estado del programa
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (success)
	{
		// Liberamos recursos
		if (shaders.vertexShader != 0)
		{
			glDetachShader(program, shaders.vertexShader);
		}

		return program;
	}
	else
	{
		// Obtenemos longitud del log
		GLint longLenght;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &longLenght);

		// Obtenemos el log
		std::vector<GLchar> errorLog(longLenght);
		glGetProgramInfoLog(program, longLenght, nullptr, errorLog.data());

		//Mostramos el log y finalizamos programa
		std::cout << "Se ha producido un error al cargar el vertex program: " << errorLog.data() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void main()
{
	int iFrameBufferWidth = 0;
	int iFrameBufferHeight = 0;

	srand(static_cast<unsigned int>(time(NULL)));

	//Inicializamos GLFW para gestionar ventanas e inputs
	glfwInit();

	//Configuramos la ventana
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // version 440 de los shaders 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Inicializamos la ventana
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Engine", NULL, NULL);

	//Asignamos función de callback para cuando el frame buffer es modificado
	glfwSetFramebufferSizeCallback(window, Resize_Window);

	//Definimos espacio de trabajo
	glfwMakeContextCurrent(window);

	//Permitimos a GLEW usar funcionalidades experimentales
	glewExperimental = GL_TRUE;

	//Activamos cull face
	glEnable(GL_CULL_FACE);

	//Indicamos lado del culling
	glCullFace(GL_BACK);

	//Inicializamos GLEW y controlamos errores
	if (glewInit() == GLEW_OK) {

		// Compilar los shaders 
		ShaderProgram myFirstProgram;
		myFirstProgram.vertexShader = LoadVertexShader("My_First_Vertex_Shader.glsl");

		//Compile program
		GLuint myFirstCompiledProgram;
		myFirstCompiledProgram = CreateProgram(myFirstProgram);

		//Definimos color para limpiar el buffer de color
		glClearColor(1.f, 0.f, 0.f, 1.f);

		GLuint vaoPuntos, vboPuntos, vboOffset;

		//Definimos cantidad de vao a crear y donde almacenarlos 
		glGenVertexArrays(1, &vaoPuntos);

		//Indico que el VAO activo de la GPU es el que acabo de crear
		glBindVertexArray(vaoPuntos);

		//Definimos cantidad de vbo a crear y donde almacenarlos
		glGenBuffers(1, &vboPuntos);
		glGenBuffers(1, &vboOffset);

		//Indico que el VBO activo es el que acabo de crear y que almacenará un array. Todos los VBO que genere se asignaran al último VAO que he hecho glBindVertexArray
		glBindBuffer(GL_ARRAY_BUFFER, vboPuntos);

		//Posición X e Y del punto
		GLfloat punto[] = {
			-0.5f,  0.5f, // Vértice superior izquierdo
			-0.5f, -0.5f, // Vértice superior derecho
			 0.0f,  0.5f, // Vértice inferior derecho
			 0.0f, -0.5f, // Vértice inferior derecho
			 0.5f,  0.5f, // Vértice inferior izquierdo
			 0.5f, -0.5f  // Vértice superior izquierdo
		};

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Ponemos los valores en el VBO creado
		glBufferData(GL_ARRAY_BUFFER, sizeof(punto), punto, GL_STATIC_DRAW);

		//Indicamos donde almacenar y como esta distribuida la información
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

		//Indicamos que la tarjeta gráfica puede usar el atributo 0
		glEnableVertexAttribArray(0);

		//Limpiamos el VBO activo
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Configurar segundo VBO 

		
		//Configuramos el vbo activo
		glBindBuffer(GL_ARRAY_BUFFER, vboOffset);

		GLfloat randomOffset[12];
		for (int i = 0; i < 12; i++) {
			randomOffset[i] = static_cast<GLfloat>(rand()) / RAND_MAX * 0.5f;
		}

		//Ponemos los valores en el VBO creado
		glBufferData(GL_ARRAY_BUFFER, sizeof(randomOffset), randomOffset, GL_STATIC_DRAW);

		//Indicamos donde almacenar y como esta distribuida la información
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

		//Indicamos que la tarjeta gráfica puede usar el atributo 1
		glEnableVertexAttribArray(1);

		//Desvinculamos VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Desvinculamos VAO
		glBindVertexArray(0);


		//We indicate which program the graphic card should use
		glUseProgram(myFirstCompiledProgram);


		//Generamos el game loop
		while (!glfwWindowShouldClose(window)) {

			//Pulleamos los eventos (botones, teclas, mouse...)
			glfwPollEvents();

			//Limpiamos los buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			//Definimos que queremos usar el VAO con los puntos
			glBindVertexArray(vaoPuntos);

			//Definimos que queremos dibujar
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

			//Dejamos de usar el VAO indicado anteriormente
			glBindVertexArray(0);

			//Cambiamos buffers
			glFlush();
			glfwSwapBuffers(window);
		}
		//Desactivate the program and free memory
		glUseProgram(0);
		glDeleteProgram(myFirstCompiledProgram);
	}
	else {
		std::cout << "Ha petao." << std::endl;
		glfwTerminate();
	}
	//Finalizamos GLFW
	glfwTerminate();
}