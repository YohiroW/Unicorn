//
//#include <cmath>
//
//// GLEW
//#include <GL/glew.h>
//
//// GLFW
//#include <GLFW/glfw3.h>
//
//// Other Libs
//#include <soil/SOIL.h>
//// GLM Mathematics
////#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//// Other includes
//#include "Shader.h"
//#include "Camera.h"
//
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void do_movement();
//
//// Window dimensions
//const GLuint WIDTH = 800, HEIGHT = 600;
//
//// Camera
//Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
//GLfloat lastX  =  WIDTH  / 2.0;
//GLfloat lastY  =  HEIGHT / 2.0;
//bool    keys[1024];
//
//// Light attributes
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//// Deltatime
//GLfloat deltaTime = 0.0f;	
//GLfloat lastFrame = 0.0f;  	
//
//
//int main(int argc, char* argv[])
//{
//#pragma region init
//
//	glfwInit();
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LightModel", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//
//	// Set the required callback functions
//	glfwSetKeyCallback(window, key_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	glewExperimental = GL_TRUE;
//	glewInit();
//
//	glViewport(0, 0, WIDTH, HEIGHT);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_STENCIL_TEST);
//	glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
//	glStencilFunc(GL_NOTEQUAL,1,0xFF);
//	
//#pragma endregion
//
//	Shader lampShader("shaders/light.vs", "shaders/light.frag");
//	Shader lightingShader("shaders/lightCaster.vs", "shaders/spotLight.frag");
//	Shader gouraudShader("shaders/phongVertex.vs","shaders/phongFrag.frag");
//	Shader rimShader("shaders/rimShader.vs","shaders/rimShader.frag");
//
//#pragma region vertex data
//	GLfloat vertices[] = {
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//	};
//	// First, set the container's VAO (and VBO)
//	GLuint VBO, containerVAO;
//	glGenVertexArrays(1, &containerVAO);
//	glGenBuffers(1, &VBO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindVertexArray(containerVAO);
//	// Position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	//normal
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	//tex
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6* sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//	glBindVertexArray(0);
//
//
//	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
//	GLuint lightVAO;
//	glGenVertexArrays(1, &lightVAO);
//	glBindVertexArray(lightVAO);
//	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	// Set the vertex attributes (only position data for the lamp))
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//
//#pragma endregion vertex data
//
//	glm::vec3 cubePosition[10] = { 
//
//		glm::vec3( 0.0f,  0.0f,  0.0f),
//		glm::vec3( 2.0f,  5.0f, -15.0f),
//		glm::vec3(-1.5f, -2.2f, -2.5f),
//		glm::vec3(-3.8f, -2.0f, -12.3f),
//		glm::vec3( 2.4f, -0.4f, -3.5f),
//		glm::vec3(-1.7f,  3.0f, -7.5f),
//		glm::vec3( 1.3f, -2.0f, -2.5f),
//		glm::vec3( 1.5f,  2.0f, -2.5f),
//		glm::vec3( 1.5f,  0.2f, -1.5f),
//		glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//
//	//GLuint emissionMap;
//	//glGenTextures(1, &emissionMap);
//	//texture to load
//	GLuint texHandle;
//	int width,height;
//	unsigned char* tex = SOIL_load_image("box.png",&width,&height,0,SOIL_LOAD_RGB);
//	glGenTextures(1,&texHandle);
//	glBindTexture(GL_TEXTURE_2D,texHandle);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//
//	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,tex);
//	glGenerateMipmap(GL_TEXTURE_2D);
//
//	SOIL_free_image_data(tex);
//	glBindTexture(GL_TEXTURE_2D,0);
//
//	GLuint lightingMapHandle;
//	unsigned char* lightMap = SOIL_load_image("box_specular.png",&width,&height,0,SOIL_LOAD_RGB);
//	glGenTextures(1,&lightingMapHandle);
//	glBindTexture(GL_TEXTURE_2D,lightingMapHandle);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//
//	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,lightMap);
//	glGenerateMipmap(GL_TEXTURE_2D);
//
//	SOIL_free_image_data(lightMap);
//	glBindTexture(GL_TEXTURE_2D,0);
//
//	////
//	lightingShader.apply();
//	//diffuse tex
//	glUniform1i(glGetUniformLocation(lightingShader.getProgram(),"material.diffuse"),0);
//	glUniform1i(glGetUniformLocation(lightingShader.getProgram(),"material.specular"),1);
//
//	// Game loop
//	while (!glfwWindowShouldClose(window))
//	{
//		// 
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//		//
//		glfwPollEvents();
//		do_movement();
//		// Clear the colorbuffer
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	
//		//////////////////////////////////////////////////////////////////////////
//		lightingShader.apply();
//		glStencilFunc(GL_ALWAYS,1,0xFF);
//		glStencilMask(0x00);
//
//		//mofify the color of light source;
//		glm::vec3 lightColor;
//		lightColor.x = sin(glfwGetTime()* 2.0f);
//		lightColor.y = sin(glfwGetTime()* 0.7f);
//		lightColor.z = sin(glfwGetTime()* 1.3f);
//		
//		glm::vec3 diffuseColor = glm::vec3(0.5f);
//		glm::vec3 ambietColor = glm::vec3(0.2f);
//
//
//		glUniform3f(glGetUniformLocation(lightingShader.getProgram(),"viewPos"),camera.Position.x,camera.Position.y,camera.Position.z);
//		//material
//		glUniform1f(glGetUniformLocation(lightingShader.getProgram(),"material.shineness"),64.0f);
//
//		glUniform3f(glGetUniformLocation(lightingShader.getProgram(),"light.lAmbiet"),ambietColor.x,ambietColor.y,ambietColor.z);
//		glUniform3f(glGetUniformLocation(lightingShader.getProgram(),"light.lDiffuse"),lightColor.x ,lightColor.y,lightColor.z);
//		glUniform3f(glGetUniformLocation(lightingShader.getProgram(),"light.lSpecular"),1.0f,1.0f,1.0f);
//
//		glUniform3f(glGetUniformLocation(lightingShader.getProgram(),"light.lPosition"),camera.Position.x,camera.Position.y,camera.Position.z);
//		//glUniform3f(glGetUniformLocation(lightingShader.getProgram(),"light.direction"), -0.2f, -1.0f, -0.3f);
//		glUniform3f(glGetUniformLocation(lightingShader.getProgram(),"light.direction"), camera.Front.x,camera.Front.y, camera.Front.z);
//		glUniform1f(glGetUniformLocation(lightingShader.getProgram(),"light.cutOff"), glm::cos(glm::radians(12.5f)));
//		glUniform1f(glGetUniformLocation(lightingShader.getProgram(),"light.outerCutOff"), glm::cos(glm::radians(17.5f)));
//
//		glUniform1f(glGetUniformLocation(lightingShader.getProgram(),"light.constant"), 1.0f);
//		glUniform1f(glGetUniformLocation(lightingShader.getProgram(),"light.linear"), 0.09f);
//		glUniform1f(glGetUniformLocation(lightingShader.getProgram(),"light.quadratic"), 0.032f);
//		
//
//		// Create camera transformations
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
//		
//		// Get the uniform locations
//		GLint modelLoc = glGetUniformLocation(lightingShader.getProgram(), "model");
//		GLint viewLoc  = glGetUniformLocation(lightingShader.getProgram(),  "view");
//		GLint projLoc  = glGetUniformLocation(lightingShader.getProgram(),  "projection");
//		// Pass the matrices to the shader
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//		// Draw the container (using container's vertex attributes)
//		glBindVertexArray(containerVAO);
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D,texHandle);
//
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D,lightingMapHandle);
//		
//		glm::mat4 model;
//		for(int i = 0; i< 10; ++i)
//		{
//			model = glm::mat4();
//			model = glm::translate(model,cubePosition[i]);
//			float angle = i* 20.0f;
//			model = glm::rotate(model,angle,glm::vec3(1.0f,0.3f,0.5f));
//			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//		glBindVertexArray(0);
//		///////////////////////////////////////////////////////////////////////////
//		gouraudShader.apply();
//
//		//stencil test
//		glStencilFunc(GL_ALWAYS,1,0xFF);
//		glStencilMask(0xFF);
//
//		//trans matrixs
//		glm::mat4 modelMat;
//		modelMat = glm::translate(modelMat, glm::vec3(0.0f,0.0f,4.0f));
//		modelMat =  glm::rotate(modelMat,(float)(sin(glfwGetTime())),glm::vec3(0.5f,0.5f,0.5f));
//		glm::mat4 projMat = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
//		glUniformMatrix4fv(glGetUniformLocation(gouraudShader.getProgram(),"model"),1, GL_FALSE, value_ptr(modelMat));
//		glUniformMatrix4fv(glGetUniformLocation(gouraudShader.getProgram(),"view"),1, GL_FALSE, value_ptr(camera.GetViewMatrix()));
//		glUniformMatrix4fv(glGetUniformLocation(gouraudShader.getProgram(),"projection"),1, GL_FALSE, value_ptr(projMat));
//		//
//		glUniform3f(glGetUniformLocation(gouraudShader.getProgram(),"lightPos"),lightPos.x,lightPos.y,lightPos.z);
//		glUniform3f(glGetUniformLocation(gouraudShader.getProgram(),"viewPos"),camera.Position.x,camera.Position.y,camera.Position.z);
//		glUniform3f(glGetUniformLocation(gouraudShader.getProgram(),"lightColor"),1.0f, 1.0f, 1.0f);
//		glUniform3f(glGetUniformLocation(gouraudShader.getProgram(),"objectColor"),1.0f, 0.5f, 0.31f);
//
//		glBindVertexArray(containerVAO);
//		glDrawArrays(GL_TRIANGLES, 0 ,36);
//
//		//rimShader.apply();
//		////the every byte compare with 1 in mask
//		//glStencilFunc(GL_NOTEQUAL,1,0xFF);
//		//glStencilMask(0x00);
//
//		////SCALE
//		//modelMat = glm::scale(modelMat,glm::vec3(1.05f,1.05f,1.05f));
//		//glUniformMatrix4fv(glGetUniformLocation(rimShader.getProgram(),"model"),1, GL_FALSE, value_ptr(modelMat));
//		//glUniformMatrix4fv(glGetUniformLocation(rimShader.getProgram(),"view"),1, GL_FALSE, value_ptr(camera.GetViewMatrix()));
//		//glUniformMatrix4fv(glGetUniformLocation(rimShader.getProgram(),"projection"),1, GL_FALSE, value_ptr(projMat));
//
//		//glDrawArrays(GL_TRIANGLES, 0 ,36);
//		//glBindVertexArray(0);
//
//		//glStencilMask(0xFF);
//		////////////////////////////////////////////////////////////////////////
//		lampShader.apply();
//
//		glStencilFunc(GL_ALWAYS,1,0xFF);
//		glStencilMask(0xFF);
//		
//		modelLoc = glGetUniformLocation(lampShader.getProgram(), "model");
//		viewLoc  = glGetUniformLocation(lampShader.getProgram(), "view");
//		projLoc  = glGetUniformLocation(lampShader.getProgram(), "projection");
//
//		// Set matrices
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//		model = glm::mat4();
//
//		model = glm::translate(model, lightPos);
//		model = glm::scale(model, glm::vec3(0.2f));
//		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//		glBindVertexArray(lightVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//		///////////////////////////////////////////////////////////////////////////
//		glfwSwapBuffers(window);
//	}
//	glfwTerminate();
//	return 0;
//}
//
//// Is called whenever a key is pressed/released via GLFW
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	if (key >= 0 && key < 1024)
//	{
//		if (action == GLFW_PRESS)
//			keys[key] = true;
//		else if (action == GLFW_RELEASE)
//			keys[key] = false;
//	}
//}
//
//void do_movement()
//{
//	// Camera controls
//	if (keys[GLFW_KEY_W])
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (keys[GLFW_KEY_S])
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (keys[GLFW_KEY_A])
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (keys[GLFW_KEY_D])
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//bool firstMouse = true;
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	GLfloat xoffset = xpos - lastX;
//	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}
//
//GLuint loadTexture(const char* path)
//{
//	GLuint texId;
//	//-1- generate a texture in opengl
//	glGenTextures(1,&texId); //-1 size -2 texture id
//
//	int width,height;
//	//-2- use external lib to load image to cache
//	unsigned char* image = SOIL_load_image(path,&width,&height,0,SOIL_LOAD_RGBA);
//	//-3- bind current texture to set parameters
//	glBindTexture(GL_TEXTURE_2D, texId);
//	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	//-4- specific parameters
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//	//-5- unbind and free the cache image occupied
//	glBindTexture(GL_TEXTURE_2D,0);
//	SOIL_free_image_data(image);
//
//	return texId;
//}