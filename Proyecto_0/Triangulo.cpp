#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Código fuente del Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n" // Atributo de entrada para las posiciones de los vértices
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" // Asigna la posición a gl_Position
"}\0";
// Código fuente del Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n" // Variable de salida para el color del fragmento
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n" // Asigna un color RGBA (rojo, verde, azul, alfa)
"}\n\0";



int main()
{
	// Inicializa GLFW
	glfwInit();

	// Indicar a GLFW qué versión de OpenGL estamos usando 
	// En este caso estamos usando OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Versión mayor de OpenGL (3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Versión menor de OpenGL (3)
	// Indicar a GLFW que usamos el perfil CORE
	// Eso significa que solo tenemos las funciones modernas
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Perfil Core de OpenGL

	// Crear un objeto GLFWwindow de 800 por 800 píxeles, llamándolo "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL); // Crea la ventana de 800x800 píxeles
	// Verificar si la creación de la ventana falló
	if (window == NULL) // Verifica si la ventana fue creada correctamente
	{
		std::cout << "Fallo al crear la ventana GLFW" << std::endl; // Mensaje de error
		glfwTerminate();
		return -1;
	}
	// Introducir la ventana en el contexto actual
	glfwMakeContextCurrent(window); // Asigna la ventana al contexto actual

	// Cargar GLAD para que configure OpenGL
	gladLoadGL();
	// Especificar el área de la ventana de OpenGL
	// En este caso el área va de x = 0, y = 0, a x = 800, y = 800
	glViewport(0, 0, 800, 800); // Define el área de visualización de OpenGL



	// Crear un objeto Shader de Vértices y obtener su referencia
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Crear el Vertex Shader
	// Adjuntar el código fuente del Vertex Shader al objeto Shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Añadir el código del Vertex Shader
	// Compilar el Vertex Shader a código máquina
	glCompileShader(vertexShader); // Compilar el Vertex Shader

	// Crear un objeto Shader de Fragmentos y obtener su referencia
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Crear el Fragment Shader
	// Adjuntar el código fuente del Fragment Shader al objeto Shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Añadir el código del Fragment Shader
	// Compilar el Fragment Shader a código máquina
	glCompileShader(fragmentShader); // Compilar el Fragment Shader

	// Crear un objeto Programa de Shaders y obtener su referencia
	GLuint shaderProgram = glCreateProgram(); // Crear el programa de Shaders
	// Adjuntar los Shaders de Vértices y Fragmentos al programa de Shaders
	glAttachShader(shaderProgram, vertexShader); // Adjuntar el Vertex Shader
	glAttachShader(shaderProgram, fragmentShader); // Adjuntar el Fragment Shader
	// Vincular todos los shaders en el programa
	glLinkProgram(shaderProgram); // Enlazar los Shaders

	// Eliminar los objetos Vertex y Fragment Shader ya que son innecesarios
	glDeleteShader(vertexShader); // Eliminar el Vertex Shader
	glDeleteShader(fragmentShader); // Eliminar el Fragment Shader



	// Coordenadas de los vértices
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Esquina inferior izquierda
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Esquina inferior derecha
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Esquina superior
	};

	// Crear contenedores de referencia para el Objeto de Array de Vértices (VAO) y el Objeto de Buffer de Vértices (VBO)
	GLuint VAO, VBO;

	// Generar el VAO y VBO con solo 1 objeto cada uno
	glGenVertexArrays(1, &VAO); // Generar el VAO
	glGenBuffers(1, &VBO); // Generar el VBO

	// Hacer del VAO el Objeto de Array de Vértices actual enlazándolo
	glBindVertexArray(VAO); // Enlazar el VAO

	// Enlazar el VBO especificando que es un GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Enlazar el VBO
	// Introducir los vértices en el VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Cargar los vértices

	// Configurar el Atributo de Vértices para que OpenGL sepa cómo leer el VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Configurar el Atributo de Vértices
	// Habilitar el Atributo de Vértices para que OpenGL sepa que debe usarlo
	glEnableVertexAttribArray(0); // Habilitar el Atributo de Vértices

	// Desenlazar tanto el VBO como el VAO para evitar modificar accidentalmente el VAO y el VBO que creamos
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Desenlazar el VBO
	glBindVertexArray(0); // Desenlazar el VAO



	// Bucle principal
	while (!glfwWindowShouldClose(window)) // Mientras la ventana no deba cerrarse
	{
		// Especificar el color de fondo
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Color de fondo
		// Limpiar el buffer trasero y asignarle el nuevo color
		glClear(GL_COLOR_BUFFER_BIT); // Limpiar el buffer
		// Decirle a OpenGL qué programa de shaders queremos usar
		glUseProgram(shaderProgram); // Usar el programa de shaders
		// Enlazar el VAO para que OpenGL sepa que debe usarlo
		glBindVertexArray(VAO); // Enlazar el VAO
		// Dibujar el triángulo usando la primitiva GL_TRIANGLES
		glDrawArrays(GL_TRIANGLES, 0, 3); // Dibujar el triángulo
		// Intercambiar el buffer trasero con el buffer delantero
		glfwSwapBuffers(window); // Intercambiar buffers
		// Manejar todos los eventos de GLFW
		glfwPollEvents(); // Manejar eventos
	}



	// Eliminar todos los objetos que hemos creado
	glDeleteVertexArrays(1, &VAO); // Eliminar el VAO
	glDeleteBuffers(1, &VBO); // Eliminar el VBO
	glDeleteProgram(shaderProgram); // Eliminar el programa de shaders
	// Eliminar la ventana antes de terminar el programa
	glfwDestroyWindow(window); // Destruir la ventana
	// Terminar GLFW antes de terminar el programa
	glfwTerminate(); // Terminar GLFW
	return 0;
}
