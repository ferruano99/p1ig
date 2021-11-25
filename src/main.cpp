#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include "Model.h"
#include <cmath>

#define PI 3.14159265;

void configScene();

void renderScene();

void drawObject(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V, glm::mat4 M);

void funFramebufferSize(GLFWwindow *window, int width, int height);

void drawSuelo(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawPatas(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawCabina(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawRotor(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawHeliceCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawConoCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawEstabilizadorCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawToroideCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);


void drawHelicoptero(glm::mat4 P, glm::mat4 V, glm::mat4 M);


// Shaders
Shaders shaders;

// Modelos
Model plane, cilindro, esfera, cono, torus, triangulo;
// Viewport
int w = 500;
int h = 500;


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
    esfera.initModel("resources/models/sphere.obj");
    cono.initModel("resources/models/cone.obj");
    torus.initModel("resources/models/torus.obj");
    triangulo.initModel("resources/models/triangle.obj");

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
    glm::vec3 eye(8, 2, 0);
    glm::vec3 center(0, 0, 0.0);
    glm::vec3 up(0, 1, 0);
    glm::mat4 V = glm::lookAt(eye, center, up);

    // Dibujamos la escena
    drawSuelo(P, V, I);

/**
 Estas dos son las matrices para el último apartado de la práctica, requiere el cambio de punto de cámara.
    //M1 (cambiar eye a (10, 4, 0))
    glm::mat4 T = glm::translate(I, glm::vec3(0.2 * 18, 0, 0.2 * 18));
    glm::mat4 R = glm::rotate(I, glm::radians(45.0f), glm::vec3(0, 1, 0));
    glm::mat4 S = glm::scale(I, glm::vec3(0.5, 0.5, 0.5));
    glm::mat4 M1 = T * S * R;

    //M2 (cambiar eye a (5, 3, 5))
    glm::mat4 R = glm::rotate(I, glm::radians(90.0f), glm::vec3(0, 1, 0));
    glm::mat4 S = glm::scale(I, glm::vec3(0.2, 0.2, 0.2));
    glm::mat4 M2 = S * R;

    for (int i = 0; i < 14; i += 2) {
        for (int j = 0; j < 14; j += 2) {
            glm::mat4 T = glm::translate(I, glm::vec3(-0.2 * 29 + i, 0, 0.2 * 29 - j));
            drawHelicoptero(P, V, T * M2);
        }

    }
**/
    drawHelicoptero(P, V, I);

}

void drawObject(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    shaders.setMat4("uPVM", P * V * M);

    glEnable(GL_POLYGON_OFFSET_FILL);
    shaders.setVec3("uColor", color);
    model.renderModel(GL_FILL);
    glDisable(GL_POLYGON_OFFSET_FILL);

    shaders.setVec3("uColor", glm::vec3(0.75, 0.75, 0.75) * color);
    model.renderModel(GL_LINE);

}

void drawSuelo(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(7.2, 0.0, 7.2));
    drawObject(plane, glm::vec3(0.5, 0.5, 0.5), P, V, M * S);

}



void drawPatas(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    //pata Izq
    glm::mat4 R = glm::rotate(I, glm::radians(90.0f), glm::vec3(1, 0, 0));
    glm::mat4 S = glm::scale(I, glm::vec3(0.1, 0.1, 1.2));
    glm::mat4 T = glm::translate(I, glm::vec3(.2 * 4.5, 0.1, 0));
    drawObject(cilindro, glm::vec3(0, 0, 1), P, V, M * T * S * R);



    //pata der
    glm::mat4 T2 = glm::translate(I, glm::vec3(-0.2 * 4.5, 0.1, 0));
    drawObject(cilindro, glm::vec3(0, 0, 1), P, V, M * T2 * S * R);


    //patas sustento izq
    glm::mat4 Sarriba = glm::scale(I, glm::vec3(0.1, 0.6, 0.1));
    glm::mat4 Rizq = glm::rotate(I, glm::radians(45.0f), glm::vec3(0, 0, 1));
    glm::mat4 T1izq = glm::translate(I, glm::vec3(0.2 * 2.5, 0.2 * 2.5, 0.2 * 3));
    glm::mat4 T2izq = glm::translate(I, glm::vec3(0.2 * 2.5, 0.2 * 2.5, -0.2 * 3));
    drawObject(cilindro, glm::vec3(0, 0, 1), P, V, M * T1izq * Rizq * Sarriba);
    drawObject(cilindro, glm::vec3(0, 0, 1), P, V, M * T2izq * Rizq * Sarriba);

    //patas sustento der
    glm::mat4 Rder = glm::rotate(I, glm::radians(-45.0f), glm::vec3(0, 0, 1));
    glm::mat4 T1der = glm::translate(I, glm::vec3(-0.2 * 2.5, 0.2 * 2.5, 0.2 * 3));
    glm::mat4 T2der = glm::translate(I, glm::vec3(-0.2 * 2.5, 0.2 * 2.5, -0.2 * 3));
    drawObject(cilindro, glm::vec3(0, 0, 1), P, V, M * T1der * Rder * Sarriba);
    drawObject(cilindro, glm::vec3(0, 0, 1), P, V, M * T2der * Rder * Sarriba);
}

void drawCabina(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    //Cuerpo
    glm::mat4 S1 = glm::scale(I, glm::vec3(0.8, 0.6, 1.5));
    glm::mat4 T1 = glm::translate(I, glm::vec3(0, 1, 0));
    drawObject(esfera, glm::vec3(0, 1, 0), P, V, M * T1 * S1);

    //cabina
    glm::mat4 S2 = glm::scale(I, glm::vec3(0.2 * 2, 0.2 * 1.5, 0.2 * 2));
    glm::mat4 T2 = glm::translate(I, glm::vec3(0, 0.2 * 6, 0.2 * 5));
    drawObject(esfera, glm::vec3(1, 0, 1), P, V, M * T2 * S2);

}

void drawRotor(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    //Soporte
    glm::mat4 S1 = glm::scale(I, glm::vec3(0.1, 0.1, 0.1));
    glm::mat4 T1 = glm::translate(I, glm::vec3(0, 0.2 * 8, 0));
    drawObject(cilindro, glm::vec3(0, 0, 1), P, V, M * T1 * S1);

    //hélices
    glm::mat4 S2 = glm::scale(I, glm::vec3(0.2, 0.2 * 6, 0.05));
    glm::mat4 T2 = glm::translate(I, glm::vec3(0, 0.2 * 8 + 0.1, -0.2 * 6));
    glm::mat4 R = glm::rotate(I, glm::radians(90.0f), glm::vec3(1, 0, 0));
    glm::mat4 Ry90 = glm::rotate(I, glm::radians(90.0f), glm::vec3(0, 1, 0));
    drawObject(cono, glm::vec3(1, 0, 0), P, V, M * T2 * R * S2);
    drawObject(cono, glm::vec3(1, 0, 0), P, V, M * Ry90 * T2 * R * S2);
    drawObject(cono, glm::vec3(1, 0, 0), P, V, M * Ry90 * Ry90 * T2 * R * S2);
    drawObject(cono, glm::vec3(1, 0, 0), P, V, M * Ry90 * Ry90 * Ry90 * T2 * R * S2);

}

void drawCola(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    //cola
    drawConoCola(P, V, M);


    //estabilizador
    glm::mat4 Te = glm::translate(I, glm::vec3(0, 0, -0.2));
    drawEstabilizadorCola(P, V, M * Te);

    //rotor trasero
    glm::mat4 Tr = glm::translate(I, glm::vec3(0, 0, -0.2 * 5));
    //torus
    drawToroideCola(P, V, M * Tr);
    //hélices torus
    drawHeliceCola(P, V, M * Tr);

}

void drawEstabilizadorCola(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(0.4, 0.1, 0.2));
    glm::mat4 Rxe = glm::rotate(I, glm::radians(90.0f), glm::vec3(1, 0, 0));
    glm::mat4 Rye = glm::rotate(I, glm::radians(90.0f), glm::vec3(0, 1, 0));
    drawObject(cilindro, glm::vec3(0, 0, 1), P, V, M * S * Rye * Rxe);
}

