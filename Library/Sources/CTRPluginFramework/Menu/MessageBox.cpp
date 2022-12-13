#include <Headers.hpp>

namespace CTRPluginFramework {
    MessageBox::MessageBox(const std::string &title, const std::string &message, DialogType dialogType, ClearScreen clear) :
        _messageBox(new MessageBoxImpl(title, message, dialogType, clear))
    {}

    MessageBox::MessageBox(const std::string &message, DialogType dialogType, ClearScreen clear) :
        _messageBox(new MessageBoxImpl(message, dialogType, clear))
    {}

    MessageBox::~MessageBox(void) {}

    MessageBox &MessageBox::SetClear(ClearScreen screen) {
        _messageBox->_clearScreen = screen;
        return *this;
    }

    bool MessageBox::operator()(void) const {
        return ((*_messageBox)());
    }
}