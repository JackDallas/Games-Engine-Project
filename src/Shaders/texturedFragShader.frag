#version 440
in vec2 UV;

out vec3 colour;

uniform sampler2D Tex;

void main(){
    colour = texture( tex, UV ).rgb;
}