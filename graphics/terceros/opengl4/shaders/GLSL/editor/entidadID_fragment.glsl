#version 420 core


//in vec3 fragPos;
in float _id;


out float id;
//out vec4 id;
void main(){            
	//id=_id;
	id=vec4(_id,0,0,1.0);
} 