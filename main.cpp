#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vs_Src = "#version 330 core \n"
                     "layout (location = 0) in vec2 aPosition; \n"
                     "layout (location = 1) in vec3 aColor; \n"
                     "out vec3 vColor; \n"
                     "void main() {\n"
                     "gl_Position = vec4(aPosition, 0, 1); \n"
                     "vColor = aColor; \n"
                     "} \n"
        ;

const char* fs_Src = "#version 330 core \n"
                     "in vec3 vColor; \n"
                     "out vec4 oColor; \n"
                     "void main() { \n"
                     "oColor = vec4(vColor, 1); \n"
                     "} \n";

unsigned compileShader(int type, const char* src) {
    unsigned shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
}

unsigned linkProgram(unsigned vs, unsigned fs) {
    unsigned program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    return program;
}

void framebuffer_size_callback(GLFWwindow*, int w, int h) {
    glViewport(0, 0, w, h);
}

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "CmakeGHActionsTest", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGL();

    unsigned vao, vbo, ebo;
    unsigned program, vs, fs;

    float vertices[] = {
            -.5f, -.5f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, -.5f, 0.0f, 0.0f, 1.0f,
    };
    unsigned indices[] = {
            0, 1, 2
    };

     glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    vs = compileShader(GL_VERTEX_SHADER, vs_Src);
    fs = compileShader(GL_FRAGMENT_SHADER, fs_Src);
    program = linkProgram(vs, fs);

    glUseProgram(program);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void*)(sizeof(float)*2));

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    glDeleteProgram(program);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);

    glfwTerminate();
    return 0;
}
