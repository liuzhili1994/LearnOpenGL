#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

void main2() {
	//����һ��vec4(��ά����)���͵ı��� ---
	glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);

	//����һ��mat4(����)���͵ı���  
	glm::mat4 trans = glm::mat4(1.0f);
	//��trans���һ��λ�ƾ���
	trans = glm::translate(trans,glm::vec3(0.0f,1.0f,1.0f));
	//��vec��λ��  vec3(0.0f,1.0f,1.0f)
	vec = trans * vec;
	std::cout<<vec.x<<vec.y<<vec.z<<std::endl;
	while (true)
	{

	}
}