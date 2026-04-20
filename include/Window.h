#pragma once

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window
{
public:
    GLFWwindow* m_Window;
    int m_Width{}, m_Height{};
    std::string m_Title;

    Window(int width, int height, const char* title);
    ~Window();
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};