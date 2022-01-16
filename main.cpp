#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<cmath>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main() {
	//first thing we need to do is to initialize it so that we could properly use it's function
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//Specifying the version of opengl that we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//vertices for triangle
	GLfloat vertices[] = {
		-0.5f,-0.5f * float(sqrt(3)) / 3 ,0.0f,
		0.5f,-0.5f * float(sqrt(3)) / 3 ,0.0f,
		0.5f,0.5f * float(sqrt(3)) / 3 ,-0.0f,
		-0.5f,0.7f,0.4f,
		0.0f,-0.7f * float(sqrt(3)) / 3 ,-0.4f,
		0.0f,-0.3f * float(sqrt(3)) / 3 ,0.2f,
		0.0f,0.2f * float(sqrt(3)) / 3 ,-0.3f,
		0.0f,-0.7f,0.4f,
	};

	GLuint indices[] = {
		0,3,5, //lower left triangle
		3,2,9,
		5,4,1
	};




	//datatype for window object
	GLFWwindow* window = glfwCreateWindow(800,800,"Grph polty",NULL,NULL);
	if (window == NULL) {
		std::cout << "window failed to create" << std::endl;
		glfwTerminate();
		return -1;
	}
	//telling glfw to use window
	glfwMakeContextCurrent(window);
	//we are telling glad to load needed configuration for opengl
	gladLoadGL();
	//
	glViewport(0, 0, 800, 800);
	//
	//vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource,NULL);
	glCompileShader(vertexShader);
	
	//fragment shader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	//attaching the our shader program
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	GLuint VAO,VBO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glClearColor(0.7f, 0.13f, 0.17f,1.0f); //rgba
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);


	while (!glfwWindowShouldClose(window)) {
		//the window response to our events
		glClearColor(0.0f, 0.13f, 0.17f, 1.0f); //rgba
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	//once we are done with window we want to delete it
	glfwDestroyWindow(window);
	//since we initialize it we should also terminate it before function end

	glfwTerminate();
	return 0;
}