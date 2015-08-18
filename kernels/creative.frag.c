// creative.frag
// Normally computes ambient, diffuse, and specular terms to produce lighting effects
// Or does additional countour mapping based on y values if instructed.

// Already interpolated values.
varying vec3 normal;
varying vec3 curPosition;

uniform float shaderOption;
const float THRESHOLD = 1.0;
void main()
{
    // already have normal and current position in view space.
    // now onto the other two variables.

    // From curPosition to Camera. Camera is origin in view space, so just
    // negate it.
    vec3 camera = normalize( - curPosition);

    // Now to get light. Light is tricky b/c it's still in world coord
    // but now it needs to be in view coord. Process here b/c there wasn't
    // a need for interpolating this point;
    vec3 lightPos = (gl_ModelViewMatrix*gl_LightSource[0].position).xyz; // this thing is 4D so.
    vec3 toLight = normalize(lightPos - curPosition);

    // Now, reflect the light ray over the normal.
    vec3 reflection = normalize(reflect(toLight, normal)); // should still be normalized, but just in case;

    // Calculate the ambient term. Also 4D because everything needs to be combined into 4D.
    vec4 ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;

    // find the diffuse term
    float dot = max(dot(normal, -toLight), 0.0);
    vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * dot;

    // finally, find the specular term
    dot = max(dot(reflection, camera), 0.0);
    vec4 specular = gl_FrontMaterial.specular * gl_LightSource[0].specular
	* pow(dot, gl_FrontMaterial.shininess); // not sure if shininess factor is correct;

    // output
    if (shaderOption > THRESHOLD) {
	gl_FragColor = ambient + diffuse + specular;
    } else {
	float curElev = (curPosition.y + 6.0) * 4.0;
	int level = int(curElev);
	vec4 contour = float(level) * vec4(0.0, .03, 0.01, 1.0);

	// adds a line.
	if (abs(curElev - float(level)) > 0.1) {
	    gl_FragColor = ambient + diffuse + contour;
	} else {
	    gl_FragColor = vec4(0, 0, 0, 1) + ambient;
	}
    }
}
