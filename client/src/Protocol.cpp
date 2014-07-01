#include "GameEngine.hpp"
#include "Protocol.hpp"

Protocol::Protocol()
{
  _func["BIENVENUE"] = &Protocol::bienvenue;
  _func["msz"] = &Protocol::msz;
  _func["bct"] = &Protocol::bct;
  _func["tna"] = &Protocol::tna;
  _func["pnw"] = &Protocol::pnw;
  _func["ppo"] = &Protocol::ppo;
  _func["plv"] = &Protocol::plv;
  _func["pin"] = &Protocol::pin;
  _func["pex"] = &Protocol::pex;
  _func["pbc"] = &Protocol::pbc;
  _func["pic"] = &Protocol::pic;
  _func["pie"] = &Protocol::pie;
  _func["pfk"] = &Protocol::pfk;
  _func["pdr"] = &Protocol::pdr;
  _func["pgt"] = &Protocol::pgt;
  _func["pdi"] = &Protocol::pdi;
  _func["enw"] = &Protocol::enw;
  _func["eht"] = &Protocol::eht;
  _func["ebo"] = &Protocol::ebo;
  _func["edi"] = &Protocol::edi;
  _func["sgt"] = &Protocol::sgt;
  _func["seg"] = &Protocol::seg;
  _func["smg"] = &Protocol::smg;
  _func["suc"] = &Protocol::suc;
  _func["sbp"] = &Protocol::sbp;
}

Protocol::~Protocol()
{

}

std::string Protocol::parseCmd(const std::string &cmd, t_display &info)
{
  std::string msg("");
  std::stringstream ss(cmd);
  std::string tmp;
  std::map<std::string, parseFunc>::iterator it;

  ss >> tmp;
  for (it = _func.begin();it != _func.end() && it->first != tmp;it++);
  if (it == _func.end())
    return (msg);
  (this->*(it->second))(cmd, msg, info);
  std::cout << "CMD => " << cmd << std::endl;
  return (msg);
}

void Protocol::bienvenue(const std::string &, std::string &msg, t_display &)
{
  msg = "GRAPHIC\n";
}

void Protocol::msz(const std::string &cmd, std::string &, t_display &info)
{
  std::stringstream ss(cmd);
  int x, y;
  std::string tmp;

  if (!(ss >> tmp >> x >> y))
    return ;
  info.loading = false;
  info.map.createMap(x, y);
}

