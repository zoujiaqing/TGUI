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


#ifndef _TGUI_PICTURE_INCLUDED_
#define _TGUI_PICTURE_INCLUDED_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    struct TGUI_API Picture : public OBJECT
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Picture();
        
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Picture(const Picture& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~Picture();
        
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Overload of assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Picture& operator= (const Picture& right);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // Load an image from a file.
        //
        // return: true on success
        //         false when the image couldn't be loaded (probalby not found)
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        bool load(const std::string filename);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // Changes the size of the picture. Note that this function will undo all scaling, as it just
        // calculates the correct scale factors for you. It is an alternative to setScale.
        // Note that the picture has to be loaded correctly before calling this function.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(float width, float height);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the size of the picture, unaffected by scaling.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2u getSize() const;
        
        
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the size of the picture, after the scaling transformation.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f getScaledSize() const;

        
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the filename that was used to load the picture.
        // When the picture has not been loaded yet then this function will return an empty string.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getLoadedFilename();
        

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // These functions are used to receive callback from the EventManager.
        // You normally don't need them, but you can use them to simulate an event.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseOnObject(float x, float y);
        void leftMousePressed(float x, float y);
        void leftMouseReleased(float x, float y);
        
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Because this struct is derived from sf::Drawable, you can just call the draw function from your sf::RenderTarget.
        // This function will be called and it will draw the picture on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        sf::Texture* m_Texture; // The SFML texture
        sf::Sprite   m_Sprite;   // The SFML sprite
        
        // The filename used to load the picture
        std::string m_LoadedFilename;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_TGUI_PICTURE_INCLUDED_