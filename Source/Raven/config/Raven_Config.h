#ifndef RAVEN_CONFIG_H
#define RAVEN_CONFIG_H
//-----------------------------------------------------------------------------
//
//  Name:   Raven_Config
//
//  Desc:   Drop-in replacement for the original Lua-backed scriptor. Raven's
//          "Params.lua" was a flat list of tunable constants (no real script
//          logic beyond a couple of multiplications), so this singleton just
//          holds those same values in a std::map instead of embedding a Lua
//          interpreter. Callers still go through config.GetInt/GetDouble/
//          GetBool/GetString exactly as before.
//
//-----------------------------------------------------------------------------
#include <map>
#include <string>

#define config Raven_Config::Instance()

class Raven_Config
{
  Raven_Config(const Raven_Config&) = delete;
  Raven_Config& operator=(const Raven_Config&) = delete;

  std::map<std::string, double>      m_Numbers;
  std::map<std::string, std::string> m_Strings;

public:

  static Raven_Config& Instance();
  Raven_Config();

  int         GetInt(const char* VariableName);
  double      GetFloat(const char* VariableName);
  double      GetDouble(const char* VariableName);
  std::string GetString(const char* VariableName);
  bool        GetBool(const char* VariableName);
};

#endif
