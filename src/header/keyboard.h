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
 * @file keyboard.h
 * @brief Classe définissant le fonctionnement du clavier. 
 * 
 * Elle contient un ensemble de touche de la classe qui est des variables qui lui sont propres comme 
 * les dimensions de la fenêtre et les différentes couleurs à signer à chaque doigt.
 * 
 * Elle possède plusieurs listes permettant de pouvoir retrouver facilement l'adresse des touches 
 * contenant des caractères. Parmi ces listes on retrouve la liste des caractères compris surtout le 
 * clavier. C'est une touche plus c'est plusieurs caractères alors elle apparaîtra plusieurs fois. 
 * Ainsi que la liste des touches de modification et la liste des modifications qu'elles apportent.
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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "imgui.h"
#include "define.h"
#include "key.h"
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>

class Keyboard {
public:
    // CONSTRUCTEUR ET INITIALISATION DU CLAVIER
    /**
     * @brief Déclare un nouvel objet clavier. Constructeur par défaut.
     */
    Keyboard();
    /**
     * @brief Fonctions qui ajoute une touche au clavier.
     * @param key Touche à ajouter au clavier.
     */
    void addKey(const Key key);

    // VUS ET RENDER
    /**
     * @brief Cette méthode utilise ImGui pour afficher les éléments graphiques relatifs au clavier.
     *  
     * Elle inclut l'affichage des paramètres globaux, de la liste des touches, ainsi que les 
     * paramètres individuels de chaque touche.
     * 
     * @param io Référence à un objet ImGuiIO, utilisé pour gérer les entrées/sorties de l'interface 
     * utilisateur ImGui.
     */
    void render(ImGuiIO& io) ;
    /**
     * @brief Affiche une vue graphique interactive du clavier virtuel dans l'interface ImGui.
     * 
     * Cette méthode gère l'affichage du clavier virtuel, sa disposition en grille ou en points, 
     * ainsi que l'affichage des touches individuelles avec leurs paramètres graphiques.
     * Elle utilise les dimensions et la position de la fenêtre pour calculer la disposition des 
     * touches.
     * @param io Référence à un objet ImGuiIO, utilisé pour gérer les entrées/sorties de l'interface 
     * utilisateur ImGui.
     */
    void view_keyboard(ImGuiIO& io);
    /**
     * @brief Affiche et gère les paramètres de personnalisation du clavier virtuel.
     * 
     * Cette méthode propose une interface utilisateur permettant de modifier divers paramètres
     * du clavier, tels que les couleurs des touches, les espacements, et les options d'affichage 
     * (grille, points). Elle applique les changements en temps réel aux touches du clavier.
     * 
     * @param io Référence à un objet ImGuiIO, utilisé pour gérer les entrées/sorties de l'interface 
     * utilisateur ImGui.
     */
    void view_settings(ImGuiIO& io);
    /**
     * @brief Affiche et gère la liste des touches du clavier virtuel.
     * 
     * Cette méthode propose une interface utilisateur permettant de visualiser, éditer ou supprimer 
     * les touches du clavier. Chaque touche est listée avec un bouton pour modifier ses paramètres 
     * ou la supprimer de la liste. Les modifications sont appliquées en temps réel.
     * 
     * @param io Référence à un objet ImGuiIO, utilisé pour gérer les entrées/sorties de l'interface 
     * utilisateur ImGui.
     */
    void view_key_list(ImGuiIO& io);

    // GESTION DES JSONS
    /**
     * @brief Charge la configuration des touches d'un clavier virtuel à partir d'un fichier JSON.
     * 
     * Cette méthode lit un fichier JSON contenant la description des touches du clavier, 
     * charge leurs positions, caractères, modificateurs et assignations, puis les ajoute à la liste 
     * des touches.
     * 
     * @param path Chemin du fichier JSON contenant la configuration du clavier.
     * @return int Nombre de touches chargées depuis le fichier.
     * @throws std::runtime_error Si le fichier ne peut pas être ouvert ou si le format JSON est 
     * invalide.
     */
    int load(const std::string& path);
    /**
     * @brief Sauvegarde la configuration des touches du clavier virtuel dans un fichier JSON.
     * 
     * Cette méthode écrit dans un fichier JSON la description des touches du clavier, 
     * y compris leurs positions, caractères, modificateurs et assignations, afin de permettre 
     * une restauration ultérieure.
     * 
     * @param cheminFichier Chemin du fichier où sauvegarder la configuration du clavier.
     * @return bool Indique si la sauvegarde a réussi (true) ou échoué (false).
     */
    int save(const std::string& path);

    // GETTER
    /**
     * @brief Get the keys object
     * @return std::vector<Key> 
     */
    std::vector<Key> get_keys ();
    // SETTER
    
