#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

enum eFigureType
{
	I_FIGURE,
	J_FIGURE,
	L_FIGURE,
	O_FIGURE,
	S_FIGURE,
	T_FIGURE,
	Z_FIGURE,
	N_FIGURES
};

class FigureBase
{
public:
	FigureBase()
	{
		m_color.r = 0;
		m_color.g = 0;
		m_color.b = 0;
		m_color.a = 255;
		m_points.resize(4);
	}
	virtual ~FigureBase() {}

	virtual eFigureType Type() const = 0;
	virtual void SetInitialPosition(const sf::Vector2i& a_point) = 0;
	virtual bool CanRotate() const { return true; }
	void Rotate();
	void UndoRotate();
	inline void MoveUp() { Move(0, -1); }
	inline void MoveDown() { Move(0, 1); }
	inline void MoveToLeft() { Move(-1, 0); }
	inline void MoveToRight() { Move(1, 0); }
	const std::vector<sf::Vector2i>& GetPoints() const { return m_points; };
	virtual int GetPivotPoint() const { return 0; }
	const sf::Color& GetColor() const { return m_color; }

protected:
	void Move(sf::Vector2i a_offset);

	std::vector<sf::Vector2i> m_points;
	sf::Color m_color;
};


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
class IFigure : public FigureBase
{
public:
	IFigure()
	{
		//Cyan
		m_color.r = 0;
		m_color.g = 255;
		m_color.b = 255;
	}

	eFigureType Type() const override { return I_FIGURE; }
	void SetInitialPosition(const sf::Vector2i& a_point) override;
	int GetPivotPoint() const override { return 1; }
};

class JFigure : public FigureBase
{
public:
	JFigure()
	{
		//Blue
		m_color.r = 0;
		m_color.g = 0;
		m_color.b = 255;
	}

	eFigureType Type() const override { return J_FIGURE; }
	void SetInitialPosition(const sf::Vector2i& a_point) override;
	int GetPivotPoint() const override { return 1; }
};

class LFigure : public FigureBase
{
public:
	LFigure()
	{
		//Orange
		m_color.r = 255;
		m_color.g = 165;
		m_color.b = 0;
	}

	eFigureType Type() const override { return L_FIGURE; }
	void SetInitialPosition(const sf::Vector2i& a_point) override;
	int GetPivotPoint() const override { return 1; }
};

class OFigure : public FigureBase
{
public:
	OFigure()
	{
		//Yellow
		m_color.r = 255;
		m_color.g = 255;
		m_color.b = 0;
	}
	bool CanRotate() const override { return false; }

	eFigureType Type() const override { return O_FIGURE; }
	void SetInitialPosition(const sf::Vector2i& a_point) override;
};

class SFigure : public FigureBase
{
public:
	SFigure()
	{
		//Red
		m_color.r = 255;
		m_color.g = 0;
		m_color.b = 0;
	}

	eFigureType Type() const override { return S_FIGURE; }
	void SetInitialPosition(const sf::Vector2i& a_point) override;
	int GetPivotPoint() const override { return 2; }
};

class TFigure : public FigureBase
{
public:
	TFigure()
	{
		//Magenta
		m_color.r = 255;
		m_color.g = 0;
		m_color.b = 255;
	}

	eFigureType Type() const override { return T_FIGURE; }
	void SetInitialPosition(const sf::Vector2i& a_point) override;
	int GetPivotPoint() const override { return 1; }
};

class ZFigure : public FigureBase
{
public:
	ZFigure()
	{
		//Green
		m_color.r = 0;
		m_color.g = 255;
		m_color.b = 0;
	}

	eFigureType Type() const override { return Z_FIGURE; }
	void SetInitialPosition(const sf::Vector2i& a_point) override;
	int GetPivotPoint() const override { return 2; }
};


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
class FigureFactory
{
public:
	static std::unique_ptr<FigureBase> CreateFigure(int nFigure)
	{
		switch (nFigure)
		{
		case I_FIGURE:
			return std::make_unique<IFigure>();
		case J_FIGURE:
			return std::make_unique<JFigure>();
		case L_FIGURE:
			return std::make_unique<LFigure>();
		case O_FIGURE:
			return std::make_unique<OFigure>();
		case S_FIGURE:
			return std::make_unique<SFigure>();
		case T_FIGURE:
			return std::make_unique<TFigure>();
		case Z_FIGURE:
			return std::make_unique<ZFigure>();
		default:
			return nullptr;
		}
	}
};