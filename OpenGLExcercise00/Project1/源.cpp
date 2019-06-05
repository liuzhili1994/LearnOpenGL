#include <iostream>

#define  GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#include "Shader.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//��OpenGL�У��κ����ﶼ��3D�ռ��У�����Ļ�ʹ���ȴ��2D�������飬
//�⵼��OpenGL�Ĵ󲿷ֹ������ǹ��ڰ�3D����ת��Ϊ��Ӧ����Ļ��2D���ء�
//3D����תΪ2D����Ĵ����������OpenGL��ͼ����Ⱦ����
//��Graphics Pipeline�������Ϊ���ߣ�ʵ����ָ����һ��ԭʼͼ������;��һ�����͹ܵ����ڼ侭�����ֱ仯�������ճ�������Ļ�Ĺ��̣�����ġ�
//ͼ����Ⱦ���߿��Ա�����Ϊ������Ҫ���֣���һ���ְ����3D����ת��Ϊ2D���꣬�ڶ������ǰ�2D����ת��Ϊʵ�ʵ�����ɫ�����ء�

//float vertices[] = {
//	-0.5f, -0.5f, 0.0f,1.0f,0,0,
//	0.5f, -0.5f, 0.0f,0,1.0f,0,
//	0.0f,  0.5f, 0.0f,0,0,1.0f,
//	0.8f, 0.8f, 0.0f,0.3f,0.5f,0.7f
//};

//������
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, //
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

//float vertices[] = {
//	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
//};
//��ʾͼƬ��һ�����ص�
//float vertices[] = {
//	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.55f, 0.55f,   // ����
//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.55f, 0.45f,   // ����
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.45f, 0.45f,   // ����
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.45f, 0.55f    // ����
//};


unsigned int indices[] = {
	0,1,2,
	2,3,0
};

//������ɫ�����  shaderԪ����
//const char* vertexShaderSource =
//"#version 330 core				      \n										 "
//"layout(location = 10) in vec3 aPos;		      \n						 "
//"out vec4 vectexColor ;				       \n								   "
//"void main() {\n																	  "
//"		gl_Position = vec4(aPos, 1.0);      \n "
//"       vectexColor = vec4(0.5,0.0,0.0,1.0); } \n		";
//
//const char* fragmentShaderSource =
//"#version 330 core				       \n									   "
//"in vec4 vectexColor;				       \n								   "
//"uniform vec4 customColor;         \n								 "
//"out vec4 FragColor;				       \n								   "
//"void main() {						\n										   "
//"		FragColor = customColor;} 	       \n		   ";

float mixValue = 0.8f;

//glm::mat4 trans = glm::mat4(1.0f);

//���ǽ��ܶ�����ɫ��shaderԪ����
const char* vertexShaderSource ;

const char* fragmentShaderSource ;

//�����û����룬���û�а��¶���İ�����escape�����᷵�� GLFEW_RELEASE
//���������escape����ͨ��glfwSetWindowShouldClose���� ��WindowsShouldClose��������Ϊtrue���ر�GLFW
void ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//TODO  glfwSetWindowShouldClose ��  glfwWindowShouldClose
		glfwSetWindowShouldClose(window, true);
		//glfwWindowShouldClose(window);  //��������ز���
	}
}


