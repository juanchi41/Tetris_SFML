#include "ViewManager.h"
#include "Tetris.h"
#include "TetrisManager.h"

constexpr float INITIAL_X_POS = 337.f;
constexpr float INITIAL_Y_POS = 119.f;
constexpr float NEXT_FUGURE_X_POS = 700.f;
constexpr float NEXT_FUGURE_Y_POS = 294.f;
constexpr float RECT_X_SIZE = 28.f;
constexpr float RECT_Y_SIZE = 21.f;
constexpr float SCORE_X_POS = 675.f;
constexpr float SCORE_Y_POS = 170.f;

ViewManager::ViewManager() : m_pauseText(m_font), m_gameOverText(m_font), m_scoreText(m_font), m_levelText(m_font)
{
	m_font.openFromFile("arial.ttf");
	m_pauseText.setPosition({ 300.f, 250.f });
	m_pauseText.setString("PAUSE");
	m_gameOverText.setPosition({ 300.f, 250.f });
	m_gameOverText.setString("GAME OVER");
	m_scoreText.setPosition({ SCORE_X_POS, SCORE_Y_POS });
	m_levelText.setPosition({ SCORE_X_POS, 416.f });
}

void ViewManager::Init(sf::RenderWindow* a_pWindow, const TetrisManager* a_pTetrisManager)
{
	m_pWindow = a_pWindow;
	m_pTetrisManager = a_pTetrisManager;

	// Load Texture atlas for text rendering
	m_mainScreenSprite.SetTexture("MainScreen.png");
	m_playingBgSprite.SetTexture("tetris_900x600.png");
}

void ViewManager::ShowMainMenu()
{
	m_pWindow->clear();
	m_pWindow->draw(m_mainScreenSprite.GetSprite());
	m_pWindow->display();
}

void ViewManager::Render()
{
	m_pWindow->clear();

	m_pWindow->draw(m_playingBgSprite.GetSprite());

	RenderCurrGameBoard();
	RenderCurrFigure();
	RenderNextFigure();
	RenderCurrentScore();
	RenderCurrentLevel();

	m_pWindow->display();
}

void ViewManager::ShowPauseMenu()
{
	m_pWindow->clear();
	m_pWindow->draw(m_mainScreenSprite.GetSprite());
	m_pWindow->draw(m_pauseText);
	m_pWindow->display();
}

void ViewManager::GameOver()
{
	m_pWindow->draw(m_gameOverText);
	m_pWindow->display();
}

void ViewManager::RenderCurrGameBoard()
{
	const std::vector<PointToDraw>& points = m_pTetrisManager->GetGameBoardPoints();
	sf::RectangleShape rect({ RECT_X_SIZE, RECT_Y_SIZE });

	for (const PointToDraw& point : points)
	{
		rect.setPosition({ INITIAL_X_POS + (point.m_point.x * RECT_X_SIZE), INITIAL_Y_POS + (point.m_point.y * RECT_Y_SIZE) });
		rect.setFillColor(point.m_color);
		
		RenderRect(rect);
	}
}

void ViewManager::RenderCurrFigure()
{
	RenderFigure(m_pTetrisManager->GetCurrFigure(), INITIAL_X_POS, INITIAL_Y_POS, 1.0);
}

void ViewManager::RenderNextFigure()
{
	RenderFigure(m_pTetrisManager->GetNextFigure(), NEXT_FUGURE_X_POS, NEXT_FUGURE_Y_POS, 0.7);
}

void ViewManager::RenderFigure(const FigureBase* a_pCurrFigure, float a_offsetX, float a_offsetY, double a_perc)
{
	sf::RectangleShape rect({ float(RECT_X_SIZE * a_perc), float(RECT_Y_SIZE * a_perc) });

	for (const sf::Vector2i& point : a_pCurrFigure->GetPoints())
	{
		rect.setPosition({ a_offsetX + float(point.x * int(RECT_X_SIZE * a_perc)), a_offsetY + float(point.y * int(RECT_Y_SIZE * a_perc)) });
		rect.setFillColor(a_pCurrFigure->GetColor());

		RenderRect(rect);
	}
}

void ViewManager::RenderRect(const sf::RectangleShape& a_rect)
{
	m_pWindow->draw(a_rect);

	/*SDL_SetRenderDrawColor(m_pRenderer, a_color.r, a_color.g, a_color.b, a_color.a);
	SDL_RenderFillRect(m_pRenderer, &a_rect);
	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, a_color.a);
	SDL_RenderDrawLine(m_pRenderer, a_rect.x, a_rect.y, (a_rect.x + a_rect.w), a_rect.y);
	SDL_RenderDrawLine(m_pRenderer, a_rect.x, a_rect.y, a_rect.x, (a_rect.y + a_rect.h));
	SDL_RenderDrawLine(m_pRenderer, (a_rect.x + a_rect.w), a_rect.y, (a_rect.x + a_rect.w), (a_rect.y + a_rect.h));
	SDL_RenderDrawLine(m_pRenderer, a_rect.x, (a_rect.y + a_rect.h), (a_rect.x + a_rect.w), (a_rect.y + a_rect.h));*/
}

void ViewManager::RenderCurrentScore()
{
	m_scoreText.setString(std::to_string(m_pTetrisManager->GetTotalLines()));
	m_pWindow->draw(m_scoreText);
}

void ViewManager::RenderCurrentLevel()
{
	m_levelText.setString(std::to_string(m_pTetrisManager->GetCurrentLevel()));
	m_pWindow->draw(m_levelText);
}
