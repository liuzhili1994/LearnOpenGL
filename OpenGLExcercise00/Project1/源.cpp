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

//在OpenGL中，任何事物都在3D空间中，而屏幕和窗口却是2D像素数组，
//这导致OpenGL的大部分工作都是关于把3D坐标转变为适应你屏幕的2D像素。
//3D坐标转为2D坐标的处理过程是由OpenGL的图形渲染管线
//（Graphics Pipeline，大多译为管线，实际上指的是一堆原始图形数据途经一个输送管道，期间经过各种变化处理最终出现在屏幕的过程）管理的。
//图形渲染管线可以被划分为两个主要部分：第一部分把你的3D坐标转换为2D坐标，第二部分是把2D坐标转变为实际的有颜色的像素。

//float vertices[] = {
//	-0.5f, -0.5f, 0.0f,1.0f,0,0,
//	0.5f, -0.5f, 0.0f,0,1.0f,0,
//	0.0f,  0.5f, 0.0f,0,0,1.0f,
//	0.8f, 0.8f, 0.0f,0.3f,0.5f,0.7f
//};

//正方体
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
//	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};
//显示图片的一个像素点
//float vertices[] = {
//	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.55f, 0.55f,   // 右上
//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.55f, 0.45f,   // 右下
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.45f, 0.45f,   // 左下
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.45f, 0.55f    // 左上
//};


unsigned int indices[] = {
	0,1,2,
	2,3,0
};

//这是绿色渐变的  shader元数据
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

//这是接受顶点颜色的shader元数据
const char* vertexShaderSource ;

const char* fragmentShaderSource ;

//处理用户输入，如果没有按下定义的按键（escape）将会返回 GLFEW_RELEASE
//如果按下了escape键，通过glfwSetWindowShouldClose函数 将WindowsShouldClose属性设置为true来关闭GLFW
void ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//TODO  glfwSetWindowShouldClose 和  glfwWindowShouldClose
		glfwSetWindowShouldClose(window, true);
		//glfwWindowShouldClose(window);  //这个方法关不掉
	}
}


int main() {
	
	
	

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//创建 GLFW 窗口
	GLFWwindow* myWindow = glfwCreateWindow(800,600,"My OpenGL Window",NULL,NULL);
	if (myWindow == NULL)
	{
		printf("Open Window Failed-------------------------");
		
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(myWindow);

	//初始化 GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW Failed。。。。。。。。。。");
		
		glfwTerminate();
		return -1;
	}
	//TODO   这一句话运行不运行没有什么区别   ？？？
	//glViewport(1000,1000,800,600);   

	//背面不用渲染  OpenGL 三个点逆时针绘制
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);*/

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//初始化代码（只运行一次，除非你的物体频繁改变）、
	//1.绑定VAO
	glBindVertexArray(VAO);  //OpenGL同时只能处理一个VAO,这句话意思是说我显卡现在就对当前这个VAO进行操作
	
	//顶点缓冲对象（Vertex Buffer Objects）会再GPU内存（通常叫显存）中存储大量顶点     作用是这样可以一次性往GPU发送大量顶点信息
	unsigned int VBO;
	glGenBuffers(1,&VBO);  //该方法可以生成多个VBO  如下：
	/*unsigned int VBO1[100];
	glGenBuffers(100, VBO1);*/

	//2.把顶点数组复制到缓冲中供OpenGL使用
	//OpenGL中有很多缓冲对象类型，顶点缓冲类型（VBO）的类型是GL_ARRAY_BUFFER
	//使用glBindBuffer将新建的缓冲对象绑定到GL_ARRAY_BUFFER目标上
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	//使用glBufferData函数把之前定义的顶点数据复制到缓冲的内存中  第四个参数决定的显卡再接受到数据之后如何处理该数据
	//有3中方式  GL_STATIC_DRAW ：数据不会或几乎不会改变
	//                  GL_DYNAMIC_DRAW ：数据会被改变很多
	//					 GL_STREAM_DRAW ：数据每次绘制时都会改变
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	/*截至目前    我们已经把顶点数据储存在显卡的内存中，用VBO这个顶点缓冲对象管理。*/
	

	unsigned int EBO;
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
	
	Shader* shader = new Shader("vertexSource.txt", "fragmentSource.txt");

	// 3. 设置顶点属性指针（告诉显卡对这些数据怎么操作）
	glVertexAttribPointer(10,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(10);

	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//纹理
	unsigned int TexBuffer1,TexBuffer2;																																
	glGenTextures(1,&TexBuffer1);																					
	//所有即将到来的GL_TEXTURE_2D操作现在都对此纹理对象有效	（官方注释）
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBuffer1); //注意此处不是glBindBuffer					
	//为当前绑定的纹理对象设置环绕，过滤方式																	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);					
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);					
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);				
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);				
	//加载并生成纹理
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("awesomeface.png",&width,&height,&nrChannel,0);
	if (data)
	{
		//当前绑定的纹理对象会被附加上纹理图像。
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//为当前绑定的纹理自动生成所有需要的多级渐远纹理。
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	glGenTextures(1, &TexBuffer2);
	//所有即将到来的GL_TEXTURE_2D操作现在都对此纹理对象有效	（官方注释）	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TexBuffer2); //注意此处不是glBindBuffer					
	//为当前绑定的纹理对象设置环绕，过滤方式																	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	data = stbi_load("container.jpg", &width, &height, &nrChannel, 0);
	if (data)
	{
		//当前绑定的纹理对象会被附加上纹理图像。
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//为当前绑定的纹理自动生成所有需要的多级渐远纹理。
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
	//第二个参数告诉opengl我们要发送多少个矩阵
	//第三个参数为我们是否希望发送的矩阵进行置换（Transpose）OpenGL开发者通常使用一种内部矩阵布局，
	//叫做列主序(Column-major Ordering)布局。GLM的默认布局就是列主序，所以并不需要置换矩阵，我们填GL_FALSE
	//最后一个参数为发送的真正的数据(使用glm进行转换为opengl可以的认识的数据)
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


	//渲染循环
	while (!glfwWindowShouldClose(myWindow))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glDrawArrays(GL_TRIANGLES,0,3);
		
		
		
		
		shader->Use();
		
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		glfwSwapBuffers(myWindow);
		glfwPollEvents();//获取用户输入  //没有这个方法，用户不能拖动，不能对任何用户输入做出处理
		ProcessInput(myWindow);
		
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();//渲染结束释放资源
	return 0;
}//main_End



