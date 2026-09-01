#pragma once

#include "../Core/Globals.h"

using namespace Core;
namespace Game
{
    static const char* WINDOW_TITLE = "Game Test";
    static const int SCREEN_WIDTH  = 720;
    static const int SCREEN_HEIGHT = 480;
    static const uint FPS = 30;

    static const uint SPEED_LIMIT = 50;

    static const double PLAYER_WIDTH          = 70;
    static const double PLAYER_HEIGHT         = 50;
    static const double PLAYER_HEIGHT_CROUCH  = 25;
    static const double PLAYER_COLOR_R        = 0.0;
    static const double PLAYER_COLOR_G        = 0.63;
    static const double PLAYER_COLOR_B        = 0.8;
    static const double PLAYER_ACCEL          = 1000;
    static const double PLAYER_JUMP_VELOCITY  = -600;
    static const double PLAYER_GRAVITY        = 1000;
    static const double PLAYER_GRAVITY_CROUCH = 1500;
    static const double PLAYER_DAMPING        = 300;
    static const double PLAYER_WALL_BOUNCE    = 0.5;
    static const int    PLAYER_EYE_SIZE       = 6;
    static const int    PLAYER_EYE_OFFSET     = 3;

    //-------------------------------------------------------------------------
    // Raven tuning parameters. These used to be hardcoded in the External/Raven
    // library (Raven_Config.cpp, itself a transcript of the original
    // Params.lua). They're now owned by the client and pushed into RavenConfig
    // by ApplyRavenConfig() (see GameConfig.cpp), which must run before any
    // Raven_* object (e.g. GameRaven) is constructed. Names match the
    // RavenConfig keys read via RavenConfig.GetXxx(...) 1:1 - do not rename
    // without updating every call site.
    //-------------------------------------------------------------------------

    // --------------------------- general game parameters ---------------------
    static const int    NumBots                     = 3;
    static const int    MaxSearchCyclesPerUpdateStep = 1000;
    static const char* const StartMap                = "maps/Raven_DM1.map";
    static const int    NumCellsX                    = 10;
    static const int    NumCellsY                    = 10;
    static const int    GraveLifetime                = 5;

    // --------------------------------- bot parameters -------------------------
    static const double Bot_MaxSpeed                = 1;
    static const double Bot_Scale                   = 0.8;

    static const double Bot_MaxHealth               = 100;
    static const double Bot_Mass                    = 1;
    static const double Bot_MaxForce                = 1.0;
    static const double Bot_MaxHeadTurnRate          = 0.2;
    static const double Bot_MaxSwimmingSpeed         = Bot_MaxSpeed * 0.2;
    static const double Bot_MaxCrawlingSpeed         = Bot_MaxSpeed * 0.6;
    static const double Bot_WeaponSelectionFrequency = 2;
    static const double Bot_GoalAppraisalUpdateFreq  = 4;
    static const double Bot_TargetingUpdateFreq      = 2;
    static const double Bot_TriggerUpdateFreq        = 8;
    static const double Bot_VisionUpdateFreq         = 4;
    static const double Bot_FOV                      = 180;
    static const double Bot_ReactionTime             = 0.2;
    static const double Bot_AimPersistance           = 1;
    static const double Bot_AimAccuracy              = 0.0;
    static const double HitFlashTime                 = 0.2;
    static const double Bot_MemorySpan               = 5;
    static const double Bot_HealthGoalTweaker        = 1.0;
    static const double Bot_ShotgunGoalTweaker       = 1.0;
    static const double Bot_RailgunGoalTweaker       = 1.0;
    static const double Bot_RocketLauncherTweaker    = 1.0;
    static const double Bot_AggroGoalTweaker         = 1.0;

    // ----------------------------- steering parameters -------------------------
    static const double SeparationWeight        = 10.0;
    static const double WallAvoidanceWeight      = 10.0;
    static const double WanderWeight             = 1.0;
    static const double SeekWeight               = 0.5;
    static const double ArriveWeight             = 1.0;
    static const double ViewDistance             = 15.0;
    static const double WallDetectionFeelerLength = 25.0 * Bot_Scale;
    static const double WaypointSeekDist          = 5;

    // ------------------------- giver-trigger parameters -------------------------
    static const double DefaultGiverTriggerRange = 10;
    static const double Health_RespawnDelay      = 10;
    static const double Weapon_RespawnDelay      = 15;

    // ----------------------------- weapon parameters -----------------------------
    static const double Blaster_FiringFreq       = 3;
    static const double Blaster_MaxSpeed         = 5;
    static const double Blaster_DefaultRounds    = 0;
    static const double Blaster_MaxRoundsCarried = 0;
    static const double Blaster_IdealRange       = 50;
    static const double Blaster_SoundRange       = 100;

    static const double Bolt_MaxSpeed = 5;
    static const double Bolt_Mass     = 1;
    static const double Bolt_MaxForce = 100.0;
    static const double Bolt_Scale    = Bot_Scale;
    static const double Bolt_Damage   = 1;

    static const double RocketLauncher_FiringFreq       = 1.5;
    static const double RocketLauncher_DefaultRounds    = 15;
    static const double RocketLauncher_MaxRoundsCarried = 50;
    static const double RocketLauncher_IdealRange       = 150;
    static const double RocketLauncher_SoundRange       = 400;

    static const double Rocket_BlastRadius        = 20;
    static const double Rocket_MaxSpeed           = 3;
    static const double Rocket_Mass               = 1;
    static const double Rocket_MaxForce           = 10.0;
    static const double Rocket_Scale              = Bot_Scale;
    static const double Rocket_Damage             = 10;
    static const double Rocket_ExplosionDecayRate = 2.0;

    static const double RailGun_FiringFreq       = 1;
    static const double RailGun_DefaultRounds    = 15;
    static const double RailGun_MaxRoundsCarried = 50;
    static const double RailGun_IdealRange       = 200;
    static const double RailGun_SoundRange       = 400;

    static const double Slug_MaxSpeed    = 5000;
    static const double Slug_Mass        = 0.1;
    static const double Slug_MaxForce    = 10000.0;
    static const double Slug_Scale       = Bot_Scale;
    static const double Slug_Persistance = 0.2;
    static const double Slug_Damage      = 10;

    static const double ShotGun_FiringFreq       = 1;
    static const double ShotGun_DefaultRounds    = 15;
    static const double ShotGun_MaxRoundsCarried = 50;
    static const double ShotGun_NumBallsInShell  = 10;
    static const double ShotGun_Spread           = 0.05;
    static const double ShotGun_IdealRange       = 100;
    static const double ShotGun_SoundRange       = 400;

    static const double Pellet_MaxSpeed    = 5000;
    static const double Pellet_Mass        = 0.1;
    static const double Pellet_MaxForce    = 1000.0;
    static const double Pellet_Scale       = Bot_Scale;
    static const double Pellet_Persistance = 0.1;
    static const double Pellet_Damage      = 1;

    // pushes every Raven tuning constant above into RavenConfig; call once,
    // before any Raven_* object (e.g. GameRaven) is constructed.
    void ApplyRavenConfig();
}
