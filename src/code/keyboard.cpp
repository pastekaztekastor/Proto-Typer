/**
 *  _  __          _                         _ 
 * | |/ /         | |                       | |
 * | ' / ___ _   _| |__   ___   __ _ _ __ __| |
 * |  < / _ \ | | | '_ \ / _ \ / _` | '__/ _` |
 * | . \  __/ |_| | |_) | (_) | (_| | | | (_| |
 * |_|\_\___|\__, |_.__/ \___/ \__,_|_|  \__,_|
 *            __/ |                            
 *           |___/                             
 * 
 * @file keyboard.cpp
 * @brief Cf ../header/keyboard.h
 * 
 * @author Mathurin Champémont
 * @date 17 novembre 2024
 *
 * @version 1.0.0
 *
 * @copyright MIT License
 *
 * @note 
 */
#include <iostream>
#include "keyboard.h"
#include "define.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>


Keyboard::Keyboard() 
{
    windows_position = {0.f, 0.f}; // Valeur d'initialisation 
}

void Keyboard::addKey(Key key) 
{
    keys.push_back(key);
}

void Keyboard::render(ImGuiIO& io) 
{
    view_keyboard(io);
    view_settings(io);
    view_key_list(io);
    for (auto& key : keys)
    {
        key.view_settings(io);
    }
}

void Keyboard::view_keyboard(ImGuiIO& io)
{
    if(is_plot_keyboard)
    {
        ImGui::Begin("Clavier Virtuel", &is_plot_keyboard);

        key_size = 
        {
            (ImGui::GetWindowSize().x-(border_keyboard*2))/grid_dimention[0], 
            (ImGui::GetWindowSize().y-(border_keyboard*2)-border_keyboard_top)/grid_dimention[1]
        };
        windows_position = ImGui::GetWindowPos();

        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        if (is_plot_grid_view_keyboard) 
        {
            plot_grid(io);
        }
        if (is_plot_dot_view_keyboard) 
        {
            plot_dot(io);
        }
        if (is_edit_mode)
        {
            coord_of_mouse(io);
        }

        for (auto& key : keys) 
        {
            key.render
            (
                io, 
                windows_position, 
                border_key, 
                key_size,
                border_keyboard,
                border_keyboard_top,
                draw_list,
                0
            ); // TODO géré les modifier pour changer les touche sur le clavier
        }
        ImGui::End();
    }
}

