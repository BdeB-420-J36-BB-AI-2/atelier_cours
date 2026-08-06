//
// Created by Khalil on 2026-07-10.
//

#ifndef RAYLIBBASIC_RAVEN_PANEL_H
#define RAYLIBBASIC_RAVEN_PANEL_H

#include <vector>
#include <string>

class Raven_UserOptions;
class Raven_Scene;

namespace Game
{
    // Model mutations requested by the panel while drawing (e.g. a button click).
    // Collected during the const render pass, applied by GameRaven::update().
    struct PanelRequest
    {
        bool addBot = false;
        bool removeBot = false;
        bool togglePause = false;
        int loadMapIndex = -1;
    };

    class Raven_Panel
    {
        Raven_Scene &_scene;

        // View-only widget state (list scroll/selection) - not part of the game model,
        // so it's safe to mutate from the const ProcessUIPanel draw pass.
        mutable int _mapListScroll = 0;
        mutable int _mapListActive = -1;

        mutable PanelRequest _pendingRequest;

    public:
        Raven_Panel(Raven_Scene &scene);
        ~Raven_Panel();
        bool ProcessUIPanel(const std::vector<std::string> &mapFiles) const;

        // Returns the requests accumulated since the last call and clears them.
        PanelRequest TakePendingRequest() const;
    };
}

#endif //RAYLIBBASIC_RAVEN_PANEL_H