void Protocol::bct(const std::string &cmd, std::string &, t_display &info)
{
  std::stringstream ss(cmd);
  std::string tmp;
  int x, y;
  int q[7];

  try
    {
      if (!(ss >> tmp >> x >> y))
	return ;
      for (int i = 0;i < 7;++i)
	if (!(ss >> q[i]))
	  return ;
      info.map[x * info.map.getY() + y] = 0;
      for (int i = 1, j = 0;i <= 64;i = i << 1, j++)
	if (q[j] > 0)
	  info.map[x * info.map.getY() + y] |= i;
      info.map.display();
    }
  catch (Exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
}

void Protocol::tna(const std::string &cmd, std::string &, t_display &info)
{
  std::stringstream ss(cmd);
  std::string tmp;

  if (!(ss >> tmp) || !(ss >> tmp))
    return ;
  if (std::find(info.team.begin(), info.team.end(), tmp) != info.team.end())
    info.team.push_back(tmp);
}

void Protocol::pnw(const std::string &cmd, std::string &, t_display &info)
{
  std::stringstream ss(cmd);
  std::stringstream parse("");
  int nb, x, y, lvl, orient;
  std::string team;

  if (!(ss >> team >> team) || team.empty() || team[0] != '#')
    return ;
  parse.str(team.substr(1));
  if (!(parse >> nb) && !(ss >> x >> y >> orient >> lvl >> team))
    return ;
  info.map.addPlayer(new t_player(nb, x, y, lvl, orient, team));
}

void Protocol::ppo(const std::string &cmd, std::string &, t_display &info)
{
  std::stringstream ss(cmd);
  std::stringstream parse("");
  int nb, x, y, orient;
  std::string team;

  if (!(ss >> team >> team) || team.empty() || team[0] != '#')
    return ;
  parse.str(team.substr(1));
  if (!(parse >> nb) || !(ss >> x >> y >> orient))
    return ;
  info.map.updatePlayerPos(nb, x, y, orient);
}

void Protocol::plv(const std::string &cmd, std::string &, t_display &info)
{
  std::stringstream ss(cmd);
  std::stringstream parse("");
  int nb, lvl;
  std::string team;

  if (!(ss >> team >> team) || team.empty() || team[0] != '#')
    return ;
  parse.str(team.substr(1));
  if (!(parse >> nb) || !(ss >> lvl))
    return ;
  info.map.updatePlayerLvl(nb, lvl);
}

void Protocol::pin(const std::string &cmd, std::string &, t_display &info)
{
  /* INVENTAIRE */
}

void Protocol::pex(const std::string &cmd, std::string &, t_display &info)
{
  /* EXPULSE */
}

void Protocol::pbc(const std::string &cmd, std::string &, t_display &info)
{
  /* BROADCAST */
}

void Protocol::pic(const std::string &cmd, std::string &, t_display &info)
{
  /* DEBUT INCANTATION */
}

void Protocol::pie(const std::string &cmd, std::string &, t_display &info)
{
  /* RESULTAT INCANTATION*/
}

void Protocol::pfk(const std::string &cmd, std::string &, t_display &info)
{
  std::stringstream ss(cmd);
  std::stringstream parse("");
  int nb, lvl;
  std::string team;

  if (!(ss >> team >> team) || team.empty() || team[0] != '#')
    return ;
  parse.str(team.substr(1));
  if (!(parse >> nb) || !(ss >> lvl))
    return ;
  info.map.updatePlayerAction(nb, LAY);
}

void Protocol::pdr(const std::string &cmd, std::string &, t_display &info)
{
  std::stringstream ss(cmd);
  std::stringstream parse("");
  int nb, lvl;
  std::string team;

  if (!(ss >> team >> team) || team.empty() || team[0] != '#')
    return ;
  parse.str(team.substr(1));
  if (!(parse >> nb) || !(ss >> lvl))
    return ;
  info.map.updatePlayerAction(nb, DROP);
}

void Protocol::pgt(const std::string &cmd, std::string &, t_display &info)
{
  std::stringstream ss(cmd);
  std::stringstream parse("");
  int nb, lvl;
  std::string team;

  if (!(ss >> team >> team) || team.empty() || team[0] != '#')
    return ;
  parse.str(team.substr(1));
  if (!(parse >> nb) || !(ss >> lvl))
    return ;
  info.map.updatePlayerAction(nb, LOOT);
}

void Protocol::pdi(const std::string &cmd, std::string &, t_display &info)
{

}

void Protocol::enw(const std::string &cmd, std::string &, t_display &info)
{

}

void Protocol::eht(const std::string &cmd, std::string &, t_display &info)
{

}

void Protocol::ebo(const std::string &cmd, std::string &, t_display &info)
{

}

void Protocol::edi(const std::string &cmd, std::string &, t_display &info)
{
  // Disparaition immediate ?
}

void Protocol::sgt(const std::string &cmd, std::string &, t_display &info)
{
  std::stringstream ss(cmd);
  std::string tmp;

  ss >> tmp >> info.time;
}

void Protocol::seg(const std::string &cmd, std::string &, t_display &info)
{
  std::stringstream ss(cmd);
  std::string tmp;

  ss >> tmp >> info.win;
}

void Protocol::smg(const std::string &cmd, std::string &, t_display &)
{
  std::cout << cmd.substr(cmd.find(" ") + 1) << std::endl;
}

void Protocol::suc(const std::string &, std::string &, t_display &)
{
  std::cerr << "Command Unknown" << std::endl;
}

void Protocol::sbp(const std::string &, std::string &, t_display &)
{
  std::cerr << "Bad Command Argument" << std::endl;
}