void drawConoCola(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(0.1, 2 * 0.2, 5 * 0.2));
    glm::mat4 R = glm::rotate(I, glm::radians(-90.0f), glm::vec3(1, 0, 0));

    drawObject(cono, glm::vec3(1, 1, 0), P, V, M * S * R);

}

void drawToroideCola(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 Rz = glm::rotate(I, glm::radians(90.0f), glm::vec3(0, 0, 1));
    glm::mat4 St = glm::scale(I, glm::vec3(0.4, 0.4, 0.4));
    drawObject(torus, glm::vec3(0, 1, 1), P, V, M * St * Rz);
}

void drawHeliceCola(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    float anguloRotor = 360/7;
    glm::mat4 Rx = glm::rotate(I, glm::radians(anguloRotor), glm::vec3(1, 0, 0));
    glm::mat4 S = glm::scale(I, glm::vec3(1, 0.2, 0.04));
    glm::mat4 R = glm::rotate(I, glm::radians(90.0f), glm::vec3(0, 1, 0));
    glm::mat4 T = glm::translate(I, glm::vec3(0, -1, 0));
    drawObject(triangulo, glm::vec3(1, 0, 0), P, V, M * S * T * R);
    drawObject(triangulo, glm::vec3(1, 0, 0), P, V, M * Rx * S * T * R);
    drawObject(triangulo, glm::vec3(1, 0, 0), P, V, M * Rx * Rx * S * T * R);
    drawObject(triangulo, glm::vec3(1, 0, 0), P, V, M * Rx * Rx * Rx * S * T * R);
    drawObject(triangulo, glm::vec3(1, 0, 0), P, V, M * Rx * Rx * Rx * Rx * S * T * R);
    drawObject(triangulo, glm::vec3(1, 0, 0), P, V, M * Rx * Rx * Rx * Rx * Rx * S * T * R);
    drawObject(triangulo, glm::vec3(1, 0, 0), P, V, M * Rx * Rx * Rx * Rx * Rx * Rx * S * T * R);

}

void funFramebufferSize(GLFWwindow *window, int width, int height) {

    // Configuracion del Viewport
    glViewport(0, 0, width, height);

    // Actualizacion de w y h
    w = width;
    h = height;


}

void drawHelicoptero(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    //Cola
    float anguloCola = atan(0.2) * 180 / PI;
    glm::mat4 Rc = glm::rotate(I, glm::radians(anguloCola), glm::vec3(1, 0, 0));
    glm::mat4 Tc = glm::translate(I, glm::vec3(0, 0.2 * 6, -0.2 * 10));

    drawPatas(P, V, M);
    drawCabina(P, V, M);
    drawRotor(P, V, M);
    drawCola(P, V, M * Tc * Rc);
}

