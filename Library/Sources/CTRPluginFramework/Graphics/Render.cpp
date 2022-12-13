#include <Headers.hpp>

namespace CTRPluginFramework {
    float Render::GetTextWidth(const std::string &text) {
        return Renderer::GetTextSize(text.c_str());
    }
 }