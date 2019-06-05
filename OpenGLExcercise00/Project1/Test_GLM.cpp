#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

void main2() {
	//声名一个vec4(四维向量)类型的变量 ---
	glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);

	//声名一个mat4(矩阵)类型的变量  
	glm::mat4 trans = glm::mat4(1.0f);
	//将trans变成一个位移矩阵
	trans = glm::translate(trans,glm::vec3(0.0f,1.0f,1.0f));
	//将vec点位移  vec3(0.0f,1.0f,1.0f)
	vec = trans * vec;
	std::cout<<vec.x<<vec.y<<vec.z<<std::endl;
	while (true)
	{

	}
}