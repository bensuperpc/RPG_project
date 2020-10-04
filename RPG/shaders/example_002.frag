#ifdef GL_ES
precision mediump float;
#endif
// Source http://glslsandbox.com/e#68140.10
#extension GL_OES_standard_derivatives : enable

#define PI 3.141592
uniform sampler2D currentTexture; 
uniform float time;
//uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {
	float ratio = 0.3;
	float ratio2 = 0.4;
	float wa = ratio2*1.0;
	float w = wa*time+0.0;
	float theta = 0.5*wa*pow(time,2.0);
	mat2 m;
	m[0] = vec2(float(cos(theta)),float(sin(theta)));
	m[1] = vec2(float(-sin(theta)),float(cos(theta)));
	
	vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);
	//vec2 mouse_p = vec2(mouse.x * 2.0 - 1.0, -mouse.y * 2.0 + 1.0);
	float e = 0.005/abs(ratio*1.0-length(p));
	
	//float w2 = log(length(mouse_p));
	//float theta2 = w2*time;
	float theta2 = time;
	mat2 m2;
	m2[0] = vec2(float(cos(theta2)),float(sin(theta2)));
	m2[1] = vec2(float(-sin(theta2)),float(cos(theta2)));
	
	for (float i=0.0;i<5.0;i+=1.0){
		vec2 p2 = m*vec2(cos(2.0*PI/5.0*i),sin(2.0*PI/5.0*i));
		float j = i + 1.0;
		//vec2 p3 = vec2(cos(2.0*PI/5.0*j),sin(2.0*PI/5.0*j));
		float e3 = 0.003/abs(ratio*cos(PI/5.0)-dot(p,p2));
		//float e2 = 0.03/abs(length(p+vec2(cos(2.0*PI/5.0*i),sin(2.0*PI/5.0*i))));
		//e += e2;
		e += e3;
	}
	//gl_FragColor = vec4(vec3(e),1.0);
	//gl_FragColor = gl_Color * texture2D(currentTexture, vec4(vec3(e),0.0));
	gl_FragColor = gl_Color * texture2D(currentTexture, vec2(e,e));
} 
