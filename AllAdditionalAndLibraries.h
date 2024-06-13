#pragma once

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
#include <SFMl/Audio.hpp>
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
	Arrow,
	Trap,

	////////////
	None
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

	//Directie pentru rotatie (vectori de baza)
	//citite de la tastatur (W,A,S,D)
	short dir_x; 
	short dir_y; 

	//Nu trebuie modificate dupa scena 2!!!
	CategoriePlayer clasaPlayer;
	std::string playerName;
};



struct Characteristics 
{
	int health;
	int attackPower;
	int speedMovement;
};

static const std::map<std::string, Characteristics> enemyStats  
{
	{"Ghoul", {1000, 25, 2}},
	{"Troll", {2000, 50, 1}},
	{"Griffon", {1500, 35, 4}}
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//----------------------------------------Number of themes----------------------------------------
const short themes = 5;


//----------------------------------------Proprietati window----------------------------------------
const short width = 1792;
const short height = 1024;
const short frameLimit = 60;
const std::string gameName = "The Beginning of the End";


//----------------------------------------Calea catre muzica----------------------------------------
const std::string path_Main_Menu_music = "Music/Main_Menu.wav";
const std::string path_Exploring_music = "Music/Exploring.wav";
const std::string path_IntroBattle_music = "Music/IntroBattle.mp3"; 
const std::string path_BattleFinal_music = "Music/BattleFinal.wav";
const std::string path_IntroAfterBattle_music = "Music/IntroAfterBattle.mp3";



//----------------------------------------For GameIntroInfo_1----------------------------------------
const std::string path_Main_Menu_BackG = "Textures/Main_menu.png";

const std::string path_Main_Menu_GameN = "Textures/Game_Name.png";

const std::string path_Main_Menu_play = "Textures/play.png";
const std::string path_Main_Menu_playH = "Textures/play_mouseHeld.png";

const std::string path_Main_Menu_exit = "Textures/exit.png";
const std::string path_Main_Menu_exitH = "Textures/exit_mouseHeld.png";


//----------------------------------------For GameIntroInfo_2----------------------------------------
const std::string path_IntroBackG = "Textures/campLupta.png";
const std::string path_OldMan = "Textures/TheOldMan.png"; 

const std::string path_IntroText_1 = "Textures/Text_1.png";
const std::string path_IntroText_2 = "Textures/Text_2.png";
const std::string path_IntroText_3 = "Textures/Text_3.png";
const std::string path_IntroText_4 = "Textures/Text_4.png";
const std::string path_IntroText_5 = "Textures/Text_5.png";
const std::string path_IntroText_6 = "Textures/Text_6.png";

const std::string path_continue = "Textures/continue.png";
const std::string path_continueH = "Textures/continue_mouseHeld.png";


//----------------------------------------For GameInfoChoose----------------------------------------
const std::string path_Choosing_BackG = "Textures/FundalChoosePlayer.png";
const std::string path_Choosing_BackG_Wi = "Textures/FundalChoosePlayer_Wizard.png";
const std::string path_Choosing_BackG_Wa = "Textures/FundalChoosePlayer_Warrior.png";
const std::string path_Choosing_BackG_R = "Textures/FundalChoosePlayer_Rogue.png";


const std::string path_Choosing_Warrior = "Textures/warrior.png";
const std::string path_Choosing_WarriorH = "Textures/warrior_mouseHeld.png";

const std::string path_Choosing_Wizard = "Textures/wizard.png";
const std::string path_Choosing_WizardH = "Textures/wizard_mouseHeld.png";

const std::string path_Choosing_Rogue = "Textures/rogue.png";
const std::string path_Choosing_RogueH = "Textures/rogue_mouseHeld.png";


//----------------------------------------For GameCrossRoads----------------------------------------
const std::string path_CrossRoads_BackG = "Textures/CrossRoads.png";
const std::string path_CrossRoads_BackG_chest = "Textures/CrossRoads_chestScene.png";

const std::string path_CrossRoads_Chest = "Textures/chestImage.png";
const std::string path_CrossRoads_ChestOpen = "Textures/chestImageOpen.png";

const std::string path_CrossRoads_ChestInfo_1 = "Textures/chestInfo_1.png";
const std::string path_CrossRoad_ChestInfo_2_fireball = "Textures/chestInfo_2_fireball.png"; 
const std::string path_CrossRoad_ChestInfo_2_iceball = "Textures/chestInfo_2_iceball.png"; 

const std::string path_CrossRoads_Open = "Textures/open.png";
const std::string path_CrossRoads_Open_mouseH = "Textures/open_mouseHeld.png";

const std::string path_CrossRoads_Skip = "Textures/skip.png";
const std::string path_CrossRoads_Skip_mouseH = "Textures/skip_mouseHeld.png";

const std::string path_caveInscription = "Textures/caveTEXT.png";
const std::string path_forestInscription = "Textures/forestTEXT.png";
const std::string path_villageInscription = "Textures/villageTEXT.png";

const std::string path_caveInscription_mouseH = "Textures/caveTEXT_mouseHeld.png";
const std::string path_forestInscription_mouseH = "Textures/forestTEXT_mouseHeld.png";
const std::string path_villageInscription_mouseH = "Textures/villageTEXT_mouseHeld.png";

const std::string path_caveInscription_choosed = "Textures/caveTEXT_choosed.png";
const std::string path_forestInscription_choosed = "Textures/forestTEXT_choosed.png";
const std::string path_villageInscription_choosed = "Textures/villageTEXT_choosed.png";


//----------------------------------------For GameInfoIntroBattle----------------------------------------
const std::string path_IntroBattle_BackGCave = "Textures/intrarePerstera.png";
const std::string path_IntroBattle_CaveDescrip = "Textures/descriereCave.png"; 

const std::string path_IntroBattle_BackGForest = "Textures/intrareForest.png";
const std::string path_IntroBattle_ForestDescrip = "Textures/descriereForest.png";

const std::string path_IntroBattle_BackGVillage = "Textures/intrareSat.png";
const std::string path_IntroBattle_VillageDescrip = "Textures/descriereSat.png";


//----------------------------------------For GameInfoBattleScene----------------------------------------
const std::string path_BattleScene_BackGCave = "Textures/battleSceneCave.png";
const std::string path_BattleScene_BackGForest = "Textures/battleSceneForest.png";
const std::string path_BattleScene_BackGVillage = "Textures/battleSceneVillage.png";



//----------------------------------------For Warrior class----------------------------------------
const std::string path_Warrior_IntroText = "Textures/TextWarriorIntro.png"; //Nu se utilizeaza in Warrior class, ci in GameIntroInfo

//Scena CrossRoads
const std::string path_Warrior_toCave = "Textures/warriorCave.png";
const std::string path_Warrior_toForest = "Textures/warriorForest.png";
const std::string path_Warrior_toVillage = "Textures/warriorVillage.png";

//Scena Battle
const std::string path_Warrior_BattleUp = "Textures/warriorBattleSceneUp.png";
const std::string path_Warrior_BattleAttacking = "Textures/warriorBattleSceneAttacking.png"; 
const std::string path_Warrior_BattleUpAttacked = "Textures/warriorBattleSceneUpAttacked.png";
const std::string path_Warrior_BattleAttackingAttacked = "Textures/warriorBattleSceneAttackingAttacked.png";

//Items
const std::string path_Warrior_spear = "Textures/spear.png"; 




//----------------------------------------For Rogue class----------------------------------------
const std::string path_Rogue_IntroText = "Textures/TextRogueIntro.png"; //Nu se utilizeaza in Rogue class, ci in GameIntroInfo

//Scena CrossRoads
const std::string path_Rogue_toCave = "Textures/rogueCave.png";
const std::string path_Rogue_toForest = "Textures/rogueForest.png";
const std::string path_Rogue_toVillage = "Textures/rogueVillage.png";

const std::string path_Rogue_BattleUp = "Textures/rogueBattleSceneUp.png";
const std::string path_Rogue_BattleUpAttacked = "Textures/rogueBattleSceneUpAttacked.png";

//Items
const std::string path_Rogue_arrow = "Textures/arrow.png"; 



//----------------------------------------For Wizard class----------------------------------------
//Scena Intro
const std::string path_Wizard_IntroText = "Textures/TextWizardIntro.png"; //Nu se utilizeaza in Wizard class, ci in GameIntroInfo

//Scena CrossRoads
const std::string path_Wizard_toForest = "Textures/wizardForest.png";
const std::string path_Wizard_toVillage = "Textures/wizardVillage.png";
const std::string path_Wizard_toCave = "Textures/wizardCave.png";

//Scena Battle
const std::string path_Wizard_BattleUp = "Textures/wizardBattleSceneUp.png";
const std::string path_Wizard_BattleUpAttacked = "Textures/wizardBattleSceneUpAttacked.png";


//Items
const std::string path_Wizard_fireBall = "Textures/fireball.png"; 
const std::string path_Wizard_iceBall = "Textures/iceball.png"; 





//----------------------------------------For Ghoul class----------------------------------------
const std::string path_Ghoul_IntroTexture = "Textures/ghoulIntroTexture.png";

const std::string path_Ghoul_MovingTexture = "Textures/ghoulMoving.png";
const std::string path_Ghoul_AttackingTexture = "Textures/ghoulAttacking.png";

const std::string path_Ghoul_BeingAttacked = "Textures/goulBeingAttacked_Moving.png";
const std::string path_Ghoul_BeingColdAttacked = "Textures/ghoulBeingColdAttacked.png"; 

const std::string path_Ghoul_AttackingAttacked = "Textures/ghoulAttackingAttacked.png";
const std::string path_Ghoul_AttackingColdAttacked = "Textures/ghoulAttackingColdAttacked.png";

const std::string path_Ghoul_IntroMesajAtack = "Textures/ghoulMesajAtack.png";


//----------------------------------------For Troll class----------------------------------------
const std::string path_Troll_IntroTexture = "Textures/trollIntroTexture.png"; 

const std::string path_Troll_MovingTexture = "Textures/trollMoving.png"; 

//Moving
const std::string path_Troll_BeingAttacked = "Textures/trollBeingAttacked_Moving.png"; 
const std::string path_Troll_BeingColdAttacked = "Textures/trollBeingColdAttacked.png"; 
//Attacking
const std::string path_Troll_AttackingAttacked = "Textures/trollAttackingAttacked.png";
const std::string path_Troll_AttackingColdAttacked = "Textures/trollAttackingColdAttacked.png";


const std::string path_Troll_AttackingTexture = "Textures/trollAttacking.png"; 


//----------------------------------------For Griffon class----------------------------------------
const std::string path_Griffon_IntroTexture = "Textures/griffonIntroTexture.png"; 

const std::string path_Griffon_MovingTexture = "Textures/griffonMoving.png"; 
const std::string path_Griffon_AttackingTexture = "Textures/griffonAttacking.png"; 


//----------------------------------------For Text----------------------------------------
//Font
const std::string path_Font_CopperPLateGhothicLight = "Fonts/COPRGTL.TTF";
const std::string path_Font_TimesNewRoman = "Fonts/times.ttf";
//Background for text
const std::string path_BlackTextureForText = "Textures/SalutPlayer.png";


//textura pentru testare
const std::string path_test = "Textures/test.png";
const std::string path_test_2 = "Textures/test_2.png";
