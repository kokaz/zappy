#include "AWidget.hpp"

AWidget::AWidget(int x, int y, int height, int width)
  : _text()
{
  _hover = false;
  _x = x;
  _y = y;
  _height = height;
  _width = width;
  _square = NULL;
  _squareHover = NULL;
  _text.initialize();
}

AWidget::~AWidget()
{
  if (_square != NULL)
    delete _square;
  if (_squareHover != NULL)
    delete _squareHover;
}

bool	AWidget::isClicked(int x, int y)
{
  if (x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height))
    return (true);
  else
    return (false);
}

void	AWidget::refresh(int width, int height, float xRatio, float yRatio)
{
  _width = width / 2;
  _height = height / 11.25f;
  _x = width / xRatio;
  _y = height / yRatio;
  _square->setPos(_x, _y);
  _square->setSize(_width, _height);
  if (_squareHover != NULL)
    {
      _squareHover->setPos(_x, _y);
      _squareHover->setSize(_width, _height);
    }
}

void	AWidget::draw()
{
}

void	AWidget::onDisplay(const std::list<std::string> &/*text*/, int /*filePos*/)
{
}

void	AWidget::init()
{
}

void	AWidget::setSquare(Square *square)
{
  _square = square;
}

Square	*AWidget::getSquare() const
{
  return (_square);
}

int	AWidget::getX() const
{
  return (_x);
}

int	AWidget::getY() const
{
  return (_y);
}

int	AWidget::getHeight() const
{
  return (_height);
}

int	AWidget::getWidth() const
{
  return (_width);
}

const Text	&AWidget::getText() const
{
  return (_text);
}

void	AWidget::update(int x, int y)
{
  if (isClicked(x, y))
    _hover = true;
  else
    _hover = false;
}
