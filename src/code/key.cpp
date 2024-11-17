/**
 *   _  __          
 *  | |/ /          
 *  | ' / ___ _   _ 
 *  |  < / _ \ | | |
 *  | . \  __/ |_| |
 *  |_|\_\___|\__, |
 *             __/ |
 *            |___/ 
 * 
 * @file key.cpp
 * @brief 
 * 
 * @author Mathurin Champémont
 * @date 16 novembre 2024
 *
 * @version 1.0.0
 *
 * @copyright MIT License
 *
 * @note 
 */

#include "key.h"
#include "imgui.h"
#include "define.h"
#include <vector>
#include <string>
#include <utility> // Pour std::pair
#include <algorithm> // Pour std::copy
#include <nlohmann/json.hpp>


Key::Key() {}

Key::Key(const std::vector<_coordinate_> pos_key,const int pos_lbl)
{
    position_key = pos_key;
    position_label = pos_lbl;
}

void Key::add_char(const std::string& lbl, const char c, const int m1 ,const int m2)
{
    list_labels.push_back(lbl);
    list_chars.push_back(c);
    list_modifier_1.push_back(m1);
    list_modifier_2.push_back(m2);
}
void Key::add_char(const char c, const int m1 ,const int m2)
{
    list_labels.push_back(std::string(1, c));
    list_chars.push_back(c);
    list_modifier_1.push_back(m1);
    list_modifier_2.push_back(m2);
}
void Key::add_position(const _coordinate_ pos)
{
    position_key.push_back(pos);
}

char Key::get_char_by_index(int i)
{
    if (i >= list_chars.size())
    {
        throw std::out_of_range("La liste des caractères ne contient pas d'éléments à l'index i");
    }
    return list_chars[i];
}
std::string Key::get_labels_by_index(int i)
{
    if (i >= list_labels.size())
    {
        throw std::out_of_range("La liste des labels ne contient pas d'éléments à l'index i");
    }
    return list_labels[i];
}
int Key::get_mod_1_by_index(int i)
{
    if (i >= list_modifier_1.size())
    {
        throw std::out_of_range("La liste des premiers modificateurs ne contient pas d'éléments à l'index i");
    }
    return list_modifier_1[i];
}
int Key::get_mod_2_by_index(int i)
{
    if (i >= list_modifier_2.size())
    {
        throw std::out_of_range("La liste des seconds modificateurs ne contient pas d'éléments à l'index i");
    }
    return list_modifier_2[i];
}
int Key::get_nb_char()
{
    if (list_chars.size() == list_labels.size() == list_modifier_1.size() == list_modifier_2.size())
    {
        return list_chars.size();
    }
    else 
    {
        throw std::logic_error("Toutes les listes n'ont pas la même taille");
    }
}

void Key::set_color_idle(ImVec4 color){ color_idle = color;}
void Key::set_color_waiting(ImVec4 color){ color_waiting = color;}
void Key::set_couleur_presse(ImVec4 color){ color_pressed = color;}
void Key::set_couleur_text(ImVec4 color){ color_text = color;}

void Key::set_finger_assignment(int f)
{
    if (f >= _NUMBER_OF_FINGERS)
    {
        throw std::out_of_range("Il est impossible de choisir un doigt par une valeur autre que de 0 à 4");
    }
    finger_assignment = f;
}

void Key::set_lbl_position(int i)
{
    if (i >= position_key.size())
    {
        throw std::out_of_range("Il est impossible de choisir un index qui n'est pas dans la liste des positions");
    }
    position_label = i;
}

