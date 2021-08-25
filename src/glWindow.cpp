#include <glWindow.hpp>
#include <string>
bool GLWindow::loadWindow(int width, int height, std::string title)
{
    if (glfwInit() == GLFW_FALSE) {
        return (ready = false);
    }
    y = title;
    _window = glfwCreateWindow(width, height, y.c_str(), nullptr, nullptr);
    if (!_window) {
        glfwTerminate();
        return (ready = false);
    }
    glfwMakeContextCurrent(_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();

        return (ready = false);
    }
    return (ready=true);
}