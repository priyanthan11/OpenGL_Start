#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);"
"}\0";
// Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f,0.3f,0.02f,1.0f);\n"
"}\n\0";


int main()
{
	// Initiate the window
	glfwInit();

	// Letting know which version of OpenGL we are using
	// In this case we using OpenGL version 3.3.8
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the core profile
	//So that means we only have the modern function
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Verticies coordinates
	GLfloat vertices[] =
	{
		-0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,// lower left corner
		0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,// Lower right corner
		0.0f,0.5f * float(sqrt(3)) * 2 / 3,0.0f // upper corner
	};




	// Creating window object of 800 x 800 pixel, naming it
	GLFWwindow* window = glfwCreateWindow(800,800,"FCA_OPENGL",NULL,NULL);
	if (window==NULL)
	{
		std::cout << "Failed to create OpenGL window" << std::endl;
		glfwTerminate();
		return -1;

	}

	// Use the created window object
	glfwMakeContextCurrent(window);

	// Load needed configuration for OpenGL
	gladLoadGL();


	// Viewport the window
	// 0, 0 = bottom
	//800,800 = top side of window
	glViewport(0, 0,800,800 );

	// Create vertex shader object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach vertex shader source to the vertext shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Compile the vertext shader into machine code
	glCompileShader(vertexShader);


	// Create fragment Shader object and get reference
	GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach fragment Shader source to Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Compine the vertex Shader into machine code
	glCompileShader(fragmentShader);



	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the vertex and fragment shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Warp-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Create reference containers for the Vertex Array object and Vertex buffer Object
	GLuint VAO,VBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// make the VAO the current Vertex Array object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO Specifiying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGl knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the vertex Attribute so that OpenGL know to use it 
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentlly modify the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	// Color window
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Execute the coloring window
	glClear(GL_COLOR_BUFFER_BIT);
	// Inorder to see the buffer we need to swap the buffer
	glfwSwapBuffers(window);

	// Window loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		//Draw the triangke using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		// poll the all events of windows
		glfwPollEvents();
	}

	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Destroy the window
	glfwDestroyWindow(window);
	// Terminate the window 
	glfwTerminate();
	return 0;
}