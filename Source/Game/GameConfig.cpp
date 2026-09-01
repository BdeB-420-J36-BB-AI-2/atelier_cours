#include "GameConfig.h"
#include "config/Raven_Config.h"

namespace Game
{
    // Stringizes the identifier so the RavenConfig key can never drift from
    // the constant's name in GameConfig.h.
#define PUSH_NUM(name) RavenConfig.SetNumber(#name, name)

    void ApplyRavenConfig()
    {
        // --------------------------- general game parameters ---------------------
        PUSH_NUM(NumBots);
        PUSH_NUM(MaxSearchCyclesPerUpdateStep);
        RavenConfig.SetString("StartMap", StartMap);
        PUSH_NUM(NumCellsX);
        PUSH_NUM(NumCellsY);
        PUSH_NUM(GraveLifetime);

        // --------------------------------- bot parameters -------------------------
        PUSH_NUM(Bot_MaxHealth);
        PUSH_NUM(Bot_MaxSpeed);
        PUSH_NUM(Bot_Mass);
        PUSH_NUM(Bot_MaxForce);
        PUSH_NUM(Bot_MaxHeadTurnRate);
        PUSH_NUM(Bot_Scale);
        PUSH_NUM(Bot_MaxSwimmingSpeed);
        PUSH_NUM(Bot_MaxCrawlingSpeed);
        PUSH_NUM(Bot_WeaponSelectionFrequency);
        PUSH_NUM(Bot_GoalAppraisalUpdateFreq);
        PUSH_NUM(Bot_TargetingUpdateFreq);
        PUSH_NUM(Bot_TriggerUpdateFreq);
        PUSH_NUM(Bot_VisionUpdateFreq);
        PUSH_NUM(Bot_FOV);
        PUSH_NUM(Bot_ReactionTime);
        PUSH_NUM(Bot_AimPersistance);
        PUSH_NUM(Bot_AimAccuracy);
        PUSH_NUM(HitFlashTime);
        PUSH_NUM(Bot_MemorySpan);
        PUSH_NUM(Bot_HealthGoalTweaker);
        PUSH_NUM(Bot_ShotgunGoalTweaker);
        PUSH_NUM(Bot_RailgunGoalTweaker);
        PUSH_NUM(Bot_RocketLauncherTweaker);
        PUSH_NUM(Bot_AggroGoalTweaker);

        // ----------------------------- steering parameters -------------------------
        PUSH_NUM(SeparationWeight);
        PUSH_NUM(WallAvoidanceWeight);
        PUSH_NUM(WanderWeight);
        PUSH_NUM(SeekWeight);
        PUSH_NUM(ArriveWeight);
        PUSH_NUM(ViewDistance);
        PUSH_NUM(WallDetectionFeelerLength);
        PUSH_NUM(WaypointSeekDist);

        // ------------------------- giver-trigger parameters -------------------------
        PUSH_NUM(DefaultGiverTriggerRange);
        PUSH_NUM(Health_RespawnDelay);
        PUSH_NUM(Weapon_RespawnDelay);

        // ----------------------------- weapon parameters -----------------------------
        PUSH_NUM(Blaster_FiringFreq);
        PUSH_NUM(Blaster_MaxSpeed);
        PUSH_NUM(Blaster_DefaultRounds);
        PUSH_NUM(Blaster_MaxRoundsCarried);
        PUSH_NUM(Blaster_IdealRange);
        PUSH_NUM(Blaster_SoundRange);

        PUSH_NUM(Bolt_MaxSpeed);
        PUSH_NUM(Bolt_Mass);
        PUSH_NUM(Bolt_MaxForce);
        PUSH_NUM(Bolt_Scale);
        PUSH_NUM(Bolt_Damage);

        PUSH_NUM(RocketLauncher_FiringFreq);
        PUSH_NUM(RocketLauncher_DefaultRounds);
        PUSH_NUM(RocketLauncher_MaxRoundsCarried);
        PUSH_NUM(RocketLauncher_IdealRange);
        PUSH_NUM(RocketLauncher_SoundRange);

        PUSH_NUM(Rocket_BlastRadius);
        PUSH_NUM(Rocket_MaxSpeed);
        PUSH_NUM(Rocket_Mass);
        PUSH_NUM(Rocket_MaxForce);
        PUSH_NUM(Rocket_Scale);
        PUSH_NUM(Rocket_Damage);
        PUSH_NUM(Rocket_ExplosionDecayRate);

        PUSH_NUM(RailGun_FiringFreq);
        PUSH_NUM(RailGun_DefaultRounds);
        PUSH_NUM(RailGun_MaxRoundsCarried);
        PUSH_NUM(RailGun_IdealRange);
        PUSH_NUM(RailGun_SoundRange);

        PUSH_NUM(Slug_MaxSpeed);
        PUSH_NUM(Slug_Mass);
        PUSH_NUM(Slug_MaxForce);
        PUSH_NUM(Slug_Scale);
        PUSH_NUM(Slug_Persistance);
        PUSH_NUM(Slug_Damage);

        PUSH_NUM(ShotGun_FiringFreq);
        PUSH_NUM(ShotGun_DefaultRounds);
        PUSH_NUM(ShotGun_MaxRoundsCarried);
        PUSH_NUM(ShotGun_NumBallsInShell);
        PUSH_NUM(ShotGun_Spread);
        PUSH_NUM(ShotGun_IdealRange);
        PUSH_NUM(ShotGun_SoundRange);

        PUSH_NUM(Pellet_MaxSpeed);
        PUSH_NUM(Pellet_Mass);
        PUSH_NUM(Pellet_MaxForce);
        PUSH_NUM(Pellet_Scale);
        PUSH_NUM(Pellet_Persistance);
        PUSH_NUM(Pellet_Damage);
    }

#undef PUSH_NUM
}
