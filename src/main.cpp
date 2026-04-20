#include <iostream>

#include "Window.h"
#include "Shader.h"

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

    // Create our VBO
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    // Bind the VAO to store the related VBO Calls
    glBindVertexArray(VAO);
    // Bind out VBO to openGL GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Give our Buffer Data and tell the gpu how to manage it
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Bind our EBO to openGL GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Give the Buffer the Indices Data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // Tell OpenGL how to interpret out vertex data
    // Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // Enable to vertex attribute giving its location (in the shader layout (location = 0) in vec3 aPos;)
    glEnableVertexAttribArray(0);
    // Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0 , 3);
        // instead if glDrawArrays we use glDrawElements When using an EBO
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
