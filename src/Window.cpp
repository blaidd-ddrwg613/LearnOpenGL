#include "Window.h"

Window::Window(int width, int height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
    {
        if (m_Window == NULL)
        {
            std::cout << "ERROR::Failed To create GLFW Window" << std::endl;
        }
    }

    glfwMakeContextCurrent(m_Window);

    // Load GLAD for OpenGL Functions must be done after creating an OpenGL contex.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR::Failed to initialize GLAD" << std::endl;
    }

    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
}