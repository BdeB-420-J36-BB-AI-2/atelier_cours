#include "Raven_Config.h"
#include <stdexcept>

static Raven_Config g_instance;

Raven_Config& Raven_Config::Instance()
{
  return g_instance;
}

//-----------------------------------------------------------------------------
//  Values transcribed 1:1 from the original Params.lua (including the couple
//  of arithmetic expressions it contained, e.g. Bot_MaxSwimmingSpeed = 0.2 *
//  Bot_MaxSpeed), so bot/weapon/steering behaviour is unchanged.
//-----------------------------------------------------------------------------
Raven_Config::Raven_Config()
{
  //--------------------------- general game parameters ---------------------
  m_Numbers["NumBots"]                       = 3;
  m_Numbers["MaxSearchCyclesPerUpdateStep"]  = 1000;
  m_Strings["StartMap"]                      = "maps/Raven_DM1.map";
  m_Numbers["NumCellsX"]                     = 10;
  m_Numbers["NumCellsY"]                     = 10;
  m_Numbers["GraveLifetime"]                 = 5;

  //--------------------------------- bot parameters -------------------------
  const double Bot_MaxSpeed = 1;
  const double Bot_Scale    = 0.8;

  m_Numbers["Bot_MaxHealth"]                 = 100;
  m_Numbers["Bot_MaxSpeed"]                  = Bot_MaxSpeed;
  m_Numbers["Bot_Mass"]                      = 1;
  m_Numbers["Bot_MaxForce"]                  = 1.0;
  m_Numbers["Bot_MaxHeadTurnRate"]           = 0.2;
  m_Numbers["Bot_Scale"]                     = Bot_Scale;
  m_Numbers["Bot_MaxSwimmingSpeed"]          = Bot_MaxSpeed * 0.2;
  m_Numbers["Bot_MaxCrawlingSpeed"]          = Bot_MaxSpeed * 0.6;
  m_Numbers["Bot_WeaponSelectionFrequency"]  = 2;
  m_Numbers["Bot_GoalAppraisalUpdateFreq"]   = 4;
  m_Numbers["Bot_TargetingUpdateFreq"]       = 2;
  m_Numbers["Bot_TriggerUpdateFreq"]         = 8;
  m_Numbers["Bot_VisionUpdateFreq"]          = 4;
  m_Numbers["Bot_FOV"]                       = 180;
  m_Numbers["Bot_ReactionTime"]              = 0.2;
  m_Numbers["Bot_AimPersistance"]            = 1;
  m_Numbers["Bot_AimAccuracy"]               = 0.0;
  m_Numbers["HitFlashTime"]                  = 0.2;
  m_Numbers["Bot_MemorySpan"]                = 5;
  m_Numbers["Bot_HealthGoalTweaker"]         = 1.0;
  m_Numbers["Bot_ShotgunGoalTweaker"]        = 1.0;
  m_Numbers["Bot_RailgunGoalTweaker"]        = 1.0;
  m_Numbers["Bot_RocketLauncherTweaker"]     = 1.0;
  m_Numbers["Bot_AggroGoalTweaker"]          = 1.0;

  //----------------------------- steering parameters -------------------------
  m_Numbers["SeparationWeight"]              = 10.0;
  m_Numbers["WallAvoidanceWeight"]           = 10.0;
  m_Numbers["WanderWeight"]                  = 1.0;
  m_Numbers["SeekWeight"]                    = 0.5;
  m_Numbers["ArriveWeight"]                  = 1.0;
  m_Numbers["ViewDistance"]                  = 15.0;
  m_Numbers["WallDetectionFeelerLength"]     = 25.0 * Bot_Scale;
  m_Numbers["WaypointSeekDist"]              = 5;

  //------------------------- giver-trigger parameters -------------------------
  m_Numbers["DefaultGiverTriggerRange"]      = 10;
  m_Numbers["Health_RespawnDelay"]           = 10;
  m_Numbers["Weapon_RespawnDelay"]           = 15;

  //----------------------------- weapon parameters -----------------------------
  m_Numbers["Blaster_FiringFreq"]            = 3;
  m_Numbers["Blaster_MaxSpeed"]              = 5;
  m_Numbers["Blaster_DefaultRounds"]         = 0;
  m_Numbers["Blaster_MaxRoundsCarried"]      = 0;
  m_Numbers["Blaster_IdealRange"]            = 50;
  m_Numbers["Blaster_SoundRange"]            = 100;

  m_Numbers["Bolt_MaxSpeed"]                 = 5;
  m_Numbers["Bolt_Mass"]                     = 1;
  m_Numbers["Bolt_MaxForce"]                 = 100.0;
  m_Numbers["Bolt_Scale"]                    = Bot_Scale;
  m_Numbers["Bolt_Damage"]                   = 1;

  m_Numbers["RocketLauncher_FiringFreq"]       = 1.5;
  m_Numbers["RocketLauncher_DefaultRounds"]    = 15;
  m_Numbers["RocketLauncher_MaxRoundsCarried"] = 50;
  m_Numbers["RocketLauncher_IdealRange"]       = 150;
  m_Numbers["RocketLauncher_SoundRange"]       = 400;

  m_Numbers["Rocket_BlastRadius"]            = 20;
  m_Numbers["Rocket_MaxSpeed"]               = 3;
  m_Numbers["Rocket_Mass"]                   = 1;
  m_Numbers["Rocket_MaxForce"]               = 10.0;
  m_Numbers["Rocket_Scale"]                  = Bot_Scale;
  m_Numbers["Rocket_Damage"]                 = 10;
  m_Numbers["Rocket_ExplosionDecayRate"]     = 2.0;

  m_Numbers["RailGun_FiringFreq"]            = 1;
  m_Numbers["RailGun_DefaultRounds"]         = 15;
  m_Numbers["RailGun_MaxRoundsCarried"]      = 50;
  m_Numbers["RailGun_IdealRange"]            = 200;
  m_Numbers["RailGun_SoundRange"]            = 400;

  m_Numbers["Slug_MaxSpeed"]                 = 5000;
  m_Numbers["Slug_Mass"]                     = 0.1;
  m_Numbers["Slug_MaxForce"]                 = 10000.0;
  m_Numbers["Slug_Scale"]                    = Bot_Scale;
  m_Numbers["Slug_Persistance"]              = 0.2;
  m_Numbers["Slug_Damage"]                   = 10;

  m_Numbers["ShotGun_FiringFreq"]            = 1;
  m_Numbers["ShotGun_DefaultRounds"]         = 15;
  m_Numbers["ShotGun_MaxRoundsCarried"]      = 50;
  m_Numbers["ShotGun_NumBallsInShell"]       = 10;
  m_Numbers["ShotGun_Spread"]                = 0.05;
  m_Numbers["ShotGun_IdealRange"]            = 100;
  m_Numbers["ShotGun_SoundRange"]            = 400;

  m_Numbers["Pellet_MaxSpeed"]               = 5000;
  m_Numbers["Pellet_Mass"]                   = 0.1;
  m_Numbers["Pellet_MaxForce"]               = 1000.0;
  m_Numbers["Pellet_Scale"]                  = Bot_Scale;
  m_Numbers["Pellet_Persistance"]            = 0.1;
  m_Numbers["Pellet_Damage"]                 = 1;
}

int Raven_Config::GetInt(const char* VariableName)
{
  return (int)GetDouble(VariableName);
}

double Raven_Config::GetFloat(const char* VariableName)
{
  return GetDouble(VariableName);
}

double Raven_Config::GetDouble(const char* VariableName)
{
  std::map<std::string, double>::const_iterator it = m_Numbers.find(VariableName);

  if (it == m_Numbers.end())
  {
    throw std::runtime_error(std::string("Raven_Config: unknown parameter ") + VariableName);
  }

  return it->second;
}

std::string Raven_Config::GetString(const char* VariableName)
{
  std::map<std::string, std::string>::const_iterator it = m_Strings.find(VariableName);

  if (it == m_Strings.end())
  {
    throw std::runtime_error(std::string("Raven_Config: unknown parameter ") + VariableName);
  }

  return it->second;
}

bool Raven_Config::GetBool(const char* VariableName)
{
  return GetDouble(VariableName) != 0.0;
}
