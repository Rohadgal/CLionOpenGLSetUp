#include "external/glew-2.1.0/include/GL/glew.h"
#include "external/glfw-3.4/include/GLFW/glfw3.h"
#include <cstdio>
#include <cmath>
#include "Shader.h"

GLFWwindow* window;

GLfloat vertices[] = {

    -0.5f,-0.5f, 0.0f,  1.0f,0.0f, 0.0f,
     0.5f,-0.5f, 0.0f,  0.0f,1.0f, 0.0f,
     0.0f, 0.5f, 0.0f,  0.0f,0.0f, 1.0f
    //-0.5f,-0.5f, 0.0f,  // Bottom Left
    // 0.5f,-0.5f, 0.0f,  // Bottom Right
    // 0.5f, 0.5f, 0.0f,   // Up Right

    // 0.5f, 0.5f, 0.0f,   // Up Right
    //-0.5f, 0.5f, 0.0f, // Up Left
    //- 0.5f,-0.5f, 0.0f  // Bottom Left
};

//const char* vertexShaderData =
//"#version 460 core\n"
//"layout (location=0) in vec3 aPos;\n"
//"layout (location=1) in vec3 aColor;\n"
//"out vec3 ourColor;\n"
//"void main()\n"
//"{\n"
//    "ourColor = aColor;\n"
//"   gl_Position = vec4(aPos, 1.0f);\n"
//"}\0";
//
//const char* fragmentShaderData =
//"#version 460 core\n"
//"out vec4 FragColor;\n"
//"in vec3 ourColor;\n"
//"uniform float xColor;\n"
//"uniform float yColor;\n"
////"uniform float zColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(xColor * ourColor.x, yColor * ourColor.y, ourColor.z, 1.0f);\n"
//"}\0";

//GLuint indexes[] = {
//    0,1,2,
//    2,3,0
//};

int main(){
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Initialize version 4.6 */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "First Triangle", nullptr, nullptr);
    if (!window)
    {
        printf("Failed to initialize Window\n");
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Check Glew
    if (glewInit() != GLEW_OK) {
        printf("Failed to initialize Glew\n");
        glfwTerminate();
    }


    /* Buffers */
    GLuint vbo, vao /*ebo*/;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    //glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    /* Position Attribute */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    /* Color Attribute */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    /* Shader */
    Shader myShader("C:/Users/Adrian/Documents/GitHub/OpenGL/res/Shader/vertexShader.glsl", "C:/Users/Adrian/Documents/GitHub/OpenGL/res/Shader/fragmentShader.glsl");

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    ////// get version info
    //const GLubyte* renderer = glGetString(GL_RENDERER);
    //const GLubyte* version = glGetString(GL_VERSION);
    //printf("Renderer: %s\n", renderer);
    //printf("OpenGL version supported %s\n", version);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /*Update*/

        /* Use this to change color over time*/
        float time = glfwGetTime();
        float xValue = std::cos(time) / 2.0f + 0.5f;
        float yValue = std::sin(time) / 2.0f + 0.5f;
        //glUniform1f(glGetUniformLocation(program, "xColor"), xValue);
        //glUniform1f(glGetUniformLocation(program, "yColor"), yValue);
        //glUniform1f(glGetUniformLocation(program, "zColor"), 0.3f);
        myShader.setFloat("xColor", xValue);
        myShader.setFloat("yColor", yValue);

        /* Render here */
        // Wipe drawing surface clear
        glClearColor(0.2f, 0.1f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //glUseProgram(program);
        myShader.use();
        glBindVertexArray(vao);

        // Draw points 0 - 6 from the currently bound vao with current in-use shader
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //glBegin(GL_TRIANGLES);
        //glColor3f(0.5f, 0.5f, 0.0f);
        //glVertex2f(-0.5f, -0.5f);
        //glVertex2f(0.0f, 0.5f);
        //glVertex2f(0.5f, -0.5f);

        /* Commented this part because the video tutorial does not have it*/
        //glEnd();

        /* Poll for and process events */
        // Update other events like input handling
        glfwPollEvents();

        /* Swap front and back buffers */
        // put stuff we've been drawing onto the display
        glfwSwapBuffers(window);


    }

    // clear
    glfwDestroyWindow(window);

    // close GL context and any other GLFW resources
    glfwTerminate();
    return 0;
}



// // tell GL to only draw onto a plixel if the shape is closer to the viewer
//glEnable(GL_DEPTH_TEST); // enable depth-testing
//glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

// GLfloat points[] = {
//     0.0f, 0.5f, 0.0f,
//     0.5f, -0.5f, 0.0f,
//     -0.5f, -0.5f, 0.0f
// };

// GLuint vbo = 0;
// glGenBuffers(1, &vbo);
// glBindBuffer(GL_ARRAY_BUFFER, vbo);
// glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

// GLuint vao = 0;
// glGenVertexArrays(1, &vao);
// glBindVertexArray(vao);
// glEnableVertexAttribArray(0);
// glBindBuffer(GL_ARRAY_BUFFER, vbo);
// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);