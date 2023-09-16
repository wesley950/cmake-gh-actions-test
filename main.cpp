#include <GLFW/glfw3.h>

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "CmakeGHActionsTest", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
