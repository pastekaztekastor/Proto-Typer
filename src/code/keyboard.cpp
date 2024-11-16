#include <iostream>
#include "keyboard.h"
#include "define.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>


Keyboard::Keyboard() 
{
    position_fenetre = {0.f, 0.f}; // Valeur d'initialisation 
    initialise();
}

void Keyboard::initialise()
{
    // TODO Charge une config
    /*
    addKey(Key({"<"}, {0 , 0, 1, 0}         ));
    addKey(Key({"&"}, {2 , 0}               ));
    addKey(Key({"é"}, {3 , 0}               ));
    addKey(Key({"\""},{4 , 0}               ));
    addKey(Key({"'"}, {5 , 0}               ));
    addKey(Key({"("}, {6 , 0}               ));
    addKey(Key({"§"}, {7 , 0}               ));
    addKey(Key({"è"}, {8 , 0}               ));
    addKey(Key({"!"}, {9 , 0}               ));
    addKey(Key({"ç"}, {10 , 0}              ));
    addKey(Key({"à"}, {11, 0}               ));
    addKey(Key({")"}, {12, 0}               ));
    addKey(Key({"-"}, {13, 0}               ));
    addKey(Key({"Escape"}, {14, 0}          ));
    addKey(Key({"Tab"}, {0, 1, 1, 1}        ));
    addKey(Key({"A"}, {2, 1}                ));
    addKey(Key({"Z"}, {3, 1}                ));
    addKey(Key({"E"}, {4, 1}                ));
    addKey(Key({"R"}, {5, 1}                ));
    addKey(Key({"T"}, {6, 1}                ));
    addKey(Key({"Y"}, {7, 1}                ));
    addKey(Key({"U"}, {8, 1}                ));
    addKey(Key({"I"}, {9, 1}                ));
    addKey(Key({"O"}, {10, 1}               ));
    addKey(Key({"P"}, {11, 1}               ));
    addKey(Key({"^"}, {12, 1}               ));
    addKey(Key({"$"}, {13, 1}               ));
    addKey(Key({"Enter"}, {14, 1, 14, 2}    ));
    addKey(Key({"Ver\nMaj"}, {0, 2, 1, 2}   ));
    addKey(Key({"Q"}, {2, 2}                ));
    addKey(Key({"S"}, {3, 2}                ));
    addKey(Key({"D"}, {4, 2}                ));
    addKey(Key({"F"}, {5, 2}                ));
    addKey(Key({"G"}, {6, 2}                ));
    addKey(Key({"H"}, {7, 2}                ));
    addKey(Key({"J"}, {8, 2}                ));
    addKey(Key({"K"}, {9, 2}                ));
    addKey(Key({"L"}, {10, 2}               ));
    addKey(Key({"M"}, {11, 2}               ));
    addKey(Key({"Ù"}, {12, 2}               ));
    addKey(Key({"`"}, {13, 2}               ));
    addKey(Key({"Maj"}, {0, 3}              ));
    addKey(Key({"@"}, {1, 3}                ));
    addKey(Key({"W"}, {2, 3}                ));
    addKey(Key({"X"}, {3, 3}                ));
    addKey(Key({"C"}, {4, 3}                ));
    addKey(Key({"V"}, {5, 3}                ));
    addKey(Key({"B"}, {6, 3}                ));
    addKey(Key({"N"}, {7, 3}                ));
    addKey(Key({","}, {8, 3}                ));
    addKey(Key({";"}, {9, 3}                ));
    addKey(Key({":"}, {10, 3}               ));
    addKey(Key({"="}, {11, 3}               ));
    addKey(Key({"Maj"}, {12, 3, 13, 3, 14, 3}));
    addKey(Key({"Ctrl"}, {0, 4}));
    addKey(Key({"Cmd"}, {1, 4}));
    addKey(Key({"Alt"}, {2, 4}));
    addKey(Key({"Espace"}, {3, 4, 4, 4, 5, 4, 6, 4, 7, 4, 8, 4, 9, 4, 10, 4}));
    addKey(Key({"Alt"}, {11, 4}));
    addKey(Key({"Fn"}, {12, 4}));
    addKey(Key({"Menu"}, {13, 4}));
    addKey(Key({"Ctrl"}, {14, 4}));
    */
}