int main() {
	
	
	

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//���� GLFW ����
	GLFWwindow* myWindow = glfwCreateWindow(800,600,"My OpenGL Window",NULL,NULL);
	if (myWindow == NULL)
	{
		printf("Open Window Failed-------------------------");
		
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(myWindow);

	//��ʼ�� GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW Failed��������������������");
		
		glfwTerminate();
		return -1;
	}
	//TODO   ��һ�仰���в�����û��ʲô����   ������
	//glViewport(1000,1000,800,600);   

	//���治����Ⱦ  OpenGL ��������ʱ�����
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);*/

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//��ʼ�����루ֻ����һ�Σ������������Ƶ���ı䣩��
	//1.��VAO
	glBindVertexArray(VAO);  //OpenGLͬʱֻ�ܴ���һ��VAO,��仰��˼��˵���Կ����ھͶԵ�ǰ���VAO���в���
	
	//���㻺�����Vertex Buffer Objects������GPU�ڴ棨ͨ�����Դ棩�д洢��������     ��������������һ������GPU���ʹ���������Ϣ
	unsigned int VBO;
	glGenBuffers(1,&VBO);  //�÷����������ɶ��VBO  ���£�
	/*unsigned int VBO1[100];
	glGenBuffers(100, VBO1);*/

	//2.�Ѷ������鸴�Ƶ������й�OpenGLʹ��
	//OpenGL���кܶ໺��������ͣ����㻺�����ͣ�VBO����������GL_ARRAY_BUFFER
	//ʹ��glBindBuffer���½��Ļ������󶨵�GL_ARRAY_BUFFERĿ����
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	//ʹ��glBufferData������֮ǰ����Ķ������ݸ��Ƶ�������ڴ���  ���ĸ������������Կ��ٽ��ܵ�����֮����δ��������
	//��3�з�ʽ  GL_STATIC_DRAW �����ݲ���򼸺�����ı�
	//                  GL_DYNAMIC_DRAW �����ݻᱻ�ı�ܶ�
	//					 GL_STREAM_DRAW ������ÿ�λ���ʱ����ı�
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	/*����Ŀǰ    �����Ѿ��Ѷ������ݴ������Կ����ڴ��У���VBO������㻺��������*/
	

	unsigned int EBO;
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
	
	Shader* shader = new Shader("vertexSource.txt", "fragmentSource.txt");

	// 3. ���ö�������ָ�루�����Կ�����Щ������ô������
	glVertexAttribPointer(10,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(10);

	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//����
	unsigned int TexBuffer1,TexBuffer2;																																
	glGenTextures(1,&TexBuffer1);																					
	//���м���������GL_TEXTURE_2D�������ڶ��Դ����������Ч	���ٷ�ע�ͣ�
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBuffer1); //ע��˴�����glBindBuffer					
	//Ϊ��ǰ�󶨵�����������û��ƣ����˷�ʽ																	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);					
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);					
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);				
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);				
	//���ز���������
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("awesomeface.png",&width,&height,&nrChannel,0);
	if (data)
	{
		//��ǰ�󶨵��������ᱻ����������ͼ��
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	glGenTextures(1, &TexBuffer2);
	//���м���������GL_TEXTURE_2D�������ڶ��Դ����������Ч	���ٷ�ע�ͣ�	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TexBuffer2); //ע��˴�����glBindBuffer					
	//Ϊ��ǰ�󶨵�����������û��ƣ����˷�ʽ																	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	data = stbi_load("container.jpg", &width, &height, &nrChannel, 0);
	if (data)
	{
		//��ǰ�󶨵��������ᱻ����������ͼ��
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	
	shader->Use();
	glUniform1i(glGetUniformLocation(shader->shaderProgram, "textureBuffer1"), 0);
	glUniform1i(glGetUniformLocation(shader->shaderProgram, "textureBuffer2"), 1);
	glUniform1f(glGetUniformLocation(shader->shaderProgram, "mixValue"), mixValue);
	//�ڶ�����������opengl����Ҫ���Ͷ��ٸ�����
	//����������Ϊ�����Ƿ�ϣ�����͵ľ�������û���Transpose��OpenGL������ͨ��ʹ��һ���ڲ����󲼾֣�
	//����������(Column-major Ordering)���֡�GLM��Ĭ�ϲ��־������������Բ�����Ҫ�û�����������GL_FALSE
	//���һ������Ϊ���͵�����������(ʹ��glm����ת��Ϊopengl���Ե���ʶ������)
	/*trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans,glm::vec3(0.5,0.5,0.5));*/
	//glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
	
	glm::mat4 rotMat = glm::mat4(1.0f);
	rotMat = glm::rotate(rotMat,glm::radians(-55.0f),glm::vec3(1.0,0,0));
	glm::mat4  viewMat= glm::mat4(1.0f);
	viewMat = glm::translate(viewMat,glm::vec3(0,0,-3.0));
	glm::mat4 proMat = glm::mat4(1.0f);
	proMat = glm::perspective(glm::radians(45.0),800.0/600,0.1,100.0);


	glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram,"rotMat"),1,GL_FALSE,glm::value_ptr(rotMat));
	glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "proMat"), 1, GL_FALSE, glm::value_ptr(proMat));


	//��Ⱦѭ��
	while (!glfwWindowShouldClose(myWindow))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glDrawArrays(GL_TRIANGLES,0,3);
		
		
		
		
		shader->Use();
		
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		glfwSwapBuffers(myWindow);
		glfwPollEvents();//��ȡ�û�����  //û������������û������϶������ܶ��κ��û�������������
		ProcessInput(myWindow);
		
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();//��Ⱦ�����ͷ���Դ
	return 0;
}//main_End



