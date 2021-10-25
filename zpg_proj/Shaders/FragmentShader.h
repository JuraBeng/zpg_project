const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"in vec4 vertexColor;"
"void main () {"
"     frag_colour = vertexColor;"
"}";
