#include <CTRPluginFramework.hpp>
#include "Framework/Wrappers.hpp"
#include "../../../Includes/stdafx.hpp"

namespace CTRPluginFramework {
    Game game = Game::None;
    Group group = Group::None;
    Update update = Update::Supported;

    namespace Helpers {
        // Chooses the correct entry between the generations
        FuncPointer ChooseEntry(FuncPointer func1, FuncPointer func2) {
            return (group == Group::XY || group == Group::ORAS ? func1 : func2);
        }
    }
}