void Key::render(
    ImGuiIO& io,
    ImVec2 pos_win,
    float key_border,
    ImVec2 key_size,
    float keyboard_border,
    float keyboard_border_top,
    ImDrawList* draw_list,
    int i_of_list)
{
    ImVec2 position_point = _INITIALISE_IMVEC2_;
    ImVec4 color = color_idle; // TODO pour modifier en fonction de l'état de la touche

    if (position_key.size()<=1){
        ImVec2 coin_TL = ImVec2(
            pos_win.x + key_border + key_size.x * position_key[0].x + keyboard_border ,
            pos_win.y + key_border + key_size.y * position_key[0].y + keyboard_border + keyboard_border_top
        );
        ImVec2 coin_BR = ImVec2(
            coin_TL.x - key_border*2 + key_size.x,
            coin_TL.y - key_border*2 + key_size.y
        );
        draw_list->AddRectFilled(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(color));
        position_point = ImVec2(
            pos_win.x + (key_size.x/2) + key_size.x * position_key[0].x + keyboard_border ,
            pos_win.y + (key_size.y/2) + key_size.y * position_key[0].y + keyboard_border + keyboard_border_top
        );
    }
    else {
        for (size_t i = 0; i < position_key.size(); i++)
        {
            bool is_a_cote_D = false;
            bool is_a_cote_B = false;
            bool is_a_cote_DB = false;
            for (size_t j = 0; j < position_key.size(); j++)
            {
                // Droite
                if (position_key[i].x   == position_key[j].x+1   && position_key[i].y == position_key[j].y) 
                {
                    ImVec2 coin_TL = ImVec2(
                        pos_win.x + key_size.x * position_key[i].x + keyboard_border ,
                        pos_win.y + key_border + key_size.y * position_key[i].y + keyboard_border + keyboard_border_top
                    );
                    ImVec2 coin_BR = ImVec2(
                        coin_TL.x - key_border + key_size.x,
                        coin_TL.y - key_border * 2 + key_size.y
                    );
                    draw_list->AddRectFilled(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(color));
                    is_a_cote_D = true;
                }
                // Gauche
                if (position_key[i].x   == position_key[j].x-1   && position_key[i].y == position_key[j].y) 
                {
                    ImVec2 coin_TL = ImVec2(
                        pos_win.x + key_border + key_size.x * position_key[i].x + keyboard_border ,
                        pos_win.y + key_border + key_size.y * position_key[i].y + keyboard_border + keyboard_border_top
                    );
                    ImVec2 coin_BR = ImVec2(
                        coin_TL.x - key_border + key_size.x,
                        coin_TL.y - key_border*2 + key_size.y
                    );
                    draw_list->AddRectFilled(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(color));
                }
                // Haut
                if (position_key[i].y == position_key[j].y-1 && position_key[i].x   == position_key[j].x) 
                {
                    ImVec2 coin_TL = ImVec2(
                        pos_win.x + key_border + key_size.x * position_key[i].x + keyboard_border ,
                        pos_win.y + key_border + key_size.y * position_key[i].y + keyboard_border + keyboard_border_top
                    );
                    ImVec2 coin_BR = ImVec2(
                        coin_TL.x - key_border*2 + key_size.x,
                        coin_TL.y - key_border + key_size.y
                    );
                    draw_list->AddRectFilled(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(color));
                }
                // Bas
                if (position_key[i].y == position_key[j].y+1 && position_key[i].x   == position_key[j].x) 
                {
                    ImVec2 coin_TL = ImVec2(
                        pos_win.x + key_border + key_size.x * position_key[i].x + keyboard_border ,
                        pos_win.y + key_size.y * position_key[i].y + keyboard_border + keyboard_border_top
                    );
                    ImVec2 coin_BR = ImVec2(
                        coin_TL.x - key_border*2 + key_size.x,
                        coin_TL.y - key_border + key_size.y
                    );
                    draw_list->AddRectFilled(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(color));
                    is_a_cote_B = true;
                }
                // Diag Bas Droite
                if (position_key[i].y == position_key[j].y+1 && position_key[i].x == position_key[j].x+1) 
                {
                    is_a_cote_DB = true;
                }
                if (is_a_cote_B && is_a_cote_D && is_a_cote_DB){
                    // Remplire le trou au milieu
                    ImVec2 coin_TL = ImVec2(
                        pos_win.x - key_border + key_size.x * position_key[i].x+1 + keyboard_border - 1,
                        pos_win.y - key_border + key_size.y * position_key[i].y+1 + keyboard_border  + keyboard_border_top -1
                    );
                    ImVec2 coin_BR = ImVec2(
                        coin_TL.x + key_border*2,
                        coin_TL.y + key_border*2
                    );
                    draw_list->AddRectFilled(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(color));
                }
            }
        }
    }
    position_point = ImVec2(
        pos_win.x + (key_size.x/2) + key_size.x * position_key[position_label].x + keyboard_border ,
        pos_win.y + (key_size.y/2) + key_size.y * position_key[position_label].y + keyboard_border + keyboard_border_top
    );
    ImVec2 text_size = ImGui::CalcTextSize(list_labels[i_of_list].c_str());
    ImVec2 text_pos = ImVec2(
        position_point.x - (text_size.x/2),
        position_point.y - (text_size.y/2)
    );
    draw_list->AddText(text_pos, ImGui::ColorConvertFloat4ToU32(color_text), list_labels[i_of_list].c_str());
}
bool Key::view_settings(ImGuiIO& io)  // Utilisation de la référence pour éviter une copie
{
    bool out = false;
    if(is_plot_settings){
        ImGui::Begin(list_labels[0].c_str(), &is_plot_settings); // on affiche toujours le premier char pour le nom de la fenètre 

        ImGui::Text("Modifier les paramètres de la touche :");
        /* TO DO mettre dans les modification de chaque char
        ImGui::SeparatorText("Modifier le label :");

        if (ImGui::InputText("Label", buffer_label, sizeof(buffer_label))) {
        }
        if (ImGui::Button("Valider")) {
            list_labels = buffer_label;  // Mettre à jour `label` si le texte a été modifié
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear")) {
            list_labels = "Sans nom";  // Mettre à jour `label` si le texte a été modifié
            strncpy(buffer_label, list_labels.c_str(), sizeof(buffer_label));
            buffer_label[sizeof(buffer_label) - 1] = '\0';
        }
        */
        ImGui::SeparatorText("Modifier le doigt de la touche");
        
        const char* labels_combo_finger[] = _ALL_FINGERS_NAME_;
        if (ImGui::Combo("Doigt", &finger_assignment, labels_combo_finger, IM_ARRAYSIZE(labels_combo_finger))) {
            out = true;
        }
        ImGui::SeparatorText("Modifier caractères de la touche :");

        // Bouton pour ajouter un nouveau caractère
        if (ImGui::Button("Ajouter un caractère")) {
            add_char(_DEFAULT_KEY_CHAR_);
            out = true;
        }
        const char* labels_combo_mod[] = _ALL_KEY_MODIFIER_;
        // Boucle pour afficher chaque caractère et ses modificateurs
        for (size_t i = 0; i < list_chars.size(); ++i) {
            ImGui::PushID(static_cast<int>(i));  // Assigner un ID unique pour chaque champ pour éviter les conflits
            // Préparer un buffer pour le caractère
            char buffer[2] = { list_chars[i], '\0' };
            ImGui::SetNextItemWidth(30.0f);
            if (ImGui::InputText("Char", buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_CharsNoBlank)) {
                list_chars[i] = buffer[0];
                out = true;
            }
            ImGui::SameLine();
            ImGui::SetNextItemWidth(100.0f);
            if (ImGui::Combo("Mod 1", &list_modifier_1[i], labels_combo_mod, IM_ARRAYSIZE(labels_combo_mod))) {
                out = true;
            }
            ImGui::SameLine();
            ImGui::SetNextItemWidth(100.0f);
            if (ImGui::Combo("Mod 2", &list_modifier_2[i], labels_combo_mod, IM_ARRAYSIZE(labels_combo_mod))) {
                out = true;
            }
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(255, 0, 0, 255)); // Couleur rouge pour le bouton
            if (ImGui::Button("Supprimer")) {
                list_chars.erase(list_chars.begin() + i);
                list_modifier_1.erase(list_modifier_1.begin() + i);
                list_modifier_2.erase(list_modifier_2.begin() + i);
                --i; // Ajuster l'indice pour ne pas sauter l'élément suivant
                out = true;
            }
            ImGui::PopStyleColor();
            ImGui::PopID();
        }

        ImGui::SeparatorText("Modifier les couleur de la touche :");
        
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur remplissage",    (float*)&color_idle))  {}
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur attente",        (float*)&color_waiting))      {}
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur pressé",         (float*)&color_pressed))       {}
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur texte",          (float*)&color_text))         {}

        ImGui::SeparatorText("Modifier la position et la forme");
        // Affichage et modification des paires de coordonnées
        for (size_t i = 0; i < position_key.size(); i ++) {
            ImGui::PushID(i);  // Assigner un ID unique pour chaque champ pour éviter les conflits

            int x = position_key[i].x;
            int y = position_key[i].y;

            ImGui::SetNextItemWidth(100.0f);
            ImGui::InputInt("X", &x);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(100.0f);
            ImGui::InputInt("Y", &y);

            // Mettre à jour les valeurs dans le vecteur
            position_key[i].x = x;
            position_key[i].y = y;

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
                position_key.erase(position_key.begin() + i, position_key.begin() + i + 2);

                // Revenir en arrière dans l'index pour éviter de sauter l'élément suivant
                i -= 2;
            }
            ImGui::PopStyleColor(1); 
            ImGui::PopID();
        }

        // Bouton pour ajouter une nouvelle paire de coordonnées
        if (ImGui::Button("Ajouter une paire de coordonnées")) {
            position_key.push_back(_DEFAULT_COORDINATE_);  // Ajouter x = 0 par défaut
        }

        ImGui::End();
    }
    return out;    
}
/*

*/