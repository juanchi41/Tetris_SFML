#include "Figures.h"

void FigureBase::Rotate()
{
	if (CanRotate())
	{
		/*sf::Vector2i offset = m_points[GetPivotPoint()];

		Move(-offset.x, -offset.y);

		for (sf::Vector2i& point : m_points)
		{
			sf::Vector2i temp = point;
			point.x = temp.y;
			point.y = -temp.x;
		}

		Move(offset.x, offset.y);*/

		for (sf::Vector2i& point : m_points)
		{
			point.rotatedBy(sf::degrees(-90.f));
		}
	}
}

void FigureBase::UndoRotate()
{
	if (CanRotate())
	{
		/*sf::Vector2i offset = m_points[GetPivotPoint()];

		Move(-offset.x, -offset.y);

		for (sf::Vector2i& point : m_points)
		{
			sf::Vector2i temp = point;
			point.x = -temp.y;
			point.y = temp.x;
		}

		Move(offset.x, offset.y);*/

		for (sf::Vector2i& point : m_points)
		{
			point.rotatedBy(sf::degrees(-90.f));
		}
	}
}


void FigureBase::Move(sf::Vector2i a_offset)
{
	for (sf::Vector2i& point : m_points)
	{
		point.x += a_offset.x;
		point.y += a_offset.y;
	}
}


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
void IFigure::SetInitialPosition(const sf::Vector2i& a_point)
{
	m_points[0] = a_point;
	m_points[1].x = a_point.x + 1;
	m_points[1].y = a_point.y;
	m_points[2].x = a_point.x + 2;
	m_points[2].y = a_point.y;
	m_points[3].x = a_point.x + 3;
	m_points[3].y = a_point.y;
}

void JFigure::SetInitialPosition(const sf::Vector2i& a_point)
{
	m_points[0].x = a_point.x - 1;
	m_points[0].y = a_point.y;
	m_points[1] = a_point;
	m_points[2].x = a_point.x + 1;
	m_points[2].y = a_point.y;
	m_points[3].x = a_point.x + 1;
	m_points[3].y = a_point.y + 1;
}

void LFigure::SetInitialPosition(const sf::Vector2i& a_point)
{
	m_points[0].x = a_point.x - 1;
	m_points[0].y = a_point.y;
	m_points[1] = a_point;
	m_points[2].x = a_point.x + 1;
	m_points[2].y = a_point.y;
	m_points[3].x = a_point.x - 1;
	m_points[3].y = a_point.y + 1;
}

void OFigure::SetInitialPosition(const sf::Vector2i& a_point)
{
	m_points[0] = a_point;
	m_points[1].x = a_point.x + 1;
	m_points[1].y = a_point.y;
	m_points[2].x = a_point.x;
	m_points[2].y = a_point.y + 1;
	m_points[3].x = a_point.x + 1;
	m_points[3].y = a_point.y + 1;
}

void SFigure::SetInitialPosition(const sf::Vector2i& a_point)
{
	m_points[0].x = a_point.x + 1;
	m_points[0].y = a_point.y;
	m_points[1] = a_point;
	m_points[2].x = a_point.x;
	m_points[2].y = a_point.y + 1;
	m_points[3].x = a_point.x - 1;
	m_points[3].y = a_point.y + 1;
}

void TFigure::SetInitialPosition(const sf::Vector2i& a_point)
{
	m_points[0] = a_point;
	m_points[1].x = a_point.x + 1;
	m_points[1].y = a_point.y;
	m_points[2].x = a_point.x + 2;
	m_points[2].y = a_point.y;
	m_points[3].x = a_point.x + 1;
	m_points[3].y = a_point.y + 1;
}

void ZFigure::SetInitialPosition(const sf::Vector2i& a_point)
{
	m_points[0] = a_point;
	m_points[1].x = a_point.x + 1;
	m_points[1].y = a_point.y;
	m_points[2].x = a_point.x + 1;
	m_points[2].y = a_point.y + 1;
	m_points[3].x = a_point.x + 2;
	m_points[3].y = a_point.y + 1;
}
