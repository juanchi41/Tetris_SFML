#include "ViewManager.h"
#include "Tetris.h"
#include "TetrisManager.h"

constexpr int INITIAL_X_POS = 337;
constexpr int INITIAL_Y_POS = 119;
constexpr int NEXT_FUGURE_X_POS = 700;
constexpr int NEXT_FUGURE_Y_POS = 294;
constexpr int RECT_X_SIZE = 28;
constexpr int RECT_Y_SIZE = 21;
constexpr int SCORE_X_POS = 675;
constexpr int SCORE_Y_POS = 170;

ViewManager::ViewManager() : m_font("arial.ttf"), m_text(m_font)
{
	
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
	DrawText("PAUSE", 350, 250, 40, 50);
	m_pWindow->display();
}

void ViewManager::GameOver()
{
	DrawText("GAME OVER", 300, 250, 40, 50);
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
	RenderFigure(m_pTetrisManager->GetCurrFigure(), INITIAL_X_POS, INITIAL_Y_POS);
}

void ViewManager::RenderNextFigure()
{
	RenderFigure(m_pTetrisManager->GetNextFigure(), NEXT_FUGURE_X_POS, NEXT_FUGURE_Y_POS, 0.7);
}

void ViewManager::RenderFigure(const FigureBase* a_pCurrFigure, int a_offsetX, int a_offsetY, double a_perc /*= 1.0*/)
{
	SDL_Rect rect;

	rect.w = int(RECT_X_SIZE * a_perc);
	rect.h = int(RECT_Y_SIZE * a_perc);

	for (const SDL_Point& point : a_pCurrFigure->GetPoints())
	{
		rect.x = a_offsetX + (point.x * int(RECT_X_SIZE * a_perc));
		rect.y = a_offsetY + (point.y * int(RECT_Y_SIZE * a_perc));

		RenderRect(rect, a_pCurrFigure->GetColor());
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
	DrawText(std::to_string(m_pTetrisManager->GetTotalLines()), SCORE_X_POS, SCORE_Y_POS);
}

void ViewManager::RenderCurrentLevel()
{
	DrawText(std::to_string(m_pTetrisManager->GetCurrentLevel()), SCORE_X_POS, 416);
}

void ViewManager::DrawText(const std::string& a_text, sf::Vector2u a_position)
{

}
