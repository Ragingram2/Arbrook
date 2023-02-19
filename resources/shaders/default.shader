#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
out vec4 pos;
void main()
{
	gl_Position = position;
	pos = gl_Position;
}

#shader fragment
#version 330 core

in vec4 pos;

void main()
{
	gl_FragColor = pos;
}