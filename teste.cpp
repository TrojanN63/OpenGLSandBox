#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    std::cout << "Antes\n";

    if (!glfwInit()) {
        std::cout << "Falhou\n";
        return -1;
    }

    std::cout << "Depois\n";

    glfwTerminate();
}
