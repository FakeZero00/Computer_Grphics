#version 330 core
//out_Color: 버텍스 셰이더에서 전달받은 색상 값
//FragColor: 출력할 생상 값으로 프레임 버퍼로 전달됨

in vec3 out_Color;

uniform vec4 tColor;

out vec4 FragColor;

void main()
{
	FragColor = tColor;
}