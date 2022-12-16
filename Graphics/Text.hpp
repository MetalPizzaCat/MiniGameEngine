#pragma once

#include "Video.hpp"

/// @brief Helper class that wraps texture info.
class Text
{
public:
    /// @brief Creates a new instance of the text object generating text texture using default font
    /// @param video Pointer to global graphics object
    /// @param text Text to display
    /// @param color Color of the text
    /// @param pos Location
    Text(Video *video, std::string const &text, Color color, Vector2 pos) : m_position(pos),
                                                                            m_scale(1, 1),
                                                                            m_video(video),
                                                                            m_color(color)

    {
        setText(text);
    }

    /// @brief Draw using stored pointer to the video object
    void draw();

    /// @brief Set new value for text and regenerate the texture
    /// @param text New value for text
    void setText(std::string const &text);
    std::string getText() const { return m_text; }

    /// @brief Set new value for color and regenerate the texture
    /// @param color New value for color
    void setColor(Color color);
    Color getColor() const { return m_color; }

    static void bindLua(lua_State *state);

    ~Text()
    {
        SDL_DestroyTexture(m_texture);
    }

private:
    Vector2 m_position;
    Vector2 m_scale;
    SDL_Texture *m_texture = nullptr;
    std::string m_text;
    int32_t m_textWidth;
    int32_t m_textHeight;
    Video *m_video;
    Color m_color;
};