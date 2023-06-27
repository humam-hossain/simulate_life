#version 330

// input vertex attributes (from vertex shader)
in vec2 fragTexCood;
in vec4 fragColor;

// input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// output fragment Color
out vec4 finalColor;

// note: add here your custom variables

void main()
{
    finalColor = texture(texture0, fragTexCood) * vec4(0,1,0,1);
}