void Keyboard::addKey(Key key) 
{
    keys_.push_back(key);
}

void Keyboard::render(ImGuiIO io) 
{

    vue_clavier(io);
    vue_reglage(io);
    vue_liste_touche(io);
    for (auto& key : keys_)
    {
        key.view_settings(io);
    }
    
}

void Keyboard::vue_clavier(ImGuiIO io)
{
    if(is_afficher_clavier)
    {
        ImGui::Begin("Clavier Virtuel", &is_afficher_clavier);

        taille_de_touche = 
        {
            (ImGui::GetWindowSize().x-(bordure_clavier*2))/grille[0], 
            (ImGui::GetWindowSize().y-(bordure_clavier*2)-bordure_clavier_top_)/grille[1]
        };
        position_fenetre = ImGui::GetWindowPos();

        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        if (is_afficher_points_) 
        {
            plot_cases(io);
        }
        if (is_afficher_points_) 
        {
            plot_points(io);
        }

        for (auto& key : keys_) 
        {
            key.render(
                io, 
                position_fenetre, 
                bordure_touche, 
                taille_de_touche,
                bordure_clavier,
                bordure_clavier_top_,
                draw_list,
                0); // TODO géré les modifier pour changer les touche sur le clavier
        }
        ImGui::End();
    }
}

