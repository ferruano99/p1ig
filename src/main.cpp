#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include "Model.h"

void configScene();

void renderScene();

void drawObject(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V, glm::mat4 M, glm::vec3 rgbLines);

void funFramebufferSize(GLFWwindow *window, int width, int height);

void drawSuelo(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawCilindro(glm::mat4 P, glm::mat4 V, glm::mat4 M);


// Shaders
Shaders shaders;

// Modelos
Model plane;
Model cilindro;

// Viewport
int w = 500;
int h = 500;

//Cámara
float desZ = 0.0;
float rotY = 0.0;

int main() {

    // Inicializamos GLFW
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Creamos la ventana
    GLFWwindow *window;
    window = glfwCreateWindow(w, h, "Sesion 5", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Inicializamos GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return false;
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    std::cout << "This system supports OpenGL Version: " << oglVersion << std::endl;

    // Configuramos los CallBacks
    glfwSetFramebufferSizeCallback(window, funFramebufferSize);

    // Entramos en el bucle de renderizado
    configScene();
    while (!glfwWindowShouldClose(window)) {
        renderScene();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void configScene() {

    // Test de profundidad
    glEnable(GL_DEPTH_TEST);
    glPolygonOffset(1.0, 1.0);

    // Shaders
    shaders.initShaders("resources/shaders/vshader.glsl", "resources/shaders/fshader.glsl");

    // Modelos
    plane.initModel("resources/models/plane.obj");
    cilindro.initModel("resources/models/cylinder.obj");

}

void renderScene() {

    // Borramos el buffer de color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Indicamos los shaders a utilizar
    shaders.useShaders();

    // Matriz P
    float fovy = 40.0;
    float nplane = 0.1;
    float fplane = 50.0;
    float aspect = (float) w / (float) h;
    glm::mat4 P = glm::perspective(glm::radians(fovy), aspect, nplane, fplane);

    // Matriz V
    glm::vec3 eye(0, 10, 0);
    glm::vec3 center(0.0, 0.0, 0.0);
    glm::vec3 up(1, 0, 0);
    glm::mat4 V = glm::lookAt(eye, center, up);

    // Dibujamos la escena
    drawSuelo(P, V, I); //R*T se puede cambiar por I
    drawCilindro(P,V,I);

}

void drawObject(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V, glm::mat4 M, glm::vec3 rgbLines) {

    shaders.setMat4("uPVM", P * V * M);

    glEnable(GL_POLYGON_OFFSET_FILL);
    shaders.setVec3("uColor", color);
    model.renderModel(GL_FILL);
    glDisable(GL_POLYGON_OFFSET_FILL);

    shaders.setVec3("uColor", rgbLines);
    model.renderModel(GL_LINE);

}

void drawSuelo(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(7.2, 1.0, 7.2));
    drawObject(plane, glm::vec3(0.5, 0.5, 0.5), P, V, M * S, glm::vec3(0.5 * 0.75, 0.5 * 0.75, 0.5 * 0.75));

}


void drawCilindro(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 T = glm::translate(I, glm::vec3(0,0,0));
    drawObject(cilindro, glm::vec3(1,0,0),P, V, M*T,glm::vec3(0.75,0,0));
}

void funFramebufferSize(GLFWwindow *window, int width, int height) {

    // Configuracion del Viewport
    glViewport(0, 0, width, height);

    // Actualizacion de w y h
    w = width;
    h = height;

}

