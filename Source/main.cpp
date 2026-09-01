/*
vcxproj properties setup check list
-----------------------------------
- C/C++ > general > additional include folder > $(SolutionDir)include\raylib; $(SolutionDir)include\
- C/C++ > general > preprocessor > GRAPHICS_API_OPENGL_33; PLATFORM_DESKTOP
- Linker > general > additional Library Directory > $(SolutionDir)Lib\$(Platform)\$(Configuration)\
- Linker > input > additional dependencies > raylib.lib;winmm.lib
*/

#include <raylib.h>
#include <Code_Utilities_Light_v2.h>

#include "Game/GameTest.h"
#include "Game/GameConfig.h"

using namespace BdB;

int main()
{
    Game::ApplyRavenConfig();
    Game::GameTest{}.run();
    // TODO: breakdown
    // - ETQ developpeur, je veux pouvoir créer un arbre de comportement pour mon jeu
    //  - task 1 : creer une classe abstraite "Node" qui sera la base de tous les noeuds de l'arbre de comportement --> OK 
    //  - task 2 : creer une classe "CompositeNode" qui sera la base de tous les noeuds composites (Sequence, Selector, etc.) --> OK
    //  - task 3 : creer une classe "LeafNode" qui sera la base de tous les noeuds feuilles (Action, Condition, etc.) --> OK
    //  - task 4 : creer une classe "BehaviourTree" qui sera la base de l'arbre de comportement --> OK
    //  - task 5 : creer une classe "Sequence" qui sera un noeud composite qui execute ses enfants dans l'ordre jusqu'à ce qu'un enfant échoue
    //  - task 6 : creer une classe "Selector" qui sera un noeud composite qui execute ses enfants dans l'ordre jusqu'à ce qu'un enfant réussisse
    // - ETQ  developpeur, je veux pouvoir rajouter des noeuds à mon arbre de comportement
    // - ETQ developpeur, je veux pouvoir executer mon arbre de comportement
    // - ETQ Game designer, je veux pouvoir utiliser une interface graphique pour créer mon arbre de comportement
    // - ETQ joueur, je veux pouvoir voir les NPC interagir avec l'environnement

}