    // ATTRIBUTS 
    bool is_plot_settings               = true;     // Variable pour afficher ou non des elements graphique
    bool is_plot_key_list               = true;     // Variable pour afficher ou non des elements graphique
    bool is_plot_keyboard               = true;     // Variable pour afficher ou non des elements graphique
    bool is_edit_mode                   = true;     // Variable pour afficher ou non des elements graphique
    bool is_plot_dot_view_keyboard      = false;    // Variable pour afficher ou non des elements graphique
    bool is_plot_grid_view_keyboard     = false;    // Variable pour afficher ou non des elements graphique

private:
    // Méthodes
    /**
     * @brief Dessine une grille de cases dans l'interface utilisateur.
     * 
     * Cette méthode trace une grille composée de rectangles à l'aide des dimensions 
     * spécifiées et des paramètres graphiques du clavier. Les positions et tailles des 
     * cases sont calculées dynamiquement en fonction des paramètres de la fenêtre et du clavier.
     * 
     * @param io Référence à un objet ImGuiIO, utilisé pour les entrées/sorties de l'interface 
     * utilisateur ImGui.
     */
    void plot_grid(ImGuiIO io);
    /**
     * @brief Dessine une grille de points dans l'interface utilisateur.
     * 
     * Cette méthode trace des cercles remplis pour représenter une grille de points. 
     * Les positions des points sont calculées dynamiquement en fonction des dimensions 
     * du clavier virtuel et des paramètres de la fenêtre.
     * 
     * @param io Référence à un objet ImGuiIO, utilisé pour les entrées/sorties de l'interface 
     * utilisateur ImGui.
     */
    void plot_dot(ImGuiIO io);
    /**
     * @brief Met à jour les listes de caractères, modificateurs et indices des touches.
     * 
     * Cette méthode réinitialise et remplit les listes utilisées pour stocker :
     * - Tous les caractères associés aux touches du clavier virtuel.
     * - Les modificateurs de chaque caractère (mod_1 et mod_2).
     * - Les indices des touches correspondant à chaque caractère.
     * 
     * Ces listes sont générées à partir des données des touches actuellement configurées.
     */
    void update_listes();
    /**
     * @brief Recherche l'index d'un caractère spécifique dans la liste des caractères.
     * 
     * Parcourt la liste des caractères associés aux touches du clavier et retourne l'index 
     * du caractère correspondant. Si le caractère n'est pas trouvé, une exception logique est levée.
     * 
     * @param c Caractère à rechercher dans la liste.
     * @return int Index du caractère dans la liste des caractères.
     * @throws std::logic_error Si le caractère n'est pas présent dans la liste.
     */
    int index_of_char(const char c);
    /**
     * @brief Récupère l'indice de la touche associée à un index spécifique de la liste des 
     * caractères.
     * 
     * Vérifie si l'index fourni est valide, puis retourne l'indice de la touche correspondante 
     * dans la liste des indices de touches. Si l'index est hors limites, une exception est levée.
     * 
     * @param i Index à rechercher dans la liste des indices de touches.
     * @return int Indice de la touche correspondante.
     * @throws std::out_of_range Si l'index est en dehors des limites de la liste.
     */
    int key_index_of_index(const int i);
    /**
     * @brief Récupère la valeur du modificateur 1 associée à un index spécifique dans la liste des 
     * modificateurs.
     * 
     * Vérifie si l'index fourni est valide, puis retourne la valeur du modificateur 1 correspondant.
     * Si l'index est hors des limites, une exception est levée.
     * 
     * @param i Index à rechercher dans la liste des modificateurs 1.
     * @return int Valeur du modificateur 1 correspondant.
     * @throws std::out_of_range Si l'index est en dehors des limites de la liste.
     */
    int mod_1_of_index(const int i);
    /**
     * @brief Récupère la valeur du modificateur 2 associée à un index spécifique dans la liste des 
     * modificateurs.
     * 
     * Vérifie si l'index fourni est valide, puis retourne la valeur du modificateur 2 correspondant.
     * Si l'index est hors des limites, une exception est levée.
     * 
     * @param i Index à rechercher dans la liste des modificateurs 2.
     * @return int Valeur du modificateur 2 correspondant.
     * @throws std::out_of_range Si l'index est en dehors des limites de la liste.
     */
    int mod_2_of_index(const int i);

    struct _coordinate_ coord_of_mouse(ImGuiIO& io) ;

    // Attributs
    std::vector<Key> keys;
    ImVec2 key_size                 = _INITIALISE_IMVEC2_;              // Pour l'initialisation
    float border_key                = _DEFAULT_KEY_BORDER_ ;            // 
    float border_keyboard           = _DEFAULT_KEYBOARD_BORDER_;        // 
    int border_keyboard_top         = _DEFAULT_KEYBOARD_BORDER_TOP_;    // 
    float dot_radius                = _DEFAULT_POINT_RADIUS_;           // 
    float text_size                 = _DEFAULT_TEXT_SIZE_;              // TOOD
    std::vector<int> grid_dimention = _DEFAULT_GRID_DIMENTION_;         // 
    ImVec2 windows_position;
    
    std::vector<char> list_char     = _INITIALISE_VECTOR_;    // Liste de tous les char contenue sur toutes les touches
    std::vector<int> list_mod_1     = _INITIALISE_VECTOR_;    // Liste de tous les modifier de chaque char 
    std::vector<int> list_mod_2     = _INITIALISE_VECTOR_;    // Liste de tous les modifier de chaque char 
    std::vector<int> list_index_key = _INITIALISE_VECTOR_;    // Index de chaque touche dans le liste de touche
    int index_acc                   = 0;                      // Index des listes

    ImVec4  color_bkg_key           = _DEFAULT_COLOR_BACKGROUND_KEY_;
    ImVec4  color_f_index           = _DEFAULT_COLOR_KEY_WAITING_1_;
    ImVec4  color_f_middle          = _DEFAULT_COLOR_KEY_WAITING_2_;
    ImVec4  color_f_ring            = _DEFAULT_COLOR_KEY_WAITING_3_;
    ImVec4  color_f_little          = _DEFAULT_COLOR_KEY_WAITING_4_;
    ImVec4  color_f_thumb           = _DEFAULT_COLOR_KEY_WAITING_5_;
    ImVec4  color_pressed           = _DEFAULT_COLOR_KEY_PRESSED_;
    ImVec4  color_text              = _DEFAULT_COLOR_TEXT_;
    ImVec4  color_dot               = _DEFAULT_COLOR_GRID_EDITION_;
};

#endif // KEYBOARD_H
