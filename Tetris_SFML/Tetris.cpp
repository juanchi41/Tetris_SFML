#include "Tetris.h"
#include <time.h>

constexpr int SCREEN_WIDTH = 900;
constexpr int SCREEN_HEIGHT = 600;

Tetris::Tetris()
{
	sf::VideoMode mode;

	mode.size = { SCREEN_WIDTH, SCREEN_HEIGHT };
	mode.bitsPerPixel = 32;
	m_pWindow = std::make_unique<sf::RenderWindow>(mode, "Tetris", sf::State::Windowed);
}

void Tetris::StartGame()
{
	m_tetrisManager.Init();
	m_viewManager.Init(m_pWindow, &m_tetrisManager);
	m_level = 1;

	Start();
}

void Tetris::Start()
{
	m_isRunning = true;

	srand((unsigned)time(nullptr));

	while (m_isRunning)
	{
		HandleEvents();
		Update();
		Render();
		CheckGameOver();
	}
}

void Tetris::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_isRunning = false;
		break;
	case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				if (m_gameStatus == eGameStatus::PLAYING)
				{
					m_tetrisManager.MoveToLeft();
				}
				break;
			case SDLK_RIGHT:
				if (m_gameStatus == eGameStatus::PLAYING)
				{
					m_tetrisManager.MoveToRight();
				}
				break;
			case SDLK_DOWN:
				if (m_gameStatus == eGameStatus::PLAYING)
				{
					m_tetrisManager.MoveDown();
				}
				break;
			case SDLK_SPACE:
				if (m_gameStatus == eGameStatus::PLAYING)
				{
					m_tetrisManager.Rotate();
				}
				break;
			case SDLK_RETURN:
				if (m_gameStatus == eGameStatus::MAIN_MENU)
				{
					m_gameStatus = eGameStatus::PLAYING;
					m_tetrisManager.Start(m_level);
				}
				else if (m_gameStatus == eGameStatus::GAME_OVER)
				{
					m_gameStatus = eGameStatus::MAIN_MENU;
				}
				break;
			case SDLK_ESCAPE:
				if (m_gameStatus == eGameStatus::PLAYING)
				{
					m_gameStatus = eGameStatus::PAUSE_MENU;
				}
				else if (m_gameStatus == eGameStatus::PAUSE_MENU)
				{
					m_gameStatus = eGameStatus::PLAYING;
				}
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

void Tetris::Update()
{
	if (m_gameStatus == eGameStatus::PLAYING)
	{
		m_tetrisManager.Update();
	}
}

void Tetris::Render()
{
	switch (m_gameStatus)
	{
	case eGameStatus::MAIN_MENU:
		m_viewManager.ShowMainMenu();
		break;
	case eGameStatus::PLAYING:
		m_viewManager.Render();
		break;
	case eGameStatus::PAUSE_MENU:
		m_viewManager.ShowPauseMenu();
		break;
	case eGameStatus::GAME_OVER:
		m_viewManager.GameOver();
		break;
	}
}

void Tetris::CheckGameOver()
{
	if (m_gameStatus == eGameStatus::PLAYING && m_tetrisManager.GameOver())
	{
		m_gameStatus = eGameStatus::GAME_OVER;
		m_tetrisManager.Clear();
	}
}
