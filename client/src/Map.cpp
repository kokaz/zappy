#include "Map.hpp"

Map::Map(): _map(NULL), _x(0), _y(0)
{

}

Map::~Map()
{
  if (_map != NULL)
    delete _map;
}

void Map::createMap(int x, int y)
{
  _map = new unsigned char[x * y];
  _x = x;
  _y = y;
}

unsigned char &Map::operator[](int coord) const
{
  if (_map != NULL && coord >= 0 && coord <= _x * _y)
    return (_map[coord]);
  throw(Exception("Not in the map"));
}

int Map::getSize() const
{
  return (_x * _y);
}

int Map::getX() const
{
  return (_x);
}

int Map::getY() const
{
  return (_y);
}

void Map::addPlayer(t_player *player)
{
  if (player->nb < 0 || (player->x < 0 || player->x > _x)
      || (player->y < 0 || player->y > _y) || (player->lvl < 0 || player->lvl > 8)
      || (player->orient < NORTH || player->orient > WEST))
    delete player;
  else
    _player.push_back(player);
}

void Map::updatePlayerPos(int nb, int x, int y, int orient)
{
  if ((x < 0 || x > _x) || (y < 0 || y > _y)
      || (orient < NORTH || orient > WEST))
    return ;
  for (std::list<t_player *>::iterator it = _player.begin();it != _player.end();++it)
    if ((*it)->nb == nb)
      {
	(*it)->x = x;
	(*it)->y = y;
	(*it)->orient = orient;
	return ;
      }
}


void Map::updatePlayerLvl(int nb, int lvl)
{
  if (lvl < 0 || lvl > 8)
    return ;
  for (std::list<t_player *>::iterator it = _player.begin();it != _player.end();++it)
    if ((*it)->nb == nb)
      {
	(*it)->lvl = lvl;
	return ;
      }
}

void Map::updatePlayerAction(int nb, Action act)
{
  for (std::list<t_player *>::iterator it = _player.begin();it != _player.end();++it)
    if ((*it)->nb == nb)
      {
	(*it)->cuAction = act;
	return ;
      }
}

void Map::addEgg(t_egg *egg)
{
  if (egg->nb < 0 || (egg->x < 0 || egg->x > _x) || (egg->y < 0 || egg->y > _y))
    delete egg;
  else
    _egg.push_back(egg);
}

void Map::display() const
{
  if (!_map)
    return ;
  for (int x = 0;x < _x;++x)
    {
      for (int y = 0;y < _y;++y)
	{
	  std::cout << static_cast<int>(_map[x * _y + y]) << "\t";
	}
      std::cout << std::endl;
    }
}
