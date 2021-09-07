#include <glWindow.hpp>
#include <string>
bool GLWindow::loadWindow(int width, int height, std::string title,std::unordered_map<int,int> hints)
{
    if (glfwInit() == GLFW_FALSE) {
        return (ready = false);
    }
    // set the title
    windowTitle = title;
    for(auto [a,b]:hints){
        glfwWindowHint(a,b);
    }
    
    _window = glfwCreateWindow(width, height, windowTitle.c_str(), nullptr, nullptr);
    if (!_window) {
        glfwTerminate();
        return (ready = false);
    }
    glfwMakeContextCurrent(_window);

    // a callback to resize the window dynamically
    glfwSetWindowSizeCallback(_window, [](GLFWwindow* window,int w,int h)->void{
        glViewport(0,0,w,h);
    });
    // load in opengl functions with glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();

        return (ready = false);
    }
    return (ready=true);
}

void GLWindow::setWindowSize(int w,int h){
    glfwSetWindowSize(_window,w,h);
}