void Keyboard::view_settings(ImGuiIO& io)
{
    if (is_plot_settings) 
    {
        ImGui::Begin("Paramètre clavier",&is_plot_settings);
        if (ImGui::Button("Exit")) {
            is_plot_settings = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Touches")) {}
        ImGui::SameLine();
        if (ImGui::Checkbox("Edition",&is_plot_dot_view_keyboard)){}
        
        ImGui::SeparatorText("Clavier");
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur remplissage",(float*)&color_bkg_key))
        {
            for(auto& key : keys)
            {
                key.set_color_idle(color_bkg_key);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur texte",(float*)&color_text))
        {
            for(auto& key : keys)
            {
                key.set_couleur_text(color_text);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur attente auriculaire",(float*)&color_f_little))
        {
            for(auto& key : keys)
            {
                key.set_color_waiting(color_f_little);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur attente annulaire",(float*)&color_f_middle))
        {
            for(auto& key : keys)
            {
                key.set_color_waiting(color_f_middle);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur attente majeur",(float*)&color_f_ring))
        {
            for(auto& key : keys)
            {
                key.set_color_waiting(color_f_ring);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur attente index",(float*)&color_f_index))
        {
            for(auto& key : keys)
            {
                key.set_color_waiting(color_f_index);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur attente pouce",(float*)&color_f_thumb))
        {
            for(auto& key : keys)
            {
                key.set_color_waiting(color_f_thumb);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur presse",(float*)&color_pressed))
        {
            for(auto& key : keys)
            {
                key.set_couleur_presse(color_pressed);
            }
        }
        if (ImGui::InputFloat("espacement touche",      &border_key,    1.0f, 1.0f, "%.2f"))    {}
        if (ImGui::InputFloat("espacement clavier",     &border_keyboard,   1.0f, 1.0f, "%.2f"))    {}
        
        ImGui::SeparatorText("Grille");
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur point",          (float*)&color_dot))                   {}
        if (ImGui::InputFloat("point taille",           &dot_radius,      0.2f, 1.0f, "%.2f"))    {}
        if (ImGui::InputInt("Marge supérieur",          &border_keyboard_top, 5))                  {}
        if (ImGui::InputInt("colones",                  &grid_dimention[0]))                                {}
        if (ImGui::InputInt("lignes",                   &grid_dimention[1]))                                {}
        if (ImGui::Checkbox("Afficher la grille",       &is_plot_dot_view_keyboard))                      {}
        if (ImGui::Checkbox("Afficher les cases",       &is_plot_grid_view_keyboard))                       {}
        ImGui::End();
    }
}

void Keyboard::view_key_list(ImGuiIO& io)
{
    if (is_plot_key_list)
    {
        ImGui::Begin("Gestion des touches", &is_plot_key_list);
        for (size_t i = 0; i < keys.size(); ++i) 
        {
            auto& key = keys[i];

            if (ImGui::Button(("Éditer##" + std::to_string(i)).c_str())) {
                key.is_plot_settings = !key.is_plot_settings;
               // ImGui::OpenPopup("Édition de la touche");
            }
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, _DEFAULT_COLOR_WARNING_BUTTON_);
            if (ImGui::Button(("Supprimer##" + std::to_string(i)).c_str())) {
                keys.erase(keys.begin() + i);
                --i; // Ajuster l'index après suppression
            }
            ImGui::PopStyleColor(1); 
            ImGui::SameLine();
            ImGui::Text("Touche %zu : %s", i + 1, key.get_labels_by_index(0).c_str());
        }
        ImGui::End();
    }
}

int Keyboard::load(const std::string &path)
{
    std::ifstream fichier(path);
    if (!fichier.is_open()) 
    {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << path << std::endl;
        return 0;
    }
    nlohmann::json j;
    fichier >> j;
    int nb_touche_charge = 0;
    for (const auto& item : j["keys"]) 
    {
        nb_touche_charge++;
        Key key;
        // Chargement des positions
        if (item.contains("positions") && item["positions"].is_array())
        {
            for (const auto& posItem : item["positions"]) 
            {
                if (posItem.contains("x") && posItem.contains("y") &&
                    posItem["x"].is_number_integer() && posItem["y"].is_number_integer())
                {
                    int x = posItem["x"].get<int>();
                    int y = posItem["y"].get<int>();
                    key.add_position({x, y});
                }
                else
                {
                    std::cerr << "Position invalide pour une touche." << std::endl;
                }
            }
        }
        else
        {
            std::cerr << "Aucune position définie pour une touche." << std::endl;
        }
        // Chargmenet de la position du text
        if (item.contains("lbl_pos"))
        {
            key.set_lbl_position(item["lbl_pos"].get<int>());
        }
        if (item.contains("finger"))
        {
            key.set_finger_assignment(item["finger"].get<int>());
        }
        else
        {
            std::cerr << "Aucun doigt défini pour cette touche." << std::endl;
        }
        // Chargement des caractères et modificateurs
        if (item.contains("chars") && item["chars"].is_array())
        {
            for (const auto& charItem : item["chars"]) 
            {
                if (charItem.contains("char") && charItem.contains("mod_1") && charItem.contains("mod_2"))
                {
                    char character = charItem["char"].get<std::string>()[0];
                    int m1 = charItem["mod_1"].get<int>();
                    int m2 = charItem["mod_2"].get<int>();
                    if (charItem.contains("label")){
                        key.add_char(charItem["label"].get<std::string>(), character, m1, m2);
                    }
                    else
                    {
                        key.add_char(character, m1, m2);
                    }
                }
                else
                {
                    std::cerr << "Caractère invalide pour une touche." << std::endl;
                }
            }
        }
        else
        {
            std::cerr << "Aucun caractère défini pour une touche." << std::endl;
        }

        keys.push_back(key);
    }
    return nb_touche_charge;
}

std::vector<Key> Keyboard::get_keys()
{
    return keys;
}

void Keyboard::plot_dot(ImGuiIO io)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    for (size_t i = 0; i < grid_dimention[0]; i++) 
    {
        for (size_t j = 0; j < grid_dimention[1]; j++) 
        {
            ImVec2 position_point = ImVec2(
                windows_position.x + (key_size.x/2) + key_size.x * i + border_keyboard ,
                windows_position.y + (key_size.y/2) + key_size.y * j + border_keyboard + border_keyboard_top
            );
            draw_list->AddCircleFilled(position_point, dot_radius, ImGui::ColorConvertFloat4ToU32(color_dot));
        }
    }
}

void Keyboard::update_listes()
{
    list_char.clear();
    list_index_key.clear();
    list_mod_1.clear();
    list_mod_2.clear();

    for (size_t i = 0; i < keys.size(); i++)
    {
        auto& key = keys[i];
        for (size_t j = 0; i < key.get_nb_char(); j++)
        {
            const auto& charactere = key.get_char_by_index(j);  // Liste de tous les char contenue sur toutes les touches
            const auto& modifier1 = key.get_mod_1_by_index(j);  // Liste de tous les modifier de chaque char 
            const auto& modifier2 = key.get_mod_2_by_index(j);  // Liste de tous les modifier de chaque char 

            list_char.push_back(charactere);
            list_mod_1.push_back(modifier1);
            list_mod_2.push_back(modifier2);
            list_index_key.push_back(i);
        }
    }
}

int Keyboard::index_of_char(const char c)
{
    for(size_t i = 0; i < list_char.size(); i++)
    {
        if (c == list_char[i])
        {
            return i;
        }
    }
    throw std::logic_error("La liste des caractères ne contient pas '" + std::string(1, c) + "'");
    return -1;
}

int Keyboard::key_index_of_index(const int i)
{
    if (i>= list_index_key.size() || i < 0)
    {
        throw std::out_of_range("L'index de longueur " + std::to_string(i) + " est hors des limites autorisées.");
        return -1;
    }
    else
    {
        return list_index_key[i];
    }
}

int Keyboard::mod_1_of_index(const int i)
{
    if (i>= list_mod_1.size() || i < 0)
    {
        throw std::out_of_range("L'index de longueur " + std::to_string(i) + " est hors des limites autorisées.");
        return -1;
    }
    else
    {
        return list_mod_1[i];
    }
}

int Keyboard::mod_2_of_index(const int i)
{
    if (i>= list_mod_2.size() || i < 0)
    {
        throw std::out_of_range("L'index de longueur " + std::to_string(i) + " est hors des limites autorisées.");
        return -1;
    }
    else
    {
        return list_mod_2[i];
    }
}

struct _coordinate_ Keyboard::coord_of_mouse(ImGuiIO &io)
{
    ImVec2 mouse_pos_global = ImGui::GetMousePos();
    ImVec2 pos_win = ImGui::GetWindowPos();
    _coordinate_ coord_mouse = 
    {
        static_cast<int>((mouse_pos_global.x - pos_win.x - (border_key + border_keyboard)) / key_size.x) ,
        static_cast<int>((mouse_pos_global.y - pos_win.y - (border_key + border_keyboard + border_keyboard_top)) / key_size.y)
    };

    std::cout << "pos = ["<<mouse_pos_global.x<<", "<<mouse_pos_global.y<<"] indice ["<<coord_mouse.x<<", "<<coord_mouse.y<<"]"<<std::endl;
    return coord_mouse;
}

void Keyboard::plot_grid(ImGuiIO io)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    for (size_t i = 0; i < grid_dimention[0]; i++) 
    {
        for (size_t j = 0; j < grid_dimention[1]; j++) 
        {
            ImVec2 coin_TL = ImVec2(
                windows_position.x + border_key*2 + key_size.x * i + border_keyboard ,
                windows_position.y + border_key*2 + key_size.y * j + border_keyboard + border_keyboard_top
            );
            ImVec2 coin_BR = ImVec2(
                coin_TL.x - border_key*4 + key_size.x,
                coin_TL.y - border_key*4 + key_size.y
            );
            draw_list->AddRect(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(color_dot));
        }
    }
}
