const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec4 vc;"
"out vec4 vertexColor;"
"uniform mat4 modelMatrix;"
"void main () {"
"     gl_Position = modelMatrix * vec4 (vp, 1.0);"
"     vertexColor = vc;"
"}";
