#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

float fov = 45.0f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;


int main()
{

	glfwInit();


	//the vertex shader source code i put it in a string because im lazy and it's 3 am so give me a fucking break
	
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"uniform mat4 transform;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"   gl_Position =  projection * view * model * vec4(aPos, 1.0);\n"
		"   ourColor = aColor;\n"
		"}\0";
// the fragment shader source code
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(ourColor, 1.0f);\n"
		"}\n\0";





	const char* vertexShaderSource2 = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"uniform mat4 transform;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"   gl_Position =  projection * view * model * vec4(aPos, 1.0);\n"
		"   ourColor = aColor;\n"
		"}\0";
	// the fragment shader source code
	const char* fragmentShaderSource2 = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(ourColor, 1.0f);\n"
		"}\n\0";













	//the vertices 

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,

	-0.5f,  0.5f, -0.5f,  1.0f, 0.0f,0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f
	};







	float vertices2[] = {
		// first triangle
 01.5f,  01.5f, 0.0f,  1.0f,  1.0f, 1.0f,  // top right
 01.5f, -01.5f, 0.0f,  1.0f,  1.0f, 1.0f,
-01.5f,  01.5f, 0.0f,  1.0f,  1.0f, 1.0f,
// second triangle
 01.5f, -01.5f, 0.0f,  1.0f,  1.0f, 1.0f,
-01.5f, -01.5f, 0.0f,  1.0f,  1.0f, 1.0f,
-01.5f,  01.5f, 0.0f,   1.0f,  1.0f, 1.0f
	
	};

	float cubex = 0;
	float cubey = 4;
	float cubez = 0;

	float velx = 0;
	float vely = 0;
	float velz = 0;

	float g = 0.003;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);




	GLFWwindow* window = glfwCreateWindow(800, 800, "opengl test project", NULL, NULL);

	glfwSetCursorPosCallback(window, cursorPositionCallback);
	//displaying a message if i fail to load the window
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);


	
	//loading GLAD that manages the modern opengl function pointers
	gladLoadGL();


	//generating the shader program
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);



	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);




	unsigned int vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);
	glCompileShader(vertexShader2);



	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);

	unsigned int shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader2);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);


	glDeleteShader(vertexShader2);
	glDeleteShader(fragmentShader2);





	// creating the vertex buffer object and the vertex array object
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);




	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);




	unsigned int VBO2, VAO2;

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);




	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0);

	glViewport(0, 0, 800, 800);
	//an array of vctor positions i made it like that so i can make more cubes without making my life hell
	glm::vec3 cubePositions[] = {


	glm::vec3(cubex,  cubey,  cubez)




	};


	//making the cube draw as lines instead of a solid color to make it look cool
	

	//allowing depth 
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//the main loop stays looping untill you close the window
	
	while (!glfwWindowShouldClose(window))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// setting up the matrices 
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0, 0, -3.0));

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(fov), 800.0f / 800.0f, 0.1f, 100.0f);

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 1.0f));



		glm::mat4 model2 = glm::mat4(1.0f);
		model2 = glm::rotate(model2, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		

		glm::mat4 trans2 = glm::mat4(0.0f);
		trans2 = glm::translate(trans2, glm::vec3(0.5f, -0.5f, 0.0f));
		trans2 = glm::rotate(trans2, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		


		glUseProgram(shaderProgram);

		// gravity stuff that i decided to not use
		vely -= g;

		cubex += velx;
		cubey += vely;
		cubez += velz;

		cubePositions[0] = glm::vec3(cubex, cubey, cubez);


		//some gravity stuff that i decided to not use

		if (cubey <= 0.54)
		{
			vely = vely * -0.9;
			g = 0;
		}
		else {
			g = 0.003;
		}
		float mousex = 0;

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			vely += 0.00001;
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			vely = 0;
			velx = 0;
			cubey = 4;
			g = 0.003;
		}
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
			g += 0.0005;
		}
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
			g -= 0.0005;
		}

		//sending the matrices to the shaders as uniforms
		int modelLoc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewlLoc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(viewlLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projectionlLoc = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(projectionlLoc, 1, GL_FALSE, glm::value_ptr(projection));


		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		


		//binding the vertex array object
		glBindVertexArray(VAO);

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glUniformMatrix4fv(viewlLoc, 1, GL_FALSE, glm::value_ptr(view));
		// looping throw the length of the cubes and drawing each one made it like that so i can add as much cubes as i want
		for (unsigned int i = 0; i < 1; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 0 * i;
			 // every 3rd iteration (including the first) we set the angle using GLFW's time function.
			
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glUseProgram(shaderProgram2);

		//sending the matrices to the shaders as uniforms
		int modelLoc2 = glGetUniformLocation(shaderProgram2, "model");
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));

		int viewlLoc2 = glGetUniformLocation(shaderProgram2, "view");
		glUniformMatrix4fv(viewlLoc2, 1, GL_FALSE, glm::value_ptr(view));

		int projectionlLoc2 = glGetUniformLocation(shaderProgram2, "projection");
		glUniformMatrix4fv(projectionlLoc2, 1, GL_FALSE, glm::value_ptr(projection));


		unsigned int transformLoc2 = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(trans2));


		model = glm::mat4(1.0f);
		model2 = glm::translate(model2, glm::vec3(0, 0, 0));
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//the camera movment

		float cameraSpeed = 0.005f; // adjust accordingly
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			cameraSpeed = 0.1;
		}
		else {
			cameraSpeed = 0.05;
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		
		

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;



		//the camera rotation (i didn;t use mouse movement because it did't work for some reason
		float sens = 0.02; // adjust accordingly
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			yaw += sens;
		}
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		{
			yaw -= sens;
		}
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		{
			pitch += sens;
		}
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		{
			pitch -= sens;
		}

		// applying the rotaion and adjusting the camer front
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
		
		// swaping the back buffer with the front buffer
		glfwSwapBuffers(window);
		//handles the events
		glfwPollEvents();
	}


	// destroying the window 
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

static void cursorPositionCallback(GLFWwindow *window, double xpos,double ypos)
{
	

	pitch = ypos * -0.1125 * 2;
	yaw = xpos * 0.1125;
}

