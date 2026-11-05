#ifndef THEME_H
#define THEME_H

#include <string>
#include <vector>
#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include "json.hpp"
#include <fstream>

struct ColorTheme {
    std::string name;
    Fl_Color background;
    Fl_Color foreground;
    Fl_Color cursor;
    Fl_Color palette[16];
};

struct ThemeEntry {
    std::string name;
    std::string filename;
    bool available;
};

inline std::vector<ThemeEntry> get_available_themes() {
    std::vector<ThemeEntry> themes;
#ifndef THEME_DIR
#define THEME_DIR "themes"
#endif
    std::string path = std::string(THEME_DIR) + "/themes.json";
    std::ifstream f(path);
    if (!f.is_open()) {
        f.open("themes/themes.json");
    }
    if (!f.is_open()) return themes;

    nlohmann::json j = nlohmann::json::parse(f);

    // Parse objects manually within the content string using json operator[]
    size_t pos = 0;
    while ((pos = j.get_content().find("{", pos)) != std::string::npos) {
        size_t end = j.get_content().find("}", pos);
        if (end == std::string::npos) break;
        std::string obj_str = j.get_content().substr(pos, end - pos + 1);

        // Parse individual object via istringstream using json::parse
        std::istringstream iss(obj_str);
        nlohmann::json item = nlohmann::json::parse(iss);

        std::string name = item["name"];
        std::string filename = item["filename"];
        if (!name.empty() && !filename.empty()) {
            std::string theme_path = std::string(THEME_DIR) + "/" + filename;
            std::ifstream test_file(theme_path);
            bool exists = test_file.is_open();
            if (!exists) {
                test_file.open("themes/" + filename);
                exists = test_file.is_open();
            }
            themes.push_back({name, filename, exists});
        }
        pos = end + 1;
    }
    return themes;
}

inline Fl_Color hex_to_flcolor(const std::string& hex) {
    if (hex.empty() || hex[0] != '#') return FL_BLACK;
    unsigned int r = 0, g = 0, b = 0;
    sscanf(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);
    return fl_rgb_color(r, g, b);
}

inline void set_default_theme(ColorTheme& theme) {
    theme.background = fl_rgb_color(31, 31, 40);
    theme.foreground = fl_rgb_color(220, 215, 186);
    theme.cursor = fl_rgb_color(200, 192, 147);
    theme.palette[0]  = fl_rgb_color(22, 22, 29);
    theme.palette[1]  = fl_rgb_color(195, 64, 67);
    theme.palette[2]  = fl_rgb_color(118, 148, 106);
    theme.palette[3]  = fl_rgb_color(192, 163, 110);
    theme.palette[4]  = fl_rgb_color(126, 156, 216);
    theme.palette[5]  = fl_rgb_color(149, 127, 184);
    theme.palette[6]  = fl_rgb_color(106, 149, 137);
    theme.palette[7]  = fl_rgb_color(200, 192, 147);
    theme.palette[8]  = fl_rgb_color(84, 84, 109);
    theme.palette[9]  = fl_rgb_color(232, 36, 36);
    theme.palette[10] = fl_rgb_color(152, 187, 108);
    theme.palette[11] = fl_rgb_color(230, 195, 132);
    theme.palette[12] = fl_rgb_color(127, 180, 202);
    theme.palette[13] = fl_rgb_color(147, 138, 169);
    theme.palette[14] = fl_rgb_color(122, 168, 159);
    theme.palette[15] = fl_rgb_color(220, 215, 186);
}

inline bool load_theme_file(const std::string& filepath, ColorTheme& theme) {
    std::ifstream f(filepath);
    if (!f.is_open()) {
        set_default_theme(theme);
        printf("Setting to default theme, filepath does not exists...");
        return false;
    }
    try {
        nlohmann::json j = nlohmann::json::parse(f);
        theme.name = filepath;
        theme.background = hex_to_flcolor(j["background"]);
        theme.foreground = hex_to_flcolor(j["foreground"]);
        theme.cursor = hex_to_flcolor(j["cursor"]);

        theme.palette[0]  = hex_to_flcolor(j["black"]);
        theme.palette[1]  = hex_to_flcolor(j["red"]);
        theme.palette[2]  = hex_to_flcolor(j["green"]);
        theme.palette[3]  = hex_to_flcolor(j["yellow"]);
        theme.palette[4]  = hex_to_flcolor(j["blue"]);
        theme.palette[5]  = hex_to_flcolor(j["magenta"]);
        theme.palette[6]  = hex_to_flcolor(j["cyan"]);
        theme.palette[7]  = hex_to_flcolor(j["white"]);
        theme.palette[8]  = hex_to_flcolor(j["brightBlack"]);
        theme.palette[9]  = hex_to_flcolor(j["brightRed"]);
        theme.palette[10] = hex_to_flcolor(j["brightGreen"]);
        theme.palette[11] = hex_to_flcolor(j["brightYellow"]);
        theme.palette[12] = hex_to_flcolor(j["brightBlue"]);
        theme.palette[13] = hex_to_flcolor(j["brightMagenta"]);
        theme.palette[14] = hex_to_flcolor(j["brightCyan"]);
        theme.palette[15] = hex_to_flcolor(j["brightWhite"]);
        return true;
    } catch (...) {
        set_default_theme(theme);
        return false;
    }
}

#endif
