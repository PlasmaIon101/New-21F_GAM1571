
uniform float u_Time;

varying vec4 v_Color;

void main()
{
//	if(gl_FragCoord.x < 400)
//	{
//		//gl_FragColor = vec4(0, cos (u_Time * 10), 0, 1);
//		gl_FragColor = vec4(0, 0, 1, 1);
//	}
//	else if (gl_FragCoord.x > 400)
//	{
//		gl_FragColor = vec4 (0.0, 1.0, 0.0, 1.0);
//	}

	gl_FragColor = v_Color;
	//gl_FragColor = sin(v_Color * u_Time); //u_Time needs to be configured in Mesh in order to work...
}
