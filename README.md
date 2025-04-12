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

```cpp
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  
```

as input to the first process of the graphics pipeline: the vertex shader

This is done by creating memory of the GPU where we store the vertex data, configure
how OpenGL should interpret the memory and specify how to send the data to the graphics card

__vertex buffer objects (VBO)__

used to manage said memory, this enables us to store a large number of vertices in the GPU's memory

sending data to the GPU from the CPU is kinda slow, so wherever we can we can try to 
send as much data as possible at once. 

`glBufferData` is a function specifically targeted to copy user-defined data into the currently bound buffer.

arg1: type of buffer to copy data into
arg2: size of data in bytes we want to pass to the buffer, can use `sizeof(whatever_you're_drawing)`
arg3: actual data to send 
arg4: specifies how we want the graphics card to manage the given data. This can take 3 forms:

`GL_STREAM_DRAW`: the data is set only once and used by the GPU at most a few times.
`GL_STATIC_DRAW`: the data is set only once and used many times.
`GL_DYANMIC_DRAW`: the data is changed a lot and used many times.

### Vertex Array Objects (VAO)

A vertex array object (also known as a VAO) can be bound just like a vertex buffer object and any 
subesequent vertex attribute calls from that point on will be stored inside the VAO. 

__Core OpenGL _requires_ that we use a VAO so it knows what to do with our vertex inputs.
If we fail to bind a VAO, OpenGL will most likely refuse to draw anything.__

A vertex array object stores the following:

- Calls to `glEnableVertexAttribArray` or `glDisableVertexAttribArray`.
- Vertex attribute configurations via `glVertexAttribPointer`.
- Vertex buffer objects associated with vertex attributes by calls to `glVertexAttribPointer`.

### Element Buffer Objects (EBOs)

An EBO is a buffer, just like a vertex buffer object, that stores indices that OpenGL uses
to decide what vertices to draw. This so called _index drawing_ is exactly the solution to 
our problem.

```cpp
float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  
```

## Shaders

### GLSL 

GLSL is its own C type language specifically for writing shaders. 
It contains useful features specifically targeted at vector and matrix 
manipulation

Example: 

```cpp
#version version_number
in type in_variable_name;
in type in_variable_name;

out type out_variable_name;

uniform type uniform_name;

void main()
{
// process input(s) and do some weird graphics stuff
...
// output processed stuff to output variable
out_variable_name = weird_stuff_we_processed;
```

When we're talking specifically about the vertex shader each input 
variable is also known as a vertex attribute. There is a maximum number 
of vertex attributes we;re allowed to declare limited by the hardware. OpenGl
guarentees that there are always at least 16 4 component vertex attributes 
available, but some hardware may allow for more which you can retrieve 
by querying `GL_MAX_VERTEX_ATTRIBS`:

```cpp
int nrAttributes;
glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
std::cout << "Maximum
```

This often returns the minimum of 16 which should be more
than enough for most purposes.