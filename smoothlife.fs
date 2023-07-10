#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

void main()
{
	finalColor = texture(texture0, fragTexCoord)*vec4(0,0.97,0,1);
}
