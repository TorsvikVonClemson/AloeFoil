/*Creates a clickable button with centered text.
x and y designates the top left corner of the button
w and h describes in an intiger how many tiles wide
sprite size is the square size of each sprite tile. multiple sheets should keep each part at set locations
imgPos is the position of a sprite to be placed in the center of the button
text is the text to be printed
sheet is the renderable for the spriteSheet
Font is self explanitory*/
#pragma once

#include <string>
#include <SDL.h>
#include "../Graphics/Rendering/Renderable.h"
#include "../Graphics/Rendering/trueType.h"
#include "../Graphics/Window/window.h"
#include "maths.h"

class Button
{
public:
	Button(int x,int y, int w, int h,int spriteSize, std::string text, Renderable* sheet, TrueType* font,Window* window, Renderer* renderer);
	~Button();
	void setEffect(int effect, SDL_Color textColor);
	bool render(SDL_Rect* viewPort);
	bool events();
	void updateText(std::string text);

private:
	int m_X, m_Y, m_W, m_H, m_SpriteSize,m_ImgPos,m_Effect;

	bool m_Highlight = false,m_Activate=false;

	std::string m_Text;

	SDL_Rect m_Sprite[100];
	Renderable* m_Sheet = NULL;
	TrueType* m_Font = NULL;
	Window* m_Window = NULL;
	Renderer* m_Renderer = NULL;
	SDL_Color m_TextColor = { 0xFF, 0xFF, 0xFF };
	Maths* m_Maths =NULL;
};