#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "key.h"
#include "define.h"
#include "keyboard.h"
#include <vector>



// Fonction de callback pour les erreurs GLFW
void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Erreur GLFW %d: %s\n", error, description);
}

int main(int, char**)
{
    Keyboard keyboard;

    // Configurer le callback d'erreur GLFW
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Spécifier la version d'OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Nécessaire sur macOS
    #endif

    // Créer la fenêtre GLFW
    GLFWwindow* window = glfwCreateWindow(_DEFAULT_WINDOW_WIDTH_, _DEFAULT_WINDOW_HEIGHT_, "Proto Typer!", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Activer le vsync

    // Initialiser Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Initialiser les backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Boucle principale
    while (!glfwWindowShouldClose(window))
    {
        // Démarrer une nouvelle frame ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Mettre à jour les dimensions du framebuffer
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)display_w, (float)display_h);

        // Votre code d'interface utilisateur ImGui ici
        ImGui::Begin("Menu");
        ImGui::SeparatorText("Clavier");

        if (ImGui::Checkbox("Réglage", &keyboard.is_afficher_settings_)) {
        }
        if (ImGui::Checkbox("Touches", &keyboard.is_afficher_liste_touches)) {
        }
        if (ImGui::Checkbox("Afficher", &keyboard.is_afficher_clavier)) {
        }
        if (ImGui::Button("Charger une clavier")) {
        }
        if (ImGui::Button("Exporter clavier")) {
        }
        ImGui::SeparatorText("Progession");
        ImGui::SeparatorText("Entrainement");

        ImGui::End();

        // Rendre la frame ImGui
        keyboard.render(io);
        ImGui::Render();
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1, 0.1, 0.1, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Échanger les buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Nettoyer
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
