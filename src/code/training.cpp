#include "training.h"

Training::Training()
{
}

void Training::render(ImGuiIO io)
{
    if (is_vu_text_a_copier)
    {
        vu_text_a_copier(io);
    }
    if (is_vu_exercice)
    {
        vu_exercice(io);
    }
}

void Training::vu_text_a_copier(ImGuiIO io)
{
    ImGui::Begin("Texte de l'exercice", &is_vu_text_a_copier);
    ImGui::TextWrapped("%s", text_a_copier.c_str());
    ImGui::End();
}

void Training::vu_exercice(ImGuiIO io)
{
    ImGui::Begin("Excercice", &is_vu_text_a_copier);
    ImGui::Text("Chrono et autre");
    ImGui::End();
}

char Training::get_current_char(int index)
{
    return text_a_copier[index];
}

void Training::set_text_a_copier(std::string t)
{
    text_a_copier = t;
}
