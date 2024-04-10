#version 440 core

out vec4 fragColor;

uniform vec1 time;

void main(){
	
	if(time < 2){
		fragColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
	else if (time < 4){
		fragColor = vec4(0.0, 1.0, 0.0, 1.0);
	}
	else{
		fragColor = vec4(0.0, 0.0, 1.0, 1.0);
	}
}