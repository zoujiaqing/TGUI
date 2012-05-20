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

    LoadingBar::LoadingBar() :
    m_Minimum       (  0),
    m_Maximum       (100),
    m_Value         (  0),
    m_SplitImage    (false),
    m_TextureBack_L (NULL),
    m_TextureBack_M (NULL),
    m_TextureBack_R (NULL),
    m_TextureFront_L(NULL),
    m_TextureFront_M(NULL),
    m_TextureFront_R(NULL)
    {
        m_ObjectType = loadingBar;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    LoadingBar::LoadingBar(const LoadingBar& copy) :
    OBJECT               (copy),
    m_Minimum            (copy.m_Minimum),
    m_Maximum            (copy.m_Maximum),
    m_Value              (copy.m_Value),
    m_SplitImage         (copy.m_SplitImage)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    LoadingBar::~LoadingBar()
    {
        if (m_TextureBack_L != NULL)  TGUI_TextureManager.removeTexture(m_TextureBack_L);
        if (m_TextureBack_M != NULL)  TGUI_TextureManager.removeTexture(m_TextureBack_M);
        if (m_TextureBack_R != NULL)  TGUI_TextureManager.removeTexture(m_TextureBack_R);

        if (m_TextureFront_L != NULL) TGUI_TextureManager.removeTexture(m_TextureFront_L);
        if (m_TextureFront_M != NULL) TGUI_TextureManager.removeTexture(m_TextureFront_M);
        if (m_TextureFront_R != NULL) TGUI_TextureManager.removeTexture(m_TextureFront_R);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    LoadingBar& LoadingBar::operator= (const LoadingBar& right)
    {
        // Make sure it is not the same object
        if (this != &right)
        {
            LoadingBar temp(right);
            this->OBJECT::operator=(right);

            std::swap(m_Minimum,        temp.m_Minimum);
            std::swap(m_Maximum,        temp.m_Maximum);
            std::swap(m_Value,          temp.m_Value);
            std::swap(m_SplitImage,     temp.m_SplitImage);
            std::swap(m_TextureBack_L,  temp.m_TextureBack_L);
            std::swap(m_TextureBack_M,  temp.m_TextureBack_M);
            std::swap(m_TextureBack_R,  temp.m_TextureBack_R);
            std::swap(m_TextureFront_L, temp.m_TextureFront_L);
            std::swap(m_TextureFront_M, temp.m_TextureFront_M);
            std::swap(m_TextureFront_R, temp.m_TextureFront_R);
            std::swap(m_SpriteBack_L,   temp.m_SpriteBack_L);
            std::swap(m_SpriteBack_M,   temp.m_SpriteBack_M);
            std::swap(m_SpriteBack_R,   temp.m_SpriteBack_R);
            std::swap(m_SpriteFront_L,  temp.m_SpriteFront_L);
            std::swap(m_SpriteFront_M,  temp.m_SpriteFront_M);
            std::swap(m_SpriteFront_R,  temp.m_SpriteFront_R);
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool LoadingBar::load(const std::string pathname)
    {
        // When everything is loaded successfully, this will become true.
        m_Loaded = false;

        // Make sure that the pathname isn't empty
        if (pathname.empty())
            return false;

        // Store the pathname
        m_LoadedPathname = pathname;

        // When the pathname does not end with a "/" then we will add it
        if (m_LoadedPathname.at(m_LoadedPathname.length()-1) != '/')
            m_LoadedPathname.push_back('/');

        // Open the info file
        InfoFileParser infoFile;
        if (infoFile.openFile(m_LoadedPathname + "info.txt") == false)
        {
            TGUI_OUTPUT((((std::string("TGUI: Failed to open ")).append(m_LoadedPathname)).append("info.txt")).c_str());
            return false;
        }

        std::string property;
        std::string value;

        // Set some default settings
        m_SplitImage = false;
        std::string imageExtension = "png";

        // Read untill the end of the file
        while (infoFile.readProperty(property, value))
        {
/*
            if (property.compare("splitimage") == 0)
            {
                // Find out if it is split or not
                if (value.compare("true") == 0)
                    m_SplitImage = true;
                else if (value.compare("false") == 0)
                    m_SplitImage = false;
            }
            else */if (property.compare("extension") == 0)
            {
                imageExtension = value;
            }
        }

        // Close the info file
        infoFile.closeFile();

        // Remove all textures if they were loaded before
        if (m_TextureBack_L != NULL)  TGUI_TextureManager.removeTexture(m_TextureBack_L);
        if (m_TextureBack_M != NULL)  TGUI_TextureManager.removeTexture(m_TextureBack_M);
        if (m_TextureBack_R != NULL)  TGUI_TextureManager.removeTexture(m_TextureBack_R);
        if (m_TextureFront_L != NULL) TGUI_TextureManager.removeTexture(m_TextureFront_L);
        if (m_TextureFront_M != NULL) TGUI_TextureManager.removeTexture(m_TextureFront_M);
        if (m_TextureFront_R != NULL) TGUI_TextureManager.removeTexture(m_TextureFront_R);

        // Load multiple images when the image is split
        if (m_SplitImage)
        {
            return false;
/*
            // load the required textures
            if ((TGUI_TextureManager.getTexture(m_LoadedPathname + "L_Back." + imageExtension, m_TextureBack_L))
             && (TGUI_TextureManager.getTexture(m_LoadedPathname + "M_Back." + imageExtension, m_TextureBack_M))
             && (TGUI_TextureManager.getTexture(m_LoadedPathname + "R_Back." + imageExtension, m_TextureBack_R))
             && (TGUI_TextureManager.getTexture(m_LoadedPathname + "L_Front." + imageExtension, m_TextureFront_L))
             && (TGUI_TextureManager.getTexture(m_LoadedPathname + "M_Front." + imageExtension, m_TextureFront_M))
             && (TGUI_TextureManager.getTexture(m_LoadedPathname + "R_Front." + imageExtension, m_TextureFront_R)))
            {
                m_SpriteBack_L.setTexture(*m_TextureBack_L, true);
                m_SpriteBack_M.setTexture(*m_TextureBack_M, true);
                m_SpriteBack_R.setTexture(*m_TextureBack_R, true);

                m_SpriteFront_L.setTexture(*m_TextureFront_L, true);
                m_SpriteFront_M.setTexture(*m_TextureFront_M, true);
                m_SpriteFront_R.setTexture(*m_TextureFront_R, true);

                m_Loaded = true;
                return true;
            }
            else
                return false;
*/
        }
        else // The image is not split
        {
            // load the required textures
            if ((TGUI_TextureManager.getTexture(m_LoadedPathname + "Back." + imageExtension, m_TextureBack_M))
            && (TGUI_TextureManager.getTexture(m_LoadedPathname + "Front." + imageExtension, m_TextureFront_M)))
            {
                m_SpriteBack_M.setTexture(*m_TextureBack_M, true);
                m_SpriteFront_M.setTexture(*m_TextureFront_M, true);

                m_Loaded = true;

                // Calculate the size of the front image (the size of the part that will be drawn)
                recalculateSize();

                return true;
            }
            else
                return false;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void LoadingBar::setSize(float width, float height)
    {
        // Don't do anything when the loading bar wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // Check if the image is split
        if (m_SplitImage)
        {
//            setScale(width / (m_TextureBack_L->getSize().x + m_TextureBack_M->getSize().x + m_TextureBack_R->getSize().x),
//                     height / m_TextureBack_M->getSize().y);
        }
        else // The image is not split
        {
            setScale(width / m_TextureBack_M->getSize().x,
                     height / m_TextureBack_M->getSize().y);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2u LoadingBar::getSize() const
    {
        // Don't continue when the loading bar wasn't loaded correctly
        if (m_Loaded == false)
            return Vector2u(0, 0);

        // Check if the image is split
        if (m_SplitImage)
        {
            // Return the size of the three images
            return Vector2u(m_TextureBack_L->getSize().x + m_TextureBack_M->getSize().x + m_TextureBack_R->getSize().x, m_TextureBack_M->getSize().y);
        }
        else // The image is not split
        {
            // Return the size of the image
            return Vector2u(m_TextureBack_M->getSize().x, m_TextureBack_M->getSize().y);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f LoadingBar::getScaledSize() const
    {
        // Don't continue when the loading bar wasn't loaded correctly
        if (m_Loaded == false)
            return Vector2f(0, 0);

        // Check if the image is split
        if (m_SplitImage)
        {
            // Return the size of the three images
            return Vector2f((m_TextureBack_L->getSize().x + m_TextureBack_M->getSize().x + m_TextureBack_R->getSize().x) * getScale().x,
                            m_TextureBack_M->getSize().y * getScale().y);
        }
        else // The image is not split
        {
            // Return the size of the image
            return Vector2f(m_TextureBack_M->getSize().x * getScale().x, m_TextureBack_M->getSize().y * getScale().y);
        }
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    std::string LoadingBar::getLoadedPathname()
    {
        return m_LoadedPathname;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void LoadingBar::setMinimum(unsigned int minimum)
    {
        // Set the new minimum
        m_Minimum = minimum;

        // The minimum can never be greater than the maximum
        if (m_Minimum > m_Maximum)
            m_Maximum = m_Minimum;

        // When the value is below the minimum then adjust it
        if (m_Value < m_Minimum)
            m_Value = m_Minimum;

        // Recalculate the size of the front image (the size of the part that will be drawn)
        recalculateSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void LoadingBar::setMaximum(unsigned int maximum)
    {
        // Set the new maximum
        m_Maximum = maximum;

        // The maximum can never be below the minimum
        if (m_Maximum < m_Minimum)
            m_Minimum = m_Maximum;

        // When the value is above the maximum then adjust it
        if (m_Value > m_Maximum)
            m_Value = m_Maximum;

        // Recalculate the size of the front image (the size of the part that will be drawn)
        recalculateSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void LoadingBar::setValue(unsigned int value)
    {
        // Set the new value
        m_Value = value;

        // When the value is below the minimum or above the maximum then adjust it
        if (m_Value < m_Minimum)
            m_Value = m_Minimum;
        else if (m_Value > m_Maximum)
            m_Value = m_Maximum;

        // Recalculate the size of the front image (the size of the part that will be drawn)
        recalculateSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int LoadingBar::incrementValue()
    {
        // When the value is still below the maximum then adjust it
        if (m_Value < m_Maximum)
        {
            ++m_Value;

            // The value has changed, so send a callback (if needed)
            if (callbackID > 0)
            {
                Callback callback;
                callback.callbackID = callbackID;
                callback.trigger    = Callback::valueChanged;
                callback.value      = m_Value;
                m_Parent->addCallback(callback);
            }
        }

        // Recalculate the size of the front image (the size of the part that will be drawn)
        recalculateSize();

        // return the new value
        return m_Value;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int LoadingBar::getMinimum()
    {
        return m_Minimum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int LoadingBar::getMaximum()
    {
        return m_Maximum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int LoadingBar::getValue()
    {
        return m_Value;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool LoadingBar::mouseOnObject(float x, float y)
    {
        // Don't do anything when the loading bar wasn't loaded correctly
        if (m_Loaded == false)
            return false;

        float loadingBarWidth;
        float loadingBarHeight;

        // Get the current scale
        Vector2f curScale = getScale();

        // Calculate the loading bar size
        if (m_SplitImage)
        {
            loadingBarHeight = m_TextureBack_M->getSize().y * curScale.y;

            // Check if the middle part will be drawn (this won't happen when the x scale is too small
            if ((curScale.y * (m_TextureBack_L->getSize().x + m_TextureBack_R->getSize().x))
                < curScale.x * (m_TextureBack_L->getSize().x + m_TextureBack_M->getSize().x + m_TextureBack_R->getSize().x))
            {
                loadingBarWidth =(m_TextureBack_L->getSize().x + m_TextureBack_R->getSize().x + m_TextureBack_M->getSize().x) * getScale().x;
            }
            else // The middle part won't be drawn
            {
                loadingBarWidth = (m_TextureBack_L->getSize().x + m_TextureBack_R->getSize().x) * curScale.y;
            }
        }
        else
        {
            loadingBarWidth = m_TextureBack_M->getSize().x * curScale.x;
            loadingBarHeight = m_TextureBack_M->getSize().y * curScale.y;
        }

        // Check if the mouse is on top of the loading bar
        if ((x > getPosition().x) && (x < getPosition().x + loadingBarWidth)
            && (y > getPosition().y) && (y < getPosition().y + loadingBarHeight))
        {
            return true;
        }
        else // When the mouse is not on top of the loading bar
        {
            m_MouseHover = false;
            return false;
        }

    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void LoadingBar::recalculateSize()
    {
        // Don't calculate anything when the loading bar wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // Get the size of the back sprite
        sf::FloatRect BackBounds = m_SpriteBack_M.getGlobalBounds();

        // Check if the image is split
        if (m_SplitImage)
        {
/*
            float middleSpriteWidth = m_SpriteBack_M.getGlobalBounds().width;

            // Adjust the width of the back sprite because it is wrong when the image is split
            BackBounds.Width = m_SpriteBack_L.getGlobalBounds().width
                                + middleSpriteWidth
                                + m_SpriteBack_R.getGlobalBounds().width;

            // Calculate the width of the front image
            float width;

            if ((m_Maximum - m_Minimum) > 0)
                width = BackBounds.Width * (m_Value / static_cast<float>(m_Maximum - m_Minimum));
            else
                width = static_cast<int>(BackBounds.Width);


            // Create the rect that will store the bounds of our sprite
            sf::IntRect FrontBounds(0, 0, 0, m_TextureFront_M->getSize().y);

            // Check if the value is so small that only the left piece may be drawn
            if (width < m_TextureFront_L->getSize().x)
            {
                // The middle and right image are not drawn
                m_SpriteFront_M.SetTextureRect(FrontBounds);
                m_SpriteFront_R.SetTextureRect(FrontBounds);

                // A piece of the left image must be drawn
                FrontBounds.Width = width;
                m_SpriteFront_L.SetTextureRect(FrontBounds);
            }
            else // We also need to draw the middle image
            {
                // Check if the right image must be drawn
                if (width > m_TextureFront_L->getSize().x + m_TextureFront_M->getSize().x)
                {
                    // The left image is drawn completely
                    FrontBounds.Width = m_SpriteBack_L.getGlobalBounds().width;
                    m_SpriteFront_L.SetTextureRect(FrontBounds);

                    // The middle image is drawn completely
                    FrontBounds.Width = middleSpriteWidth;
                    m_SpriteFront_M.SetTextureRect(FrontBounds);

                    // A piece of the right image must be drawn
                    FrontBounds.Width = width - m_SpriteBack_L.getGlobalBounds().width - middleSpriteWidth;
                    m_SpriteFront_R.SetTextureRect(FrontBounds);
                }
                else // Don't draw the right image
                {
                    // The right image is not drawn
                    m_SpriteFront_R.SetTextureRect(FrontBounds);

                    // The left image is drawn completely
                    FrontBounds.Width = m_SpriteBack_L.getGlobalBounds().width;
                    m_SpriteFront_L.SetTextureRect(FrontBounds);

                    // A piece of the middle image must be drawn
                    FrontBounds.Width = width - m_SpriteBack_L.getGlobalBounds().width;
                    m_SpriteFront_M.SetTextureRect(FrontBounds);
                }
            }
*/
        }
        else // The image is not split
        {
            // Calculate the size of the front sprite
            sf::IntRect FrontBounds(BackBounds);

            // Only change the width when not dividing by zero
            if ((m_Maximum - m_Minimum) > 0)
                FrontBounds.width = static_cast<int>(BackBounds.width * (m_Value / static_cast<float>(m_Maximum - m_Minimum)));
            else
                FrontBounds.width = static_cast<int>(BackBounds.width);

            // Set the size of the front image
            m_SpriteFront_M.setTextureRect(FrontBounds);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void LoadingBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Don't draw when the loading bar wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // Check if the image is split
        if (m_SplitImage)
        {
/*
            // Get the current scale
            Vector2f scale = getScale();

            // Set the position of the image
            states.transform.translate(getPosition());

            // Draw the loading bar
            states.transform.scale(scale.y, scale.y);
            target.draw(m_SpriteBack_L, states);
            target.draw(m_SpriteFront_L, states);



            states.transform.translate(m_SpriteBack_L.getGlobalBounds().width, 0);


            // Calculate the scale for our middle image
            float scaleX = (((m_TextureBack_L->getSize().x + m_TextureBack_M->getSize().x + m_TextureBack_R->getSize().x)  * scale.x)
                            - ((m_TextureBack_L->getSize().x + m_TextureBack_R->getSize().x) * scale.y))
                            / m_TextureBack_M->getSize().x;

            // Set the scale for the middle image
            states.transform.scale(scaleX / scale.y, 1);

            target.draw(m_SpriteBack_M, states);
            target.draw(m_SpriteFront_M, states);

            states.transform.translate(m_SpriteBack_M.getGlobalBounds().width, 0);
            states.transform.scale(scale.y / scaleX, 1);
            target.draw(m_SpriteBack_R, states);
            target.draw(m_SpriteFront_R, states);
*/
        }
        else // The image is not split
        {
            // Adjust the transformation
            states.transform *= getTransform();

            // Draw the loading bar
            target.draw(m_SpriteBack_M, states);
            target.draw(m_SpriteFront_M, states);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////