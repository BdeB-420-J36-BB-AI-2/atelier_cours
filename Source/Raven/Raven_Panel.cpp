#include "Raven_Panel.h"

#include "Raven_Scene.h"
#include "Raven_UserOptions.h"
#include "misc/GraphicsContext.h"
#include "raylib.h"

namespace Game
{
    Raven_Panel::Raven_Panel(Raven_Scene &scene)
        : _scene(scene)
    {
    }

    Raven_Panel::~Raven_Panel() = default;

    bool Raven_Panel::ProcessUIPanel(const std::vector<std::string>& mapFiles) const
    {
        const double PanelWidth = 240.0;
        Rect2D panelRect = {5, 5, PanelWidth, gfx.GetScreenHeight() - 10.0};
        bool bMouseOverPanel = CheckCollisionPointRec(GetMousePosition(), Rectangle{(float)panelRect.x, (float)panelRect.y, (float)panelRect.w, (float)panelRect.h});
        {
          gfx.GuiPanel(panelRect, "Raven  (TAB to hide)");

          double y = 30;
          const double x = 15;
          const double w = PanelWidth - 20;

          gfx.GuiLabel({x, y, w, 20}, ("Bots: " + std::to_string(_scene.GetNumBots())).c_str()); y += 22;

          if (gfx.GuiButton({x, y, w*0.48, 22}, "Add Bot (Up)"))
              _pendingRequest.addBot = true;
          if (gfx.GuiButton({x + w*0.52, y, w*0.48, 22}, "Remove Bot (Dn)"))
              _pendingRequest.removeBot = true;
          y += 26;

          if (gfx.GuiButton({x, y, w, 22}, "Pause / Resume (P)"))
              _pendingRequest.togglePause = true;
          y += 32;

          gfx.GuiLabel({x, y, w, 18}, "Navigation"); y += 18;
          gfx.GuiCheckBox({x, y, 16, 16}, "Show nav graph", &UserOptions.m_bShowGraph); y += 20;
          gfx.GuiCheckBox({x, y, 16, 16}, "Show path of selected bot", &UserOptions.m_bShowPathOfSelectedBot); y += 20;
          gfx.GuiCheckBox({x, y, 16, 16}, "Show node indices", &UserOptions.m_bShowNodeIndices); y += 20;

          bool bWasQuick   = UserOptions.m_bSmoothPathsQuick;
          bool bWasPrecise = UserOptions.m_bSmoothPathsPrecise;
          gfx.GuiCheckBox({x, y, 16, 16}, "Smooth paths (quick)", &UserOptions.m_bSmoothPathsQuick); y += 20;
          gfx.GuiCheckBox({x, y, 16, 16}, "Smooth paths (precise)", &UserOptions.m_bSmoothPathsPrecise); y += 24;
          if (UserOptions.m_bSmoothPathsQuick && !bWasQuick)
              UserOptions.m_bSmoothPathsPrecise = false;
          if (UserOptions.m_bSmoothPathsPrecise && !bWasPrecise)
              UserOptions.m_bSmoothPathsQuick = false;

          gfx.GuiLabel({x, y, w, 18}, "Bots"); y += 18;
          gfx.GuiCheckBox({x, y, 16, 16}, "Show IDs", &UserOptions.m_bShowBotIDs); y += 20;
          gfx.GuiCheckBox({x, y, 16, 16}, "Show health", &UserOptions.m_bShowBotHealth); y += 20;
          gfx.GuiCheckBox({x, y, 16, 16}, "Show target of selected bot", &UserOptions.m_bShowTargetOfSelectedBot); y += 20;
          gfx.GuiCheckBox({x, y, 16, 16}, "Show sensed opponents", &UserOptions.m_bShowOpponentsSensedBySelectedBot); y += 20;
          gfx.GuiCheckBox({x, y, 16, 16}, "Only show bots in target FOV", &UserOptions.m_bOnlyShowBotsInTargetsFOV); y += 20;
          gfx.GuiCheckBox({x, y, 16, 16}, "Show scores", &UserOptions.m_bShowScore); y += 20;
          gfx.GuiCheckBox({x, y, 16, 16}, "Show goal queue of selected bot", &UserOptions.m_bShowGoalsOfSelectedBot); y += 24;

          gfx.GuiLabel({x, y, w, 18}, "Maps (double-click to load)"); y += 18;

          std::string mapListText;
          for (size_t i = 0; i < mapFiles.size(); ++i)
          {
            if (i > 0) mapListText += ";";
            mapListText += mapFiles[i];
          }

          int previousActive = _mapListActive;
          gfx.GuiListView({x, y, w, 130}, mapListText.c_str(), &_mapListScroll, &_mapListActive);

          if (_mapListActive >= 0 && _mapListActive < (int)mapFiles.size() && _mapListActive != previousActive)
            _pendingRequest.loadMapIndex = _mapListActive;
        }

      return bMouseOverPanel;
    }

    PanelRequest Raven_Panel::TakePendingRequest() const
    {
        PanelRequest request = _pendingRequest;
        _pendingRequest = PanelRequest();
        return request;
    }
}
