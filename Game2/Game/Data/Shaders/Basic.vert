
attribute vec2 a_Position;
attribute vec4 a_Color;
attribute vec2 a_UVCoord;

uniform vec2 u_ObjectTranslation;
uniform vec2 u_ObjectScale; // TODO: pass in as a uniform.
uniform vec2 u_CameraTranslation; // inverse of the camera's position.
uniform vec2 u_ProjectionScale;

varying vec2 v_UVCoord;
varying vec4 v_Color;

void main()
{
    vec2 objectSpacePosition = a_Position;
    vec2 worldSpacePosition = objectSpacePosition*u_ObjectScale + u_ObjectTranslation;
    vec2 viewSpacePosition = worldSpacePosition + u_CameraTranslation;
    vec2 clipSpacePosition = viewSpacePosition * u_ProjectionScale;
    gl_Position = vec4( clipSpacePosition, 0.0, 1.0 );

    vec2 uvScale = vec2( 0.1, 1.0 );
    vec2 uvOffset = vec2( 0.6, 0.0 );

    v_UVCoord = a_UVCoord * uvScale + uvOffset;
    v_Color = a_Color;
}
