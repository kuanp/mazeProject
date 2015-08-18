// red.frag

/*
  this just colors everything red!
*/

varying vec4 exampleVarVec;
void main()
{
    // don't do anything interesting, just set the color
    // as this vector was set in the vertex shader.
    gl_FragColor = exampleVarVec;
}
