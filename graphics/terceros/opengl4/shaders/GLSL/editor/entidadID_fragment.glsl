#version 420 core


//in vec3 fragPos;
flat in int _id;


//out float id;
out vec4 fragColor;
void main(){            
	//id=_id;
	fragColor=vec4(float(_id & 0xff) / 255.0, float((_id >> 8) & 0xff) / 255.0, float((_id >> 16) & 0xff) / 255.0,1.0);

	//fragColor=vec4(float(_id & 0xff) / 255.0, 0, 1.0, 1.0);
} 