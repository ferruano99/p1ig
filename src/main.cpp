#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include "Model.h"
#include <cmath>

#define PI 3.14159265;

void configScene();

void renderScene();

//FUNCIONES CALLBACKS
void funFramebufferSize(GLFWwindow *window, int width, int height);

void funKey(GLFWwindow *window, int key, int scancode, int action, int mods);

void funScroll(GLFWwindow *window, double xoffset, double yoffset);

void funCursorPos(GLFWwindow *window, double xpos, double ypos);


//FUNCIONES OBJECTOS
void drawObject(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawSuelo(glm::mat4 P, glm::mat4 V, glm::mat4 M);


//FUNCIONES SOPORTE DEL HELICÓPTERO
void drawPatas(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawPata(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawSoportePata(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawPataInclinada(glm::mat4 P, glm::mat4 V, glm::mat4 M);


//FUNCIONES CUERPO DEL HELICÓPTERO
void drawCabina(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawCuerpoCabina(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawCristalCabina(glm::mat4 P, glm::mat4 V, glm::mat4 M);


//FUNCIONES ROTOR SUPERIOR
void drawHeliceRotor(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawSoporteRotor(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawRotor(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawAspaRotor(glm::mat4 P, glm::mat4 V, glm::mat4 M);


//FUNCIONES COLA DEL HELICÓPTERO
void drawCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawHeliceCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawConoCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawEstabilizadorCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawToroideCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawAspaCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);


//GENERAR HELICÓPTERO
void drawHelicoptero(glm::mat4 P, glm::mat4 V, glm::mat4 M);


// Shaders
Shaders shaders;

// Modelos
Model plane, cilindro, esfera, cono, torus, triangulo;
// Viewport
int w = 500;
int h = 500;


//zoom de la cámara
float fovy = 40.0;
//Movimiento de la cámara
float alphaX = 0.0;
float alphaY = 0.0;
double lastX = w / 2; //última pos de la X para girar girar el ratón en compás con la imagen (Se comienza con w/2 y h/2 para halalr el centro de la pantalla)
double lastY = h / 2;

//movimiento helicóptero
float Txhelic = 0.0;
float Tzhelic = 0.0;
float Ryhelic = 0.0;


//aspas superior y trasera
int naspas = 4;     //para cambiar las aspas de la hélice superior
float Ryaspa = 0.0; //para rotar el aspa superior
float Rxaspa = 0.0; // para rotar el aspa trasero

//recogida de patas
float Rypata = 0;
float Txpata = 0.0;

//parar hélice
bool parar = false;

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
    glfwSwapInterval(0); //Para las hélices y las animaciones

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
    glfwSetKeyCallback(window, funKey);
    glfwSetScrollCallback(window, funScroll);
    glfwSetCursorPosCallback(window, funCursorPos);


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
    float nplane = 0.1;
    float fplane = 50.0;
    float aspect = (float) w / (float) h;
    glm::mat4 P = glm::perspective(glm::radians(fovy), aspect, nplane, fplane);

    // Matriz V
    float x = 10.0f * glm::cos(glm::radians(alphaY)) * glm::sin(glm::radians(alphaX));
    float y = 10.0f * glm::sin(glm::radians(alphaY));
    float z = 10.0f * glm::cos(glm::radians(alphaY)) * glm::cos(glm::radians(alphaX));

    glm::vec3 eye(x, y, z);
    glm::vec3 center(0, 0, 0.0);
    glm::vec3 up(0, 1, 0);
    glm::mat4 V = glm::lookAt(eye, center, up);

    // Dibujamos la escena
    drawSuelo(P, V, I);
    glm::mat4 Thz = glm::translate(I, glm::vec3(0, 0, Tzhelic));
    glm::mat4 Thx = glm::translate(I, glm::vec3(Txhelic, 0, 0));
    glm::mat4 Rhy = glm::rotate(I, glm::radians(Ryhelic), glm::vec3(0, 1, 0));
    drawHelicoptero(P, V, Thz * Thx * Rhy);
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
    //derecha
    glm::mat4 Ry = glm::rotate(I, glm::radians(Rypata), glm::vec3(0, 0, 1));
    glm::mat4 Tx = glm::translate(I, glm::vec3(Txpata, 0, 0));
    drawPata(P, V, M * Tx * Ry); //Aplicamos la rotación y traslación correspondiente a cada pata

    //izquierda
    glm::mat4 R = glm::rotate(I, glm::radians(180.0f), glm::vec3(0, 1, 0));
    glm::mat4 Txi = glm::translate(I, glm::vec3(-Txpata, 0, 0));
    drawPata(P, V, M * Txi * R * Ry); //La rotamos 180º

}


void drawPata(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    //soporte
    glm::mat4 Td = glm::translate(I, glm::vec3(0.2 * 4.5, -0.2 * 4.5, 0));
    drawSoportePata(P, V, M * Td);

    //pata inclinada
    glm::mat4 T1 = glm::translate(I, glm::vec3(0, 0, 0.2 * 3));
    glm::mat4 T2 = glm::translate(I, glm::vec3(0, 0, -0.2 * 3));
    drawPataInclinada(P, V, M * T1);
    drawPataInclinada(P, V, M * T2);


}

void drawSoportePata(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 R = glm::rotate(I, glm::radians(90.0f), glm::vec3(1, 0, 0));
    glm::mat4 S = glm::scale(I, glm::vec3(0.1, 0.1, 1.2));
    drawObject(cilindro, glm::vec3(0, 0, 1), P, V, M * S * R);
}

void drawPataInclinada(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 R = glm::rotate(I, glm::radians(45.0f), glm::vec3(0, 0, 1));
    glm::mat4 S = glm::scale(I, glm::vec3(0.1, 0.2 * 3, 0.1));
    glm::mat4 T = glm::translate(I, glm::vec3(0.2 * 2.5, -0.2 * 2.5, 0));
    drawObject(cilindro, glm::vec3(0, 0, 1), P, V, M * T * R * S);
}

void drawCabina(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    drawCuerpoCabina(P, V, M);

    glm::mat4 T = glm::translate(I, glm::vec3(0, 0.2 * 1, 0.2 * 5));
    drawCristalCabina(P, V, M * T);

}

void drawCuerpoCabina(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(0.2 * 4, 0.2 * 3, 0.2 * 7));
    drawObject(esfera, glm::vec3(0, 1, 0), P, V, M * S);
}

void drawCristalCabina(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(0.2 * 2, 0.2 * 1.5, 0.2 * 2));
    drawObject(esfera, glm::vec3(1, 0, 1), P, V, M * S);
}

void drawAspaRotor(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(0.2, 0.2 * 6, 0.05));
    glm::mat4 T = glm::translate(I, glm::vec3(0, 0, -6 * 0.2));
    glm::mat4 R = glm::rotate(I, glm::radians(90.0f), glm::vec3(1, 0, 0));
    drawObject(cono, glm::vec3(1, 0, 0), P, V, M * T * R * S);
}


void drawHeliceRotor(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    for (int i = 0; i < naspas; ++i) { //Va cambiando a medida que pulsemos las teclas 1-9.
        glm::mat4 R = glm::rotate(I, glm::radians(i * 360.0f / naspas), glm::vec3(0, 1, 0));
        drawAspaRotor(P, V, M * R);
    }

}

void drawSoporteRotor(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(0.1, 0.1, 0.1));
    drawObject(cilindro, glm::vec3(0, 0, 1), P, V, M * S);
}

void drawRotor(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    //Soporte

    glm::mat4 T = glm::translate(I, glm::vec3(0, 0.2 * 0.5, 0));
    drawSoporteRotor(P, V, M);

    //hélices

    int timer = glfwGetTime() * 1000; //ms
    if (timer % 10 == 0 && !parar) {
        Ryaspa += 3.6;  //cada 10 ms rotamos 3.6º
    }
    glm::mat4 Rhelices = glm::rotate(I, glm::radians(Ryaspa), glm::vec3(0, 1, 0));  //aplicamos rotación
    drawHeliceRotor(P, V, M * Rhelices * T);

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
    int timer = glfwGetTime() * 1000; //ms
    if (timer % 10 == 0 && !parar) {
        Rxaspa -= 1.8;  //cada 10 ms rotamos -1.8º antihorario
    }
    glm::mat4 R = glm::rotate(I, glm::radians(Rxaspa), glm::vec3(1, 0, 0));  //aplicamos rotación
    drawHeliceCola(P, V, M * Tr * R);

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

void drawAspaCola(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(1, 0.2, 0.04));
    glm::mat4 R = glm::rotate(I, glm::radians(90.0f), glm::vec3(0, 1, 0));
    glm::mat4 T = glm::translate(I, glm::vec3(0, -1, 0));
    drawObject(triangulo, glm::vec3(1, 0, 0), P, V, M * S * T * R);
}

void drawHeliceCola(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    for (int i = 0; i < 7; ++i) {
        glm::mat4 Rx = glm::rotate(I, glm::radians(i * 360.0f / 7), glm::vec3(1, 0, 0));
        drawAspaCola(P, V, M * Rx);
    }
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

    //cabina
    glm::mat4 Tca = glm::translate(I, glm::vec3(0, 0.2 * 5, 0));

    //rotor
    glm::mat4 Tr = glm::translate(I, glm::vec3(0, 0.2 * 8.5, 0));

    //patas
    glm::mat4 Tp = glm::translate(I, glm::vec3(0, 0.2 * 5, 0));

    drawPatas(P, V, M * Tp);
    drawCabina(P, V, M * Tca);
    drawRotor(P, V, M * Tr);
    drawCola(P, V, M * Tc * Rc);
}

void funKey(GLFWwindow *window, int key, int scancode, int action, int mods) {
    switch (key) {
        case GLFW_KEY_P:
            if (action == GLFW_PRESS) {
                if (parar) {
                    parar = false;
                } else {
                    parar = true;
                }
            }
            break;
        case GLFW_KEY_Z:
            if (mods == GLFW_MOD_SHIFT) {
                if (Tzhelic + 0.1 <= 7.2)
                    Tzhelic += 0.1;
            } else {
                if (Tzhelic - 0.1 >= -7.2)
                    Tzhelic -= 0.1;
            }
            break;
        case GLFW_KEY_X:
            if (mods == GLFW_MOD_SHIFT) {
                if (Txhelic + 0.1 <= 7.2)
                    Txhelic += 0.1;
            } else {
                if (Txhelic - 0.1 >= -7.2)
                    Txhelic -= 0.1;
            }
            break;
        case GLFW_KEY_R:
            if (mods == GLFW_MOD_SHIFT) {
                Ryhelic += 5;
            } else {
                Ryhelic -= 5;
            }
            break;
        case GLFW_KEY_1:
            if (action == GLFW_PRESS) {
                naspas = 1;
            }
            break;
        case GLFW_KEY_2:
            if (action == GLFW_PRESS) {
                naspas = 2;
            }
            break;

        case GLFW_KEY_3:
            if (action == GLFW_PRESS) {
                naspas = 3;
            }
            break;
        case GLFW_KEY_4:
            if (action == GLFW_PRESS) {
                naspas = 4;
            }
            break;
        case GLFW_KEY_5:
            if (action == GLFW_PRESS) {
                naspas = 5;
            }
            break;
        case GLFW_KEY_6:
            if (action == GLFW_PRESS) {
                naspas = 6;
            }
            break;
        case GLFW_KEY_7:
            if (action == GLFW_PRESS) {
                naspas = 7;
            }
            break;
        case GLFW_KEY_8:
            if (action == GLFW_PRESS) {
                naspas = 8;
            }
            break;
        case GLFW_KEY_9:
            if (action == GLFW_PRESS) {
                naspas = 9;
            }
            break;
        case GLFW_KEY_Q:
            if (action == GLFW_PRESS) {
                //resetear var globales?
                Txhelic = 0.0;
                Tzhelic = 0.0;
                Ryhelic = 0.0;
                Rypata = 0.0;
                Txpata = 0.0;
                naspas = 4;
                parar = false;
            }
            break;
        case GLFW_KEY_UP:
            if (Rypata + 5 <= 45 && Txpata >= 0) {
                Rypata += 5;
            }

            break;
        case GLFW_KEY_DOWN:
            if (Rypata - 5 >= 0 && Txpata >= 0) {
                Rypata -= 5;
            }
            break;
        case GLFW_KEY_LEFT:
            if (Rypata == 45 && Txpata >= -1) {
                Txpata -= 0.05;
            }
            break;
        case GLFW_KEY_RIGHT:
            if (Rypata == 45 && Txpata + 0.05 <= 0) {
                Txpata += 0.05;
            }
            break;
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS) {
                glfwDestroyWindow(window);
            }
            break;
        default:

            break;
    }
}

void funScroll(GLFWwindow *window, double xoffset, double yoffset) {
    if (yoffset < 0) { //Movimiento de la rueda del ratón
        if (fovy < 60)
            fovy += 5;
    } else {
        if (fovy > 10)
            fovy -= 5;
    }
}

void funCursorPos(GLFWwindow *window, double xpos, double ypos) {

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        return; //para que funcione cada vez que estemos pulsando el click izq
    }
    float centroX = w / 2; //Centro de la pantalla en x e y
    float centroY = h / 2;
    float anguloX = 90 / centroX; //hallar cuántos º son 1 pixel
    float anguloY = 90 / centroY;


    if ((alphaY + anguloY * (lastY - ypos)) <= 89 && (alphaY + anguloY * (lastY - ypos)) >= -89) {
        alphaY += anguloY * (lastY - ypos); //se le suma el ángulo y multiplicamos por los píxeles que el ratón no ha sido capaz de coger en el frame anterior
    }
    alphaX += anguloX * (xpos - lastX); //igual

    lastX = xpos; //refrescamos x e y para recoger cuántos píxeles se ha perdido el ratón
    lastY = ypos;

}
