/*
 * creative.vert
*/
//Interpolation candidates.
varying vec3 normal;
varying vec3 curPosition;

void main()
{
    // Everything needed to calculate the phong value needs to be in
    // ModelView space (eye space? not screen space).
    // And the variables that needs to be calculated here

    // We need glNormalMatrix because normal is technically flipping some
    // of coordinates. Math online says so.. :P It does project
    // into model-view space tho. This value will be interpolated.
    normal = normalize(gl_NormalMatrix * gl_Normal);

    // And need current location from model-view space. This value will get interpolated.
    curPosition = (gl_ModelViewMatrix * gl_Vertex).xyz;

    // Standard output
    gl_Position = ftransform();
}
