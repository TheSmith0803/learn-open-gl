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
std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
```

This often returns the minimum of 16 which should be more
than enough for most purposes.

### Types

GLSL has, like any other programming language, data types for specifying what
kind of variable we want to work with. GLSL has most of the default basic types we 
know from languages like C:
`float, double, uint, and bool`
GLSL also features two container types that we will be using a lot,
namely, `vectors` and `matrices`. 

### Vectors

a vector in GLSL is a 1, 2, 3, or 4 component container for any of the basic
types just mentioned. They can take the following form (`n` represents the number of components):

- `vecn`: the default vector of `n` floats
- `bvecn`: a vector of `n` booleans
- `ivecn`: a vector of `n` integers
- `uvecn`: a vector of `n` unsigned integers
- `dvecn`: a vector of `n` double components

Most of the time we will be using the basic `vecn` since floats are sufficient for most of our purposes.

Components of a vector can be accessed via `vec.x` where `x` is the first component of the vector
You can use `.x, .y, .z` and `.w` to access their different components. (1,2,3, and 4)

so you could do something like this: 

```cpp
vec2 someVec;
vec4 differentVec = someVec.xyxx;
vec3 anotherVec = differentVec.zyw;
vec4 otherVec = someVec.xxxx + anotherVec.yxzy;
```

You can use any combonation of 4 letters to create a new vector (of the same type) as long
as the original vector has those components; it is not allowed to access the .z component
of a vec2 for example. We can also pass vectors as arguments to different vector contructor calls,
reducing the number of arguments required:

```cpp
vec2 vect = vec2(0.5, 0.7);
vec4 result = vec4(vect, 0.0, 0.0);
vec4 otherResult = vec4(result.xyz, 1.0);
```

### Ins and Outs

Shaders are nice little programs of their own, but they are a part of a while and for that reason
we want to have inputs and outputs on the individual shader so that we can move stuff around. 

GLSL defined the `in` and `out` keywords specifically for that putpose. Each shader can specify 
inputs and outputs using those keywords and wherever an output variable matches with an input variable
of the next shader stage, they are passed along. Vertex and fragment shaders differ slightly though.

Vertex shaders __should__ recieve some form of input.
The vertex shader differs in its input, in that it recieves its input straight 
from the vertex data.

_It is also possible to omit the layout (location = 0) specifier and query for 
the attribute locations in your OpenGL code via `glGetAttribLocation`, 
but I'd prefer to set them in the vertex shader. It is easier to 
understand and saves you (and OpenGL) some work._

Fragment shaders on the other hand require a vec4 color output variable,
since the fragment shaders needs to genereate a final output color. If you fail 
to specify an output color in your fragment shader, the color buffer output for those fragments 
will be undefined (which usually means OpenGL will render them as black or white).

__Vertex Shader__

```cpp
#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
  
out vec4 vertexColor; // specify a color output to the fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}
```

__Fragment Shader__

```cpp
#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

void main()
{
    FragColor = vertexColor;
} 
```

In the above shader code, you can see that we declared a `vertexColor` variable
as a `vec4` output that we set in the vertex shader, and we declare a similar `vertexColor`
input in the fragment shader.

Since they both have the same name, `vertexColor` in the fragment shader is linked to the
`vertexColor` in the vertex shader

### Uniforms

Uniforms are another way to pass data from our application on the CPU to the shaders on the GPU.
Uniforms are slightly different than vertex attributes though.

1. Uniforms are global (Uniforms are unique per shader program object and can be accessed from any 
   shader at any point in the program)
2. Whatever you set the uniform value to, they will keep their values until they are reset or updated.


to declare a uniform in GLSL we simply add the `uniform` keyword to a shader with a type and a name.

Example: 

```cpp
#version 330 core
out vec4 FragColor;
  
uniform vec4 ourColor; // we set this variable in the OpenGL code.

void main()
{
    FragColor = ourColor;
}   
```

In this shader program we defclared a uniform `vec4 ourColor` in the fragment shader and set the 
fragment's output color to the content of this uniform value. 

Since uniforms are global variables we can define them in any shader stage we'd like so no need to go through 
the vertex shader again to get something to the fragement shader.
We're not using this uniform in the vertex shader so there is no need to define it there.

_If you declare a uniform that isn't used anywhere in your GLSL code the compiler will 
silently remove the variable from the compiled version which is the cause for several 
frustrating errors; keep this in mind!_

In order to add data to the uniform variable in the fragment shader code above, we need to first find the
index/location of the uniform attribute in the shader.

Once we have the index/location of the uniform, we can update its values. Instead of passing a single 
color to the fragment shader, we can actually change the color over time :ooo

```cpp
float timeValue = glfwGetTime();
float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
glUseProgram(shaderProgram);
glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
```

First we retrieve the running time in seconds via `glfwGetTime()`. 
Then we vary the color in the range of 0.0 - 1.0 by using the `sin` function and store the result in 
`greenValue`.

Then we query for the location of the ourColor uniform using `glGetUniformLocation`. 
We supply the shader program and the name of the uniform (that we want to retrieve the location from) 
to the query function. 

If `glGetUniformLocation` returns -1, it could not find the location. 
Lastly we can set the uniform value using the `glUniform4f` function. 
Note that finding the uniform location does not require you to use the shader program first, 
but updating a uniform does require you to first use the program (by calling `glUseProgram`), 
because it sets the uniform on the currently active shader program.

If you were wondering why we keep setting that `f` next to each float, it is opengls way of 
telling C that that value is a float (i think).It is called a "postfix".

Whenever you want to configure an option of OpenGL simply pick the overloaded function that corresponds 
with your type. In our case we want to set 4 floats of the uniform individually
so we pass our data via glUniform4f

### More Attributes!!!

