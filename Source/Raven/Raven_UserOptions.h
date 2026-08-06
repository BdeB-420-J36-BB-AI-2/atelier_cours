#ifndef USER_OPTIONS
#define USER_OPTIONS
//-----------------------------------------------------------------------------
//
//  Name:   Raven_UserOptions.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   singleton class to control a number of menu options
//-----------------------------------------------------------------------------

#define UserOptions Raven_UserOptions::Instance()

class Raven_UserOptions
{
  Raven_UserOptions(const Raven_UserOptions &) = delete;
  Raven_UserOptions& operator=(const Raven_UserOptions&) = delete;

public:
  static Raven_UserOptions& Instance();
  Raven_UserOptions();
  
  bool m_bShowGraph;

  bool m_bShowNodeIndices;

  bool m_bShowPathOfSelectedBot;

  bool m_bShowTargetOfSelectedBot;

  bool m_bShowOpponentsSensedBySelectedBot;

  bool m_bOnlyShowBotsInTargetsFOV;

  bool m_bShowGoalsOfSelectedBot;

  bool m_bShowGoalAppraisals;

  bool m_bShowWeaponAppraisals;

  bool m_bSmoothPathsQuick;
  bool m_bSmoothPathsPrecise;

  bool m_bShowBotIDs;

  bool m_bShowBotHealth;

  bool m_bShowScore;
};


#endif