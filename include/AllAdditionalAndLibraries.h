#ifndef ALLADDITIONALANDLIBRARIES_H
#define ALLADDITIONALANDLIBRARIES_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <optional>
#include <random>
#include <atomic>
#include <cmath>
#include <sstream>


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "auxFunctions.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


enum class CategoriePlayer
{
	Warrior = 1, 
	Rogue,
	Wizard
};

enum class CategorieEnemy
{
	Ghoul = 1,
	Troll, 
	Griffon
};


enum class BattleLocation
{
	Cave = 1, 
	Forest, 
	Village
};

enum class Direction
{
	Up = 1,
	Down, 
	Left, 
	Right
};

enum class TypeItem
{
	//For wizard
	FireBall = 0,
	IceBall,

	//For warior
	Sword,
	Spear,

	//For rogue
	Knive,
	SpikedTrap,

	//For troll
	Rock, 

	////////////
	None
};

const std::map<TypeItem, int> projSpeed
{
	{TypeItem::FireBall, 14}, 
	{TypeItem::IceBall,  12}, 
	{TypeItem::Spear,    10}, 
	{TypeItem::Knive,    16},
	{TypeItem::Rock,	 12}
}; 


//Numarul de tipuri de item-uri posibile pentru fiecare clasa
const short possItemsWizard = 2;
const short possItemsWarrior = 2;
const short possItemsRogue = 2;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Player; //Forward declaration pentru utilizarea pointerului
class Enemy; 

struct ActionResults //Instantele clasei date fac legatura (sunt agregate ale lui Game) intre clasa Game si clasele derivate din GameInfo
{
	//Final scena
	std::optional<bool> sceneEnd;
	//Are loc introducerea textului 
	bool isEnteringText;

	std::shared_ptr<Player> player;
	std::shared_ptr<Enemy> enemy; 

	BattleLocation locatieLupta; 
	bool defeatedEnemy; 

	//Directie pentru rotatie (vectori de baza)
	//citite de la tastatura (W,A,S,D)
	short dir_x; 
	short dir_y; 

	//Nu trebuie modificate dupa scena 2!!!
	CategoriePlayer clasaPlayer;
	std::string playerName;
};



struct Stats 
{
	int health;
	int attackPower;
	int speedMovement;
};

