#include <Headers.hpp>

namespace CTRPluginFramework {
    SubMenu::SubMenu(const vector<string> &options) :
        _options(options), _selector{0}, _isOpen{false}, _action{false}
    {}

    SubMenu::~SubMenu() {}

    int SubMenu::operator()(void) {
        bool action = _action;
        _action = false;
        return action ? _selector : -1;
    }

    void SubMenu::Draw(void) {
        if (!_isOpen)
            return;

        static IntRect background(240, 20, 130, 200);
        const Color &black = Color::Black;
        const Color &darkgrey = Color::DarkGrey;
        const Color &gainsboro = Color::Gainsboro;
        const Color &textcolor = Preferences::Settings.MainTextColor;

        // Ensure the top screen is the target
        Renderer::SetTarget(TOP);
        Renderer::DrawRect2(background, Preferences::Settings.BackgroundMainColor, Preferences::Settings.BackgroundSecondaryColor);

        int posY = 25;

        // Draw title's menu
        Renderer::DrawSysString("Options", 245, posY, 340, textcolor);
        posY = 46;

        if (_options.empty())
            return;

        const IntRect selRect = IntRect(241, 45 + _selector * 12, 110, 12);

        for (u32 i = 0; i < _options.size(); i++) {
            const char *str = _options[i].c_str();

            if (i == _selector) {
                // If an action is selected, create a little effect (yeah, very little)
                if (!_fadeClock.HasTimePassed(Seconds(0.2f))) {
                    // Draw action rectangle
                    Renderer::DrawRect(selRect, gainsboro);
                    // Draw selector
                    Renderer::DrawRect(selRect, darkgrey, false);
                    // Draw text
                    Renderer::DrawString(str, 245, posY, black);
                    posY += 2;
                    continue;
                }

                else {
                    // Draw selector
                    Renderer::DrawRect(selRect, darkgrey, false);
                }
            }

            Renderer::DrawString(str, 245, posY, textcolor);
            posY += 2;
        }
    }

    void SubMenu::ProcessEvent(const Event &event) {
        if (!_isOpen) {
            if (event.type == event.KeyPressed && event.key.code == Key::X)
                _isOpen = true;

            return;
        }

        if (event.type == Event::EventType::KeyPressed) {
            switch (event.key.code) {
                case Key::DPadUp:
                    _selector = max((int)_selector - 1, (int)0);
                    break;
                case Key::DPadDown:
                    _selector = min((u32)_selector + 1, (u32)_options.size() - 1);
                    break;
                case Key::A:
                    _action = true;
                    _fadeClock.Restart();
                    break;
                case Key::B:
                    _isOpen = false;
                    break;

                default: break;
            }
        }
    }

    bool SubMenu::IsOpen(void) {
        return _isOpen;
    }

    void SubMenu::ChangeOptions(const vector<string> &options) {
        _selector = 0;
        _options.clear();
        _options = options;
    }

    u32 SubMenu::OptionsCount(void) {
        return _options.size();
    }
}