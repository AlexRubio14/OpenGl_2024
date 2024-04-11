#version 440 core

out vec4 fragColor;

uniform float time;

void main(){
	
	if(time < 2.f){
		fragColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
	else if (time < 4.f){
		fragColor = vec4(0.0, 1.0, 0.0, 1.0);
	}
	else{
		fragColor = vec4(0.0, 0.0, 1.0, 1.0);
	}
}