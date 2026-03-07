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
	m_viewManager.Init(m_pWindow.get(), &m_tetrisManager);
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
	while (std::optional<sf::Event> event = m_pWindow->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_isRunning = false;
		}
		else if (event->is<sf::Event::KeyPressed>())
		{
			if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter)
			{
				if (m_gameStatus == eGameStatus::MAIN_MENU)
				{
					m_gameStatus = eGameStatus::PLAYING;
					m_tetrisManager.Start(m_level);
				}
				else if (m_gameStatus == eGameStatus::GAME_OVER)
				{
					m_gameStatus = eGameStatus::MAIN_MENU;
				}
			}
			else if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
			{
				if (m_gameStatus == eGameStatus::PLAYING)
				{
					m_gameStatus = eGameStatus::PAUSE_MENU;
				}
				else if (m_gameStatus == eGameStatus::PAUSE_MENU)
				{
					m_gameStatus = eGameStatus::PLAYING;
				}
			}
			else if (m_gameStatus == eGameStatus::PLAYING)
			{
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down)
				{
					m_tetrisManager.MoveDown();
				}
				else if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Left)
				{
					m_tetrisManager.MoveToLeft();
				}
				else if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Right)
				{
					m_tetrisManager.MoveToRight();
				}
				else if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space)
				{
					m_tetrisManager.Rotate();
				}
			}
		}
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