const std::map<std::string, Stats> enemyStats  
{
	{"Ghoul", {800, 25, 2}},
	{"Troll", {1500, 50, 1}},
	{"Griffon", {1000, 35, 4}}
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//----------------------------------------Number of themes----------------------------------------
const short themes = 6;


//----------------------------------------Proprietati window----------------------------------------
const short width = 1792;
const short height = 1024;
const short frameLimit = 60;
const std::string gameName = "The Beginning of the End";


//----------------------------------------Calea catre muzica----------------------------------------
const std::string path_Main_Menu_music = "img-font-audio/Music/Main_Menu.wav";
const std::string path_Exploring_music = "img-font-audio/Music/Exploring.wav";
const std::string path_IntroBattle_music = "img-font-audio/Music/IntroBattle.mp3"; 
const std::string path_BattleFinal_music = "img-font-audio/Music/BattleFinal.wav";
const std::string path_IntroAfterBattle_music = "img-font-audio/Music/IntroAfterBattle.mp3";
const std::string path_TheEnd_music = "img-font-audio/Music/TheEnd.mp3"; 



//----------------------------------------For GameIntroInfo_1----------------------------------------
const std::string path_Main_Menu_BackG = "img-font-audio/Textures/Main_menu.png";

const std::string path_Main_Menu_GameN = "img-font-audio/Textures/Game_Name.png";

const std::string path_Main_Menu_play = "img-font-audio/Textures/play.png";
const std::string path_Main_Menu_playH = "img-font-audio/Textures/play_mouseHeld.png";

const std::string path_Main_Menu_exit = "img-font-audio/Textures/exit.png";
const std::string path_Main_Menu_exitH = "img-font-audio/Textures/exit_mouseHeld.png";


//----------------------------------------For GameIntroInfo_2----------------------------------------
const std::string path_IntroBackG = "img-font-audio/Textures/campLupta.png";
const std::string path_OldMan = "img-font-audio/Textures/TheOldMan.png"; 

const std::string path_IntroText_1 = "img-font-audio/Textures/Text_1.png";
const std::string path_IntroText_2 = "img-font-audio/Textures/Text_2.png";
const std::string path_IntroText_3 = "img-font-audio/Textures/Text_3.png";
const std::string path_IntroText_4 = "img-font-audio/Textures/Text_4.png";
const std::string path_IntroText_5 = "img-font-audio/Textures/Text_5.png";
const std::string path_IntroText_6 = "img-font-audio/Textures/Text_6.png";

const std::string path_continue = "img-font-audio/Textures/continue.png";
const std::string path_continueH = "img-font-audio/Textures/continue_mouseHeld.png";


//----------------------------------------For GameInfoChoose----------------------------------------
const std::string path_Choosing_BackG = "img-font-audio/Textures/FundalChoosePlayer.png";
const std::string path_Choosing_BackG_Wi = "img-font-audio/Textures/FundalChoosePlayer_Wizard.png";
const std::string path_Choosing_BackG_Wa = "img-font-audio/Textures/FundalChoosePlayer_Warrior.png";
const std::string path_Choosing_BackG_R = "img-font-audio/Textures/FundalChoosePlayer_Rogue.png";


const std::string path_Choosing_Warrior = "img-font-audio/Textures/warrior.png";
const std::string path_Choosing_WarriorH = "img-font-audio/Textures/warrior_mouseHeld.png";

const std::string path_Choosing_Wizard = "img-font-audio/Textures/wizard.png";
const std::string path_Choosing_WizardH = "img-font-audio/Textures/wizard_mouseHeld.png";

const std::string path_Choosing_Rogue = "img-font-audio/Textures/rogue.png";
const std::string path_Choosing_RogueH = "img-font-audio/Textures/rogue_mouseHeld.png";


//----------------------------------------For GameCrossRoads----------------------------------------
const std::string path_CrossRoads_BackG = "img-font-audio/Textures/CrossRoads.png";
const std::string path_CrossRoads_BackG_chest = "img-font-audio/Textures/CrossRoads_chestScene.png";

const std::string path_CrossRoads_Chest = "img-font-audio/Textures/chestImage.png";
const std::string path_CrossRoads_ChestOpen = "img-font-audio/Textures/chestImageOpen.png";

const std::string path_CrossRoads_ChestInfo_1 = "img-font-audio/Textures/chestInfo_1.png";
const std::string path_CrossRoad_ChestInfo_2_fireball = "img-font-audio/Textures/chestInfo_2_fireball.png"; 
const std::string path_CrossRoad_ChestInfo_2_iceball = "img-font-audio/Textures/chestInfo_2_iceball.png"; 
const std::string path_CrossRoad_ChestInfo_2_spear = "img-font-audio/Textures/chestInfo_2_spear.png"; 
const std::string path_CrossRoad_ChestInfo_2_spikedTrap = "img-font-audio/Textures/chestInfo_2_spikedTrap.png";
const std::string path_CrossRoad_ChestInfo_2_knive = "img-font-audio/Textures/chestInfo_2_knive.png";

const std::string path_CrossRoads_Open = "img-font-audio/Textures/open.png";
const std::string path_CrossRoads_Open_mouseH = "img-font-audio/Textures/open_mouseHeld.png";

const std::string path_CrossRoads_Skip = "img-font-audio/Textures/skip.png";
const std::string path_CrossRoads_Skip_mouseH = "img-font-audio/Textures/skip_mouseHeld.png";

const std::string path_caveInscription = "img-font-audio/Textures/caveTEXT.png";
const std::string path_forestInscription = "img-font-audio/Textures/forestTEXT.png";
const std::string path_villageInscription = "img-font-audio/Textures/villageTEXT.png";

const std::string path_caveInscription_mouseH = "img-font-audio/Textures/caveTEXT_mouseHeld.png";
const std::string path_forestInscription_mouseH = "img-font-audio/Textures/forestTEXT_mouseHeld.png";
const std::string path_villageInscription_mouseH = "img-font-audio/Textures/villageTEXT_mouseHeld.png";

const std::string path_caveInscription_choosed = "img-font-audio/Textures/caveTEXT_choosed.png";
const std::string path_forestInscription_choosed = "img-font-audio/Textures/forestTEXT_choosed.png";
const std::string path_villageInscription_choosed = "img-font-audio/Textures/villageTEXT_choosed.png";


//----------------------------------------For GameInfoIntroBattle----------------------------------------
const std::string path_IntroBattle_BackGCave = "img-font-audio/Textures/intrareCave.png";
const std::string path_IntroBattle_CaveDescrip = "img-font-audio/Textures/descriereCave.png"; 

const std::string path_IntroBattle_BackGForest = "img-font-audio/Textures/intrareForest.png";
const std::string path_IntroBattle_ForestDescrip = "img-font-audio/Textures/descriereForest.png";

const std::string path_IntroBattle_BackGVillage = "img-font-audio/Textures/intrareVillage.png";
const std::string path_IntroBattle_VillageDescrip = "img-font-audio/Textures/descriereVillage.png";

const std::string path_Ghoul_IntroMesajAtack = "img-font-audio/Textures/ghoulMesajAtack.png";
const std::string path_Troll_IntroMesajAtack = "img-font-audio/Textures/trollMesajAtack.png";
const std::string path_Griffon_IntroMesajAtack = "img-font-audio/Textures/griffonMesajAtack.png";



//----------------------------------------For GameInfoBattleScene----------------------------------------
const std::string path_BattleScene_BackGCave = "img-font-audio/Textures/battleSceneCave.png";
const std::string path_BattleScene_BackGForest = "img-font-audio/Textures/battleSceneForest.png";
const std::string path_BattleScene_BackGVillage = "img-font-audio/Textures/battleSceneVillage.png";


//----------------------------------------For GameInfoEndOfTheFight----------------------------------------
const std::string path_EndOfTheFight_BackGCave = "img-font-audio/Textures/caveFinish.png"; 
const std::string path_EndOfTheFight_BackGForest = "img-font-audio/Textures/forestFinish.png";
const std::string path_EndOfTheFight_BackGVillage = "img-font-audio/Textures/villageFinish.png";

const std::string path_EndOfTheFight_win = "img-font-audio/Textures/youWin.png";
const std::string path_EndOfTheFight_defeat = "img-font-audio/Textures/defeat.png";



//----------------------------------------For Warrior class----------------------------------------
const std::string path_Warrior_IntroText = "img-font-audio/Textures/TextWarriorIntro.png"; //Nu se utilizeaza in Warrior class, ci in GameIntroInfo

//Scena CrossRoads
const std::string path_Warrior_toCave = "img-font-audio/Textures/warriorCave.png";
const std::string path_Warrior_toForest = "Timg-font-audio/extures/warriorForest.png";
const std::string path_Warrior_toVillage = "img-font-audio/Textures/warriorVillage.png";

//Scena Battle
const std::string path_Warrior_BattleUp = "img-font-audio/Textures/warriorBattleSceneUp.png";
const std::string path_Warrior_BattleAttacking = "img-font-audio/Textures/warriorBattleSceneAttacking.png"; 
const std::string path_Warrior_BattleUpAttacked = "img-font-audio/Textures/warriorBattleSceneUpAttacked.png";
const std::string path_Warrior_BattleAttackingAttacked = "img-font-audio/Textures/warriorBattleSceneAttackingAttacked.png";

//Items
const std::string path_Warrior_spear = "img-font-audio/Textures/spear.png"; 




//----------------------------------------For Rogue class----------------------------------------
const std::string path_Rogue_IntroText = "img-font-audio/Textures/TextRogueIntro.png"; //Nu se utilizeaza in Rogue class, ci in GameIntroInfo

//Scena CrossRoads
const std::string path_Rogue_toCave = "img-font-audio/Textures/rogueCave.png";
const std::string path_Rogue_toForest = "img-font-audio/Textures/rogueForest.png";
const std::string path_Rogue_toVillage = "img-font-audio/Textures/rogueVillage.png";

const std::string path_Rogue_BattleUp = "img-font-audio/Textures/rogueBattleSceneUp.png";
const std::string path_Rogue_BattleUpAttacked = "img-font-audio/Textures/rogueBattleSceneUpAttacked.png";

//Items
const std::string path_Rogue_knive = "img-font-audio/Textures/knive.png"; 
const std::string path_Rogue_trap = "img-font-audio/Textures/spikedTrap.png"; 




//----------------------------------------For Wizard class----------------------------------------
//Scena Intro
const std::string path_Wizard_IntroText = "img-font-audio/Textures/TextWizardIntro.png"; //Nu se utilizeaza in Wizard class, ci in GameIntroInfo

//Scena CrossRoads
const std::string path_Wizard_toForest = "img-font-audio/Textures/wizardForest.png";
const std::string path_Wizard_toVillage = "img-font-audio/Textures/wizardVillage.png";
const std::string path_Wizard_toCave = "img-font-audio/Textures/wizardCave.png";

//Scena Battle
const std::string path_Wizard_BattleUp = "img-font-audio/Textures/wizardBattleSceneUp.png";
const std::string path_Wizard_BattleUpAttacked = "img-font-audio/Textures/wizardBattleSceneUpAttacked.png";


//Items
const std::string path_Wizard_fireBall = "img-font-audio/Textures/fireball.png"; 
const std::string path_Wizard_iceBall = "img-font-audio/Textures/iceball.png"; 





//----------------------------------------For Ghoul class----------------------------------------
const std::string path_Ghoul_IntroTexture = "img-font-audio/Textures/ghoulIntroTexture.png";

const std::string path_Ghoul_MovingTexture = "img-font-audio/Textures/ghoulMoving.png";
const std::string path_Ghoul_AttackingTexture = "img-font-audio/Textures/ghoulAttacking.png";

const std::string path_Ghoul_BeingAttacked = "img-font-audio/Textures/goulBeingAttacked_Moving.png";
const std::string path_Ghoul_BeingColdAttacked = "img-font-audio/Textures/ghoulBeingColdAttacked.png"; 

const std::string path_Ghoul_AttackingAttacked = "img-font-audio/Textures/ghoulAttackingAttacked.png";
const std::string path_Ghoul_AttackingColdAttacked = "img-font-audio/Textures/ghoulAttackingColdAttacked.png";


//----------------------------------------For Troll class----------------------------------------
const std::string path_Troll_IntroTexture = "img-font-audio/Textures/trollIntroTexture.png"; 

const std::string path_Troll_MovingTexture = "img-font-audio/Textures/trollMoving.png"; 

//Moving
const std::string path_Troll_BeingAttacked = "img-font-audio/Textures/trollBeingAttacked_Moving.png"; 
const std::string path_Troll_BeingColdAttacked = "img-font-audio/Textures/trollBeingColdAttacked.png"; 
//Attacking
const std::string path_Troll_AttackingAttacked = "img-font-audio/Textures/trollAttackingAttacked.png";
const std::string path_Troll_AttackingColdAttacked = "img-font-audio/Textures/trollAttackingColdAttacked.png";

//Rock item for troll attack
const std::string path_Troll_Rock = "img-font-audio/Textures/rock.png"; 


const std::string path_Troll_AttackingTexture = "img-font-audio/Textures/trollAttacking.png"; 


//----------------------------------------For Griffon class----------------------------------------
const std::string path_Griffon_IntroTexture = "img-font-audio/Textures/griffonIntroTexture.png"; 

const std::string path_Griffon_MovingTexture = "img-font-audio/Textures/griffonMoving.png"; 
const std::string path_Griffon_AttackingTexture = "img-font-audio/Textures/griffonAttacking.png"; 

//Moving
const std::string path_Griffon_BeingAttacked = "img-font-audio/Textures/griffonBeingAttacked_Moving.png";
const std::string path_Griffon_BeingColdAttacked = "img-font-audio/Textures/griffonBeingColdAttacked_Moving.png";
//Attacking
const std::string path_Griffon_AttackingAttacked = "img-font-audio/Textures/griffonAttackingAttacked.png";
const std::string path_Griffon_AttackingColdAttacked = "img-font-audio/Textures/griffonAttackingColdAttacked.png";


//----------------------------------------For Text----------------------------------------
//Font
const std::string path_Font_CopperPLateGhothicLight = "img-font-audio/Fonts/COPRGTL.TTF";
const std::string path_Font_TimesNewRoman = "img-font-audio/Fonts/times.ttf";
const std::string path_Font_Arial = "img-font-audio/Fonts/arial.ttf"; 

//Background for text
const std::string path_BlackTextureForText = "img-font-audio/Textures/SalutPlayer.png";


//textura pentru testare
const std::string path_test = "img-font-audio/Textures/test.png";
const std::string path_test_2 = "img-font-audio/Textures/test_2.png";


#endif //ALLADDITIONALANDLIBRARIES_H
