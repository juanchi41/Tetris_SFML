#pragma once

#include <SFML/Graphics.hpp>
#include "TetrisManager.h"
#include "ViewManager.h"

enum class eGameStatus
{
	MAIN_MENU,
	PLAYING,
	PAUSE_MENU,
	GAME_OVER
};

class Tetris
{
public:
	Tetris();
	~Tetris() = default;

	void StartGame();
	inline int GetLevel() const { return m_level; }

private:
	void Start();
	void HandleEvents();
	void PollEvents();
	void Update();
	void Render();
	void CheckGameOver();

	eGameStatus m_gameStatus = eGameStatus::MAIN_MENU;
	bool m_isRunning = false;
	int m_level;
	std::unique_ptr<sf::RenderWindow> m_pWindow;
	TetrisManager m_tetrisManager;
	ViewManager m_viewManager;
};
