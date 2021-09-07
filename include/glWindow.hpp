#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>
#include<unordered_map>
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
    /** Get window id */
    GLFWwindow* window(){return _window;}

    /**
     * Load a window for use, setting hints
    */
    bool loadWindow(int width, int height, std::string windowTitle,std::unordered_map<int,int> hints);
    /** Set window size */
    void setWindowSize(int w,int h);
    /**
     * Safely close the window if not already ready
    */
    ~GLWindow(){
        if(!ready && _window!=nullptr){
            glfwTerminate();
        }
    }
};