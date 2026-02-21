#pragma once

#include <SFML/Graphics.hpp>

class TetrisManager;
class FigureBase;

class SpriteInfo
{
public:
	SpriteInfo() : m_sprite(m_texture)
	{

	}

	void SetTexture(const std::filesystem::path& filename)
	{
		if (m_texture.loadFromFile(filename))
		{
			m_sprite.setTexture(m_texture, true);
		}
	}

	const sf::Sprite& GetSprite() const { return m_sprite; }

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

class ViewManager
{
public:
	ViewManager();
	~ViewManager() = default;
	void Init(sf::RenderWindow* a_pWindow, const TetrisManager* a_pTetrisManager);

	void ShowMainMenu();
	void Render();
	void ShowPauseMenu();
	void GameOver();

private:
	void RenderCurrGameBoard();
	void RenderCurrFigure();
	void RenderNextFigure();
	void RenderFigure(const FigureBase* a_pCurrFigure, float a_offsetX, float a_offsetY, double a_perc = 1.0);
	void RenderRect(const sf::RectangleShape& a_rect);
	void RenderCurrentScore();
	void RenderCurrentLevel();

	sf::RenderWindow* m_pWindow = nullptr;
	const TetrisManager* m_pTetrisManager = nullptr;
	SpriteInfo m_mainScreenSprite;
	SpriteInfo m_playingBgSprite;
	sf::Font m_font;
	sf::Text m_pauseText;
	sf::Text m_gameOverText;
	sf::Text m_scoreText;
	sf::Text m_levelText;
};
