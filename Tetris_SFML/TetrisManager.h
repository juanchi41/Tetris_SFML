#pragma once

#include <vector>
#include <set>
#include "Figures.h"
#include <SFML/Graphics.hpp>

constexpr int GAME_BOARD_TOTAL_ROWS = 19;
constexpr int GAME_BOARD_TOTAL_COLUMNS = 10;

struct PointToDraw
{
	sf::Vector2i m_point;
	sf::Color m_color;
};

class TetrisManager
{
public:
	TetrisManager() = default;
	~TetrisManager() = default;

	void Init();
	void Clear();
	void Start(int a_level);
	inline bool GameOver() const { return m_bGameOver; }
	bool MoveToLeft();
	bool MoveToRight();
	bool MoveDown();
	void Rotate();
	void Update();

	int GetTotalLines() const { return m_nTotalLines; }
	int GetCurrentLevel() const { return m_level; }
	const FigureBase* GetCurrFigure() const { return m_pCurrFigure.get(); }
	const FigureBase* GetNextFigure() const { return m_pNextFigure.get(); }
	const std::vector<PointToDraw>& GetGameBoardPoints() const { return m_boardPoints; }

private:
	void ClearRow(std::vector<sf::Color>& a_row);
	std::unique_ptr<FigureBase> CreateNewFigure() const;
	void SetInitialPositions();
	bool AreValidPositions(const std::vector<sf::Vector2i>& a_points, int a_offsetX = 0, int a_offsetY = 0) const;
	bool IsValidPosition(const sf::Vector2i& a_point, int a_offsetX, int a_offsetY) const;
	void CheckRows(const std::set<int>& a_figureRows);
	void CalcBoardPoints();
	void RemoveRows(const std::vector<int>& a_rowsToRemove);
	inline bool IsEmptyPosition(const sf::Color& item) const { return item.r == 0 && item.g == 0 && item.b == 0; }

	bool m_bGameOver = false;
	int m_nTotalLines = 0;
	int m_level = 1;
	std::uint32_t m_lastTick = 0;
	sf::Clock m_clock;
	std::unique_ptr<FigureBase> m_pCurrFigure;
	std::unique_ptr<FigureBase> m_pNextFigure;
	std::vector<std::vector<sf::Color>> m_gameBoard;
	std::vector<PointToDraw> m_boardPoints;
	std::vector<int> m_figureStatistics;
};
