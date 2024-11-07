#include "key.h"
#include "imgui.h"
#include <vector>
#include <algorithm> // Pour std::copy


Key::Key(const std::string& lbl, const std::vector<int>& positions){
    label = lbl;
    positions_touche = positions;
    position_label = {positions[0], positions[1]};
}

Key::Key() {}

std::string Key::get_label()
{
    return label;
}

void Key::set_couleur_remplissage(ImVec4 color){ couleur_remplissage = color;}
void Key::set_couleur_attente(ImVec4 color){ couleur_attente = color;}
void Key::set_couleur_presse(ImVec4 color){ couleur_presse = color;}
void Key::set_couleur_text(ImVec4 color){ couleur_text = color;}

int Key::nombre_de_char(){ return chars.size();}

char Key::get_char_by_index(int index){ return chars[index];}
std::vector<int> Key::get_modifiers_by_index(int index){ return key_modifier_by_char[index];}

void Key::render(
    ImGuiIO io,
    ImVec2 position_fenetre,
    float bordure_touche,
    ImVec2 taille_de_touche,
    float bordure_clavier,
    float bordure_clavier_top_,
    ImDrawList *draw_list)
{
    ImVec2 position_point = _INITIALISE_IMVEC2_;

    if (positions_touche.size()<=2){
        ImVec2 coin_TL = ImVec2(
            position_fenetre.x + bordure_touche + taille_de_touche.x * positions_touche[0] + bordure_clavier ,
            position_fenetre.y + bordure_touche + taille_de_touche.y * positions_touche[1] + bordure_clavier + bordure_clavier_top_
        );
        ImVec2 coin_BR = ImVec2(
            coin_TL.x - bordure_touche*2 + taille_de_touche.x,
            coin_TL.y - bordure_touche*2 + taille_de_touche.y
        );
        draw_list->AddRectFilled(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(couleur_remplissage));
        position_point = ImVec2(
            position_fenetre.x + (taille_de_touche.x/2) + taille_de_touche.x * positions_touche[0] + bordure_clavier ,
            position_fenetre.y + (taille_de_touche.y/2) + taille_de_touche.y * positions_touche[1] + bordure_clavier + bordure_clavier_top_
        );
    }
    else {

        for (size_t i = 0; i < positions_touche.size()/2; i++)
        {
            bool is_a_cote_D = false;
            bool is_a_cote_B = false;
            bool is_a_cote_DB = false;
            for (size_t j = 0; j < positions_touche.size()/2; j++)
            {
                // Droite
                if (positions_touche[i*2]   == positions_touche[j*2]+1   && positions_touche[i*2+1] == positions_touche[j*2+1]) 
                {
                    ImVec2 coin_TL = ImVec2(
                        position_fenetre.x + taille_de_touche.x * positions_touche[i*2] + bordure_clavier ,
                        position_fenetre.y + bordure_touche + taille_de_touche.y * positions_touche[i*2+1] + bordure_clavier + bordure_clavier_top_
                    );
                    ImVec2 coin_BR = ImVec2(
                        coin_TL.x - bordure_touche + taille_de_touche.x,
                        coin_TL.y - bordure_touche*2 + taille_de_touche.y
                    );
                    draw_list->AddRectFilled(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(couleur_remplissage));
                    is_a_cote_D = true;
                }
                // Gauche
                if (positions_touche[i*2]   == positions_touche[j*2]-1   && positions_touche[i*2+1] == positions_touche[j*2+1]) 
                {
                    ImVec2 coin_TL = ImVec2(
                        position_fenetre.x + bordure_touche + taille_de_touche.x * positions_touche[i*2] + bordure_clavier ,
                        position_fenetre.y + bordure_touche + taille_de_touche.y * positions_touche[i*2+1] + bordure_clavier + bordure_clavier_top_
                    );
                    ImVec2 coin_BR = ImVec2(
                        coin_TL.x - bordure_touche + taille_de_touche.x,
                        coin_TL.y - bordure_touche*2 + taille_de_touche.y
                    );
                    draw_list->AddRectFilled(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(couleur_remplissage));
                }
                // Haut
                if (positions_touche[i*2+1] == positions_touche[j*2+1]-1 && positions_touche[i*2]   == positions_touche[j*2]) 
                {
                    ImVec2 coin_TL = ImVec2(
                        position_fenetre.x + bordure_touche + taille_de_touche.x * positions_touche[i*2] + bordure_clavier ,
                        position_fenetre.y + bordure_touche + taille_de_touche.y * positions_touche[i*2+1] + bordure_clavier + bordure_clavier_top_
                    );
                    ImVec2 coin_BR = ImVec2(
                        coin_TL.x - bordure_touche*2 + taille_de_touche.x,
                        coin_TL.y - bordure_touche + taille_de_touche.y
                    );
                    draw_list->AddRectFilled(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(couleur_remplissage));
                }
                // Bas
                if (positions_touche[i*2+1] == positions_touche[j*2+1]+1 && positions_touche[i*2]   == positions_touche[j*2]) 
                {
                    ImVec2 coin_TL = ImVec2(
                        position_fenetre.x + bordure_touche + taille_de_touche.x * positions_touche[i*2] + bordure_clavier ,
                        position_fenetre.y + taille_de_touche.y * positions_touche[i*2+1] + bordure_clavier + bordure_clavier_top_
                    );
                    ImVec2 coin_BR = ImVec2(
                        coin_TL.x - bordure_touche*2 + taille_de_touche.x,
                        coin_TL.y - bordure_touche + taille_de_touche.y
                    );
                    draw_list->AddRectFilled(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(couleur_remplissage));
                    is_a_cote_B = true;
                }
                // Diag Bas Droite
                if (positions_touche[i*2+1] == positions_touche[j*2+1]+1 && positions_touche[i*2] == positions_touche[j*2]+1) 
                {
                    is_a_cote_DB = true;
                }
                if (is_a_cote_B && is_a_cote_D && is_a_cote_DB){
                    // Remplire le trou au milieu
                    ImVec2 coin_TL = ImVec2(
                        position_fenetre.x - bordure_touche + taille_de_touche.x * positions_touche[i*2]+1 + bordure_clavier - 1,
                        position_fenetre.y - bordure_touche + taille_de_touche.y * positions_touche[i*2+1]+1 + bordure_clavier  + bordure_clavier_top_ -1
                    );
                    ImVec2 coin_BR = ImVec2(
                        coin_TL.x + bordure_touche*2,
                        coin_TL.y + bordure_touche*2
                    );
                    draw_list->AddRectFilled(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(couleur_remplissage));
                }
            }
        }
        position_point = ImVec2(
            position_fenetre.x + (taille_de_touche.x/2) + taille_de_touche.x * position_label[0] + bordure_clavier ,
            position_fenetre.y + (taille_de_touche.y/2) + taille_de_touche.y * position_label[1] + bordure_clavier + bordure_clavier_top_
        );
    }
    ImVec2 text_size = ImGui::CalcTextSize(label.c_str());
    ImVec2 text_pos = ImVec2(
        position_point.x - (text_size.x/2),
        position_point.y - (text_size.y/2)
    );
    draw_list->AddText(text_pos, ImGui::ColorConvertFloat4ToU32(couleur_text), label.c_str());
}
void Key::vue_reglages(ImGuiIO& io)  // Utilisation de la référence pour éviter une copie
{
    if(is_afficher_reglage){
        ImGui::Begin(label.c_str(), &is_afficher_reglage);

        ImGui::Text("Modifier les paramètres de la touche :");

        ImGui::SeparatorText("Modifier le label :");
        char buffer[256];
        strncpy(buffer, label.c_str(), sizeof(buffer));
        buffer[sizeof(buffer) - 1] = '\0';
        if (ImGui::InputText("Label", buffer, sizeof(buffer))) {
            label = buffer;  // Mettre à jour `label` si le texte a été modifié
        }
        if (ImGui::Button("Valider")) {
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear")) {
            label = "Sans nom";  // Mettre à jour `label` si le texte a été modifié
        }
        ImGui::SeparatorText("Modifier les couleur de la touche :");
        
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur remplissage",    (float*)&couleur_remplissage))  {}
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur attente",        (float*)&couleur_attente))      {}
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur pressé",         (float*)&couleur_presse))       {}
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur texte",          (float*)&couleur_text))         {}

        ImGui::SeparatorText("Modifier la position et la forme");
        // Affichage et modification des paires de coordonnées
        for (size_t i = 0; i < positions_touche.size(); i += 2) {
            ImGui::PushID(i);  // Assigner un ID unique pour chaque champ pour éviter les conflits

            int x = positions_touche[i];
            int y = positions_touche[i + 1];

            ImGui::SetNextItemWidth(100.0f);
            ImGui::InputInt("X", &x);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(100.0f);
            ImGui::InputInt("Y", &y);

            // Mettre à jour les valeurs dans le vecteur
            positions_touche[i] = x;
            positions_touche[i + 1] = y;

            // Pick la place de la touche 
            ImGui::SameLine();
            if (ImGui::Button("Pick")) {
                // TO DO 
            }

            // Ajouter un bouton pour supprimer la paire
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, _DEFAULT_COLOR_WARNING_BUTTON_);
            if (ImGui::Button("Supprimer")) {
                // Supprimer la paire (x, y) en utilisant erase()
                positions_touche.erase(positions_touche.begin() + i, positions_touche.begin() + i + 2);

                // Revenir en arrière dans l'index pour éviter de sauter l'élément suivant
                i -= 2;
            }
            ImGui::PopStyleColor(1); 
            ImGui::PopID();
        }

        // Bouton pour ajouter une nouvelle paire de coordonnées
        if (ImGui::Button("Ajouter une paire de coordonnées")) {
            positions_touche.push_back(0);  // Ajouter x = 0 par défaut
            positions_touche.push_back(0);  // Ajouter y = 0 par défaut
        }

        ImGui::End();
    }
}
