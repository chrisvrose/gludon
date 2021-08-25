#include <glad/glad.h>
#include <iostream>
#include <string>

#include <GLFW/glfw3.h>

class GLWindow {
private:
    bool ready;
    std::string windowTitle;
    GLFWwindow* _window;

public:

    GLWindow()
    {
        ready = false;
        _window = nullptr;
    }
    GLFWwindow* window(){return _window;}

    bool loadWindow(int, int, std::string);

    /**
     * Safely close the window if not already ready
    */
    ~GLWindow(){
        if(!ready && _window!=nullptr){
            glfwTerminate();
        }
    }
};