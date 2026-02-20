#include "TetrisManager.h"
#include "Figures.h"

constexpr int MAX_LEVEL = 18;

void TetrisManager::Init()
{
	m_gameBoard.assign(GAME_BOARD_TOTAL_ROWS, std::vector<sf::Color>(GAME_BOARD_TOTAL_COLUMNS));
	Clear();
}

void TetrisManager::Clear()
{
	m_bGameOver = false;
	m_nTotalLines = 0;
	m_lastTick = 0;
	m_pCurrFigure.reset();
	m_pNextFigure.reset();
	m_boardPoints.clear();
	m_figureStatistics.assign(N_FIGURES, 0);

	for (std::vector<sf::Color>& row : m_gameBoard)
	{
		ClearRow(row);
	}
}

void TetrisManager::ClearRow(std::vector<sf::Color>& a_row)
{
	for (sf::Color& item : a_row)
	{
		memset(&item, 0, sizeof(sf::Color));
	}
}

void TetrisManager::Start(int a_level)
{
	m_level = a_level;
	m_pCurrFigure = CreateNewFigure();
	m_pNextFigure = CreateNewFigure();

	SetInitialPositions();
}

std::unique_ptr<FigureBase> TetrisManager::CreateNewFigure() const
{
	int nFigure = rand() % N_FIGURES;

	return FigureFactory::CreateFigure(nFigure);
}

void TetrisManager::SetInitialPositions()
{
	sf::Vector2i point;

	point.x = (GAME_BOARD_TOTAL_COLUMNS + 1) / 2;
	point.y = 0;
	m_pCurrFigure->SetInitialPosition(point);

	point.x = 0;
	m_pNextFigure->SetInitialPosition(point);

	if (!AreValidPositions(m_pCurrFigure->GetPoints()))
	{
		m_bGameOver = true;
	}
}

bool TetrisManager::AreValidPositions(const std::vector<sf::Vector2i>& a_points, int a_offsetX, int a_offsetY) const
{
	for (const sf::Vector2i& point : a_points)
	{
		if (!IsValidPosition(point, a_offsetX, a_offsetY))
		{
			return false;
		}
	}

	return true;
}

bool TetrisManager::IsValidPosition(const sf::Vector2i& a_point, int a_offsetX, int a_offsetY) const
{
	int x = a_point.x + a_offsetX;
	int y = a_point.y + a_offsetY;

	return (x >= 0 && x < GAME_BOARD_TOTAL_COLUMNS && y >= 0 && y < GAME_BOARD_TOTAL_ROWS && IsEmptyPosition(m_gameBoard[y][x]));
}

bool TetrisManager::MoveToLeft()
{
	m_pCurrFigure->MoveToLeft();

	if (!AreValidPositions(m_pCurrFigure->GetPoints()))
	{
		m_pCurrFigure->MoveToRight();
		return false;
	}

	return true;
}

bool TetrisManager::MoveToRight()
{
	m_pCurrFigure->MoveToRight();

	if (!AreValidPositions(m_pCurrFigure->GetPoints()))
	{
		m_pCurrFigure->MoveToLeft();
		return false;
	}

	return true;
}

bool TetrisManager::MoveDown()
{
	m_pCurrFigure->MoveDown();

	if (!AreValidPositions(m_pCurrFigure->GetPoints()))
	{
		m_pCurrFigure->MoveUp();
		return false;
	}

	return true;
}

void TetrisManager::Rotate()
{
	m_pCurrFigure->Rotate();

	if (!AreValidPositions(m_pCurrFigure->GetPoints()))
	{
		m_pCurrFigure->UndoRotate();
	}
}

void TetrisManager::Update()
{
	std::int32_t currTick = m_clock.getElapsedTime().asMilliseconds();

	if (currTick >= m_lastTick + std::int32_t(1000 / m_level))
	{
		m_lastTick = currTick;

		if (!MoveDown())
		{
			std::set<int> figureRows;

			//Colisión! Metemos la figura en el tablero
			for (const sf::Vector2i& point : m_pCurrFigure->GetPoints())
			{
				m_gameBoard[point.y][point.x] = m_pCurrFigure->GetColor();
				figureRows.insert(point.y);
			}

			++m_figureStatistics[m_pCurrFigure->Type()];
			m_pCurrFigure = std::move(m_pNextFigure);
			m_pNextFigure = CreateNewFigure();

			SetInitialPositions();
			CheckRows(figureRows);
			CalcBoardPoints();
		}
	}
}

void TetrisManager::CheckRows(const std::set<int>& a_figureRows)
{
	std::vector<int> rowsToRemove;

	for (int nRow : a_figureRows)
	{
		const std::vector<sf::Color>& row = m_gameBoard[nRow];
		bool bRemoveThisRow = true;

		for (const sf::Color& item : row)
		{
			if (IsEmptyPosition(item))
			{
				bRemoveThisRow = false;
				break;
			}
		}

		if (bRemoveThisRow)
		{
			rowsToRemove.push_back(nRow);
		}
	}

	RemoveRows(rowsToRemove);
}

void TetrisManager::RemoveRows(const std::vector<int>& a_rowsToRemove)
{
	for (int row : a_rowsToRemove)
	{
		for (int i = row; i > 0; --i)
		{
			m_gameBoard[i] = m_gameBoard[i - 1];
		}

		ClearRow(m_gameBoard[0]);
		++m_nTotalLines;
	}

	if (m_level < MAX_LEVEL && ((m_nTotalLines / 10) + 1) > m_level)
	{
		++m_level;
	}
}

void TetrisManager::CalcBoardPoints()
{
	PointToDraw point;

	m_boardPoints.clear();

	for (int x = 0; x < GAME_BOARD_TOTAL_COLUMNS; ++x)
	{
		for (int y = 0; y < GAME_BOARD_TOTAL_ROWS; ++y)
		{
			const sf::Color& item = m_gameBoard[y][x];

			if (!IsEmptyPosition(item))
			{
				point.m_point.x = x;
				point.m_point.y = y;
				point.m_color.r = item.r;
				point.m_color.g = item.g;
				point.m_color.b = item.b;
				point.m_color.a = item.a;
				m_boardPoints.push_back(point);
			}
		}
	}
}
