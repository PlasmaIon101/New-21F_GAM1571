attribute vec2 a_Position; //X, Y (position 0)
attribute vec3 a_Colors; //Red, Green, Blue
attribute float a_Alpha; //Transparency Control

uniform vec2 u_Offset;
uniform float u_Time;
uniform float u_Size;

varying vec4 v_Color;

void main()
{
	//float scale = 5;
	
	vec2 pos = a_Position * u_Size + u_Offset;

	//pos.y += sin( u_Offset.x );
	//pos.y += sin( u_Time + a_Position.x/5);

	gl_Position = vec4( pos / 50 - 1, 0.0, 1.0 );

	v_Color = vec4(a_Colors, a_Alpha);

	//gl_Position = vec4( a_Position + u_Offset, 0.0, 1.0 );
}
