// texture.frag
// computes texture and hopefully some normal mapping rendering methods.

// Already interpolated values.
varying vec3 normal;
varying vec3 curPosition;

uniform sampler2D tex1;
//uniform sampler2D tex2;
uniform sampler2D texNormal;
uniform float shit;

void main()
{
    // Read in texture1
    vec4 tex1Color = texture2D(tex1, gl_TexCoord[0].st).xyzw;
    vec3 normalV = texture2D(texNormal, gl_TexCoord[0].st).xyz;
   // gl_FragColor = tex1Color;
   // return;
   // gl_FragColor = texture2D(texNormal, gl_TexCoord[0].st).xyzw;
   // gl_FragColor = vec4(shit, shit, shit, 1);
   // return;

    // already have normal and current position in view space.
    // now onto the other two variables.

    // From curPosition to Camera. Camera is origin in view space, so just
    // negate it.
    vec3 camera = normalize( - curPosition);

    // Now to get light. Light is tricky b/c it's still in world coord
    // but now it needs to be in view coord. Process here b/c there wasn't
    // a need for interpolating this point;
    vec3 lightPos = (gl_ModelViewMatrix*gl_LightSource[0].position).xyz; // this thing is 4D so.
    // vec3 lightPos = gl_LightSource[0].position.xyz; // this thing is 4D so.
    vec3 toLight = normalize(lightPos - curPosition);

    // Now, reflect the light ray over the normal.
    vec3 reflection = normalize(reflect(toLight, normalV)); // should still be normalized, but just in case;

    // Calculate the ambient term. Also 4D because everything needs to be combined into 4D.
    vec4 ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;

    // find the diffuse term
    float dot = max(dot(normalV, -toLight), 0.0);
    vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * dot;

    // finally, find the specular term
    dot = max(dot(reflection, camera), 0.0);
    vec4 specular = gl_FrontMaterial.specular * gl_LightSource[0].specular
	* pow(dot, gl_FrontMaterial.shininess);

    // output
    //gl_FragColor = specular;
    gl_FragColor = ambient + diffuse + specular + tex1Color;
}