void Keyboard::vue_reglage(ImGuiIO io)
{
    if (is_afficher_settings_) 
    {
        ImGui::Begin("Paramètre clavier",&is_afficher_settings_);
        if (ImGui::Button("Exit")) {
            is_afficher_settings_ = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Touches")) {}
        ImGui::SameLine();
        if (ImGui::Checkbox("Edition",&is_afficher_points_)){}
        
        ImGui::SeparatorText("Clavier");
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur remplissage",(float*)&couleur_remplissage))
        {
            for(auto& key : keys_)
            {
                key.set_color_idle(couleur_remplissage);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur texte",(float*)&couleur_text))
        {
            for(auto& key : keys_)
            {
                key.set_couleur_text(couleur_text);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur attente auriculaire",(float*)&couleur_attente_1))
        {
            for(auto& key : keys_)
            {
                key.set_color_waiting(couleur_attente_1);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur attente annulaire",(float*)&couleur_attente_2))
        {
            for(auto& key : keys_)
            {
                key.set_color_waiting(couleur_attente_2);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur attente majeur",(float*)&couleur_attente_3))
        {
            for(auto& key : keys_)
            {
                key.set_color_waiting(couleur_attente_3);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur attente index",(float*)&couleur_attente_4))
        {
            for(auto& key : keys_)
            {
                key.set_color_waiting(couleur_attente_4);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur attente pouce",(float*)&couleur_attente_5))
        {
            for(auto& key : keys_)
            {
                key.set_color_waiting(couleur_attente_5);
            }
        }
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur presse",(float*)&couleur_presse))
        {
            for(auto& key : keys_)
            {
                key.set_couleur_presse(couleur_presse);
            }
        }
        if (ImGui::InputFloat("espacement touche",      &bordure_touche,    1.0f, 1.0f, "%.2f"))    {}
        if (ImGui::InputFloat("espacement clavier",     &bordure_clavier,   1.0f, 1.0f, "%.2f"))    {}
        
        ImGui::SeparatorText("Grille");
        ImGui::SetNextItemWidth(230.0f);
        if (ImGui::ColorEdit4("couleur point",          (float*)&couleur_points))                   {}
        if (ImGui::InputFloat("point taille",           &rayon_points,      0.2f, 1.0f, "%.2f"))    {}
        if (ImGui::InputInt("Marge supérieur",          &bordure_clavier_top_, 5))                  {}
        if (ImGui::InputInt("colones",                  &grille[0]))                                {}
        if (ImGui::InputInt("lignes",                   &grille[1]))                                {}
        if (ImGui::Checkbox("Afficher la grille",       &is_afficher_points_))                      {}
        if (ImGui::Checkbox("Afficher les cases",       &is_afficher_cases_))                       {}
        ImGui::End();
    }
}

void Keyboard::vue_liste_touche(ImGuiIO io)
{
    if (is_afficher_liste_touches)
    {
        ImGui::Begin("Gestion des touches", &is_afficher_liste_touches);
        for (size_t i = 0; i < keys_.size(); ++i) 
        {
            auto& key = keys_[i];

            if (ImGui::Button(("Éditer##" + std::to_string(i)).c_str())) {
                key.is_plot_settings = !key.is_plot_settings;
               // ImGui::OpenPopup("Édition de la touche");
            }
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, _DEFAULT_COLOR_WARNING_BUTTON_);
            if (ImGui::Button(("Supprimer##" + std::to_string(i)).c_str())) {
                keys_.erase(keys_.begin() + i);
                --i; // Ajuster l'index après suppression
            }
            ImGui::PopStyleColor(1); 
            ImGui::SameLine();
            ImGui::Text("Touche %zu : %s", i + 1, key.get_labels_by_index(0).c_str());
        }
        ImGui::End();
    }
}

int Keyboard::chargerConfigurationClavier(const std::string &cheminFichier)
{
    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open()) 
    {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << cheminFichier << std::endl;
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
            // todo
        }
        if (item.contains("finger"))
        {
            // todo
        }
        // Chargement des caractères et modificateurs
        if (item.contains("chars") && item["chars"].is_array())
        {
            for (const auto& charItem : item["chars"]) 
            {
                if (charItem.contains("char"))
                {
                    char character = charItem["char"].get<std::string>()[0];
                    int m1 = charItem["mod_1"].get<int>();
                    int m2 = charItem["mod_2"].get<int>();

                    key.add_char(character, m1, m2);
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

        keys_.push_back(key);
    }
    return nb_touche_charge;
}



std::vector<Key> Keyboard::get_keys()
{
    return keys_;
}

void Keyboard::plot_points(ImGuiIO io)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    for (size_t i = 0; i < grille[0]; i++) 
    {
        for (size_t j = 0; j < grille[1]; j++) 
        {
            ImVec2 position_point = ImVec2(
                position_fenetre.x + (taille_de_touche.x/2) + taille_de_touche.x * i + bordure_clavier ,
                position_fenetre.y + (taille_de_touche.y/2) + taille_de_touche.y * j + bordure_clavier + bordure_clavier_top_
            );
            draw_list->AddCircleFilled(position_point, rayon_points, ImGui::ColorConvertFloat4ToU32(couleur_points));
        }
    }
}

void Keyboard::update_listes()
{
    for (size_t i = 0; i < keys_.size(); i++)
    {
        auto& key = keys_[i];
        for (size_t j = 0; i < key.get_nb_char(); j++)
        {
            const auto& charactere = key.get_char_by_index(j);    // Liste de tous les char contenue sur toutes les touches
            const auto& modifier1 = key.get_mod_1_by_index(j);  // Liste de tous les modifier de chaque char 
            const auto& modifier2 = key.get_mod_2_by_index(j);  // Liste de tous les modifier de chaque char 

            liste_des_char.push_back(charactere);
            liste_des_modifier_1.push_back(modifier1);
            liste_des_modifier_2.push_back(modifier2);
            liste_des_index_des_touches.push_back(i);
        }
    }
}

int Keyboard::key_index_of_char(char c)
{
    for (size_t i = 0; i < liste_des_char.size(); i++)
    {
        if (c == liste_des_char[i])
        {
            return i;
        }   
    }
    return -1;
}

void Keyboard::plot_cases(ImGuiIO io)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    for (size_t i = 0; i < grille[0]; i++) 
    {
        for (size_t j = 0; j < grille[1]; j++) 
        {
            ImVec2 coin_TL = ImVec2(
                position_fenetre.x + bordure_touche*2 + taille_de_touche.x * i + bordure_clavier ,
                position_fenetre.y + bordure_touche*2 + taille_de_touche.y * j + bordure_clavier + bordure_clavier_top_
            );
            ImVec2 coin_BR = ImVec2(
                coin_TL.x - bordure_touche*4 + taille_de_touche.x,
                coin_TL.y - bordure_touche*4 + taille_de_touche.y
            );
            draw_list->AddRect(coin_TL, coin_BR, ImGui::ColorConvertFloat4ToU32(couleur_points));
        }
    }
}
