/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (VDV_B@hotmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/TGUI.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RadioButton::RadioButton()
    {
        m_ObjectType = radioButton;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    RadioButton::RadioButton(const RadioButton& copy) :
    Checkbox(copy)
    {
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    RadioButton& RadioButton::operator= (const RadioButton& right)
    {
        if (this != &right)
        {
            this->Checkbox::operator=(right);
        }
        
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::check()
    {
        // Tell our parent that all the radio buttons should be unchecked
        m_Parent->uncheckRadioButtons();
        
        // Check this radio button
        m_Checked = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::uncheck()
    {
        // The radio button can't be unchecked, so we override the original function with an empty one.
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}