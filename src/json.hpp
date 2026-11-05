#ifndef SIMPLE_JSON_H
#define SIMPLE_JSON_H

#include <string>
#include <sstream>
#include <cstdlib>

namespace nlohmann {
class json {
    const std::string& get_content() const { return content; }
    static json parse(std::istream& is) {
        json j;
        std::stringstream ss;
        ss << is.rdbuf();
        j.content = ss.str();
        return j;
    }
    std::string operator[](const std::string& key) const {
        std::string search = "\"" + key + "\"";
        size_t pos = content.find(search);
        if (pos == std::string::npos) return "";
        pos = content.find(':', pos);
        if (pos == std::string::npos) return "";
        pos = content.find('"', pos);
        if (pos == std::string::npos) return "";
        size_t end = content.find('"', pos + 1);
        if (end == std::string::npos) return "";
        return content.substr(pos + 1, end - pos - 1);
    }
};
}

#endif
