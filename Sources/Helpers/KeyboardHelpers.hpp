#ifndef KEYBOARDHELPERS_HPP
#define KEYBOARDHELPERS_HPP

#include "CTRPluginFramework/Menu/MenuEntry.hpp"

namespace CTRPluginFramework
{
    template <typename T>
    T *GetArg(MenuEntry *entry)
    {
        T *Arg = reinterpret_cast<T *>(entry->GetArg());
        
        if (Arg == nullptr)
        {
            Arg = new T();
            entry->SetArg(Arg);
        }
        
        return (Arg);
    }
    
    template <typename T>
    T *GetArg(MenuEntry *entry, T DefaultValue)
    {
        T *Arg = reinterpret_cast<T *>(entry->GetArg());
        
        if (Arg == nullptr)
        {
            Arg = new T(DefaultValue);
            entry->SetArg(Arg);
        }
        
        return (Arg);
    }
    
	using OnCompareCallback = bool (*)(const void *, std::string&);
	
	template<typename T>
	bool KB(const std::string &Message, bool CanAbort, bool IsHex, const int MaxLength, T &Output, T Default, OnCompareCallback Callback = nullptr) 
	{
		Keyboard KB(Message);
		KB.CanAbort(CanAbort);
		KB.IsHexadecimal(IsHex);
		KB.SetMaxLength(MaxLength);
		KB.SetCompareCallback(Callback);
		return KB.Open((T &)Output, (T)Default);
	};
	
	struct KBSelection
	{
		const char* Name;
		int Value;
	};
	
	struct KBStrings
	{
		const char* Name;
		const char* Nickname;
	};
}
#endif