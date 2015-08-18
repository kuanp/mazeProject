// red.vert

/*
  This simple GLSL vertex shader just sets a color (red)
  to use in the fragment shader and computes the position
  of the vertex (to be interpolated automatically, and used
  in the fragment shader)
*/

// This 'varying' vertex output can be read as an input
// by a fragment shader that makes the same declaration.
varying vec4 exampleVarVec;

void main()
{
    // we want to render the shape using standard OpenGL position transforms.
    gl_Position = ftransform();

    // go cardinal!
    exampleVarVec = vec4(0.85, 0., 0., 1.);
}
