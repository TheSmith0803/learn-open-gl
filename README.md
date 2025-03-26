# I am learning open gl

## Hello triangle

vertex data is a collection of vertices. A vertex is a collection of data per 3D coordinate. 

primitives: different calls to hint to opengl what we are going to be drawing to the screen

ex: `GL_POINTS, GL_TRIANGLES` and `GL_LINE_STRIP.`

vertex shader: takes a single vertex, the main purpose of the 
vertex shader is to transform 3D coordinates into different 3D coordinates

The output of the vertex shader is optionally passed to the __geometry shader__

The __geometry shader__ takes as input, a collection of vertices that form a primitive and has the 
ability to generate other shapes by emitting new vertices to form new (or other) primitive(s).

the __primitive assembly__ stage takes as input all the vertices (or vertx if `GL_POINTS` is chosen) from the
vertex (or geometry) shader that form one or more primitives and assembles all the point(s) in the primitive 
shape given; in this case, two triangles.

The output of the primitive assembly stage is then passed on to the __raterization stage__ where it maps the 
resulting primitive(s) to the corresponding pixels on the final screen, resulting in fragments for the 
fragments shader to use.

Before the fragment shaders run, clipping is performed. Clipping discards all fragments that are outside your 
view, increasing performance. 

### Normalized Device Coordinates (NDC)

Once your vertex coordinates have been processed in the vertex shader, they should be in 
normalized device coordinates which is a small space where the x, y and z values vary 
from -1.0 to 1.0

We can sned our defined vertex data:

cpp```float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  ```

as input to the first process of the graphics pipeline: the vertex shader

This is done by creating memory of the GPU where we store the vertex data, configure
how OpenGL should interpret the memory and specify how to send the data to the graphics card

__vertex buffer objects (VBO)__

used to manage said memory, this enables us to store a large number of vertices in the GPU's memory

sending data to the GPU from the CPU is kinda slow, so wherever we can we can try to 
send as much data as possible at once. 