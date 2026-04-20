#include <iostream>

#include "Window.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

void ProcessEvents(GLFWwindow* window);

struct UserSettings
{
    const int width = 800, height = 600;
    const std::string title = "Learn OpenGL";
} userSettings;;

int main()
{
    Window window( userSettings.width, userSettings.height, userSettings.title.c_str());

    const char* vertexPath = RESOURCES_PATH"shaders/default.vert";
    const char* fragmentPath = RESOURCES_PATH"shaders/default.frag";

    Shader shader(vertexPath, fragmentPath);

    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
   };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));

    // Links VBO attributes such as coordinates and colors to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window.m_Window))
    {
        // Input
        ProcessEvents(window.m_Window);

        // Rendering
        glClearColor(0.39, 0.58, 0.93, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        VAO1.Bind();
        glDrawArrays(GL_TRIANGLES, 0 , 3);
        // Swap Buffers and Poll Events
        glfwSwapBuffers(window.m_Window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void ProcessEvents(GLFWwindow* window)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

}
