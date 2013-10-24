#ifndef MENUSTATES_HPP
#define MENUSTATES_HPP
//------------------------------------------------------------------------
//
// Name: MenuStates.hpp
//
// Desc: All the states that can be assigned to the Menu class
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"

class Menu;

// Provide easy access
#define MenuIdleState MenuIdle::Instance()
#define MenuPauseState MenuPause::Instance()
#define MenuMainState MenuMain::Instance()
#define MenuHelpState MenuHelp::Instance()
#define MenuNewState MenuNew::Instance()
#define MenuIntroState MenuIntro::Instance()
#define MenuLoadState MenuLoad::Instance()
#define MenuSaveState MenuSave::Instance()
#define MenuGuardianState MenuGuardian::Instance()
#define MenuNpcState MenuNpc::Instance()
#define MenuGameState MenuGame::Instance()
#define MenuEquipInvState MenuEquipInv::Instance()
#define MenuWeaponInvState MenuWeaponInv::Instance()
#define MenuShieldInvState MenuShieldInv::Instance()
#define MenuArmourInvState MenuArmourInv::Instance()
#define MenuAccessoryInvState MenuAccessoryInv::Instance()
#define MenuItemInvState MenuItemInv::Instance()
#define MenuEquipShopState MenuEquipShop::Instance()
#define MenuEquipShopBuyState MenuEquipShopBuy::Instance()

#define MenuEquipShopBuyWeaponState MenuEquipShopBuyWeapon::Instance()
#define MenuEquipShopBuyShieldState MenuEquipShopBuyShield::Instance()
#define MenuEquipShopBuyArmourState MenuEquipShopBuyArmour::Instance()
#define MenuEquipShopBuyAccessoryState MenuEquipShopBuyAccessory::Instance()

#define MenuEquipShopSellState MenuEquipShopSell::Instance()

#define MenuEquipShopSellWeaponState MenuEquipShopSellWeapon::Instance()
#define MenuEquipShopSellShieldState MenuEquipShopSellShield::Instance()
#define MenuEquipShopSellArmourState MenuEquipShopSellArmour::Instance()
#define MenuEquipShopSellAccessoryState MenuEquipShopSellAccessory::Instance()

#define MenuItemShopState MenuItemShop::Instance()
#define MenuItemShopBuyState MenuItemShopBuy::Instance()
#define MenuItemShopSellState MenuItemShopSell::Instance()
#define MenuFerryState MenuFerry::Instance()
#define MenuInnState MenuInn::Instance()
#define MenuRestState MenuRest::Instance()
#define MenuDeathState MenuDeath::Instance()
#define MenuUIState MenuUI::Instance()

//------------------------------------------------------------------------
//
// This is the Idle State for the Menu
//
//------------------------------------------------------------------------
class MenuIdle : public State<Menu>
{
private:
	
	MenuIdle(){}

	// Copy constructor and assignment should be private
	MenuIdle(const MenuIdle&);
	MenuIdle &operator=(const MenuIdle&);
 
public:

	// This is a singleton
	static MenuIdle *Instance();
	
	void Enter(Menu *menu);
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu);
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Pause State for the Menu
//
//------------------------------------------------------------------------
class MenuPause : public State<Menu>
{
private:
	
	MenuPause(){}

	// Copy constructor and assignment should be private
	MenuPause(const MenuIdle&);
	MenuPause &operator=(const MenuPause&);
 
public:

	// This is a singleton
	static MenuPause *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Main Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuMain : public State<Menu>
{
private:
	
	MenuMain(){}

	// Copy constructor and assignment should be private
	MenuMain(const MenuMain&);
	MenuMain &operator=(const MenuMain&);
 
public:

	// This is a singleton
	static MenuMain *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the New Game Screen State for the Menu
//
//------------------------------------------------------------------------
class MenuNew : public State<Menu>
{
private:

	MenuNew(){}
	
	// Copy constructor and assignment should be private
	MenuNew(const MenuNew&);
	MenuNew &operator=(const MenuNew&);

public:

	// This is a singleton
	static MenuNew *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Load Screen State for the Menu
//
//------------------------------------------------------------------------
class MenuLoad : public State<Menu>
{
private:
	
	MenuLoad(){}

	// Copy constructor and assignment should be private
	MenuLoad(const MenuLoad&);
	MenuLoad &operator=(const MenuLoad&);
 
public:

	// This is a singleton
	static MenuLoad *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Save Screen State for the Menu
//
//------------------------------------------------------------------------
class MenuSave : public State<Menu>
{
private:
	
	MenuSave(){}

	// Copy constructor and assignment should be private
	MenuSave(const MenuSave&);
	MenuSave &operator=(const MenuSave&);
 
public:

	// This is a singleton
	static MenuSave *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Help Screen State for the Menu
//
//------------------------------------------------------------------------
class MenuHelp : public State<Menu>
{
private:

	MenuHelp(){}
	
	// Copy constructor and assignment should be private
	MenuHelp(const MenuHelp&);
	MenuHelp &operator=(const MenuHelp&);

public:

	// This is a singleton
	static MenuHelp *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Intro Screen State for the Menu
//
//------------------------------------------------------------------------
class MenuIntro : public State<Menu>
{
private:

	MenuIntro(){}
	
	// Copy constructor and assignment should be private
	MenuIntro(const MenuIntro&);
	MenuIntro &operator=(const MenuIntro&);

public:

	// This is a singleton
	static MenuIntro *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Game Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuGame : public State<Menu>
{
private:

	MenuGame(){}
	
	// Copy constructor and assignment should be private
	MenuGame(const MenuGame&);
	MenuGame &operator=(const MenuGame&);

public:

	// This is a singleton
	static MenuGame *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Inventory Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuEquipInv : public State<Menu>
{
private:

	MenuEquipInv(){}
	
	// Copy constructor and assignment should be private
	MenuEquipInv(const MenuEquipInv&);
	MenuEquipInv &operator=(const MenuEquipInv&);

public:

	// This is a singleton
	static MenuEquipInv *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Weapon Inventory Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuWeaponInv : public State<Menu>
{
private:

	MenuWeaponInv(){}
	
	// Copy constructor and assignment should be private
	MenuWeaponInv(const MenuWeaponInv&);
	MenuWeaponInv &operator=(const MenuWeaponInv&);

public:

	// This is a singleton
	static MenuWeaponInv *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Shield Inventory Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuShieldInv : public State<Menu>
{
private:

	MenuShieldInv(){}
	
	// Copy constructor and assignment should be private
	MenuShieldInv(const MenuShieldInv&);
	MenuShieldInv &operator=(const MenuShieldInv&);

public:

	// This is a singleton
	static MenuShieldInv *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Armour Inventory Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuArmourInv : public State<Menu>
{
private:

	MenuArmourInv(){}
	
	// Copy constructor and assignment should be private
	MenuArmourInv(const MenuShieldInv&);
	MenuArmourInv &operator=(const MenuShieldInv&);

public:

	// This is a singleton
	static MenuArmourInv *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Accessory Inventory Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuAccessoryInv : public State<Menu>
{
private:

	MenuAccessoryInv(){}
	
	// Copy constructor and assignment should be private
	MenuAccessoryInv(const MenuShieldInv&);
	MenuAccessoryInv &operator=(const MenuShieldInv&);

public:

	// This is a singleton
	static MenuAccessoryInv *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Item Inventory Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuItemInv : public State<Menu>
{
private:

	MenuItemInv(){}
	
	// Copy constructor and assignment should be private
	MenuItemInv(const MenuItemInv&);
	MenuItemInv &operator=(const MenuItemInv&);

public:

	// This is a singleton
	static MenuItemInv *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Guardian Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuGuardian : public State<Menu>
{
private:
	
	MenuGuardian(){}

	// Copy constructor and assignment should be private
	MenuGuardian(const MenuGuardian&);
	MenuGuardian &operator=(const MenuGuardian&);
 
public:

	// This is a singleton
	static MenuGuardian *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Npc Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuNpc : public State<Menu>
{
private:
	
	MenuNpc(){}

	// Copy constructor and assignment should be private
	MenuNpc(const MenuNpc&);
	MenuNpc &operator=(const MenuNpc&);
 
public:

	// This is a singleton
	static MenuNpc *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Item Shop Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuItemShop : public State<Menu>
{
private:
	
	MenuItemShop(){}

	// Copy constructor and assignment should be private
	MenuItemShop(const MenuItemShop&);
	MenuItemShop &operator=(const MenuItemShop&);
 
public:

	// This is a singleton
	static MenuItemShop *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Item Shop Buy Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuItemShopBuy : public State<Menu>
{
private:
	
	MenuItemShopBuy(){}

	// Copy constructor and assignment should be private
	MenuItemShopBuy(const MenuItemShopBuy&);
	MenuItemShopBuy &operator=(const MenuItemShopBuy&);
 
public:

	// This is a singleton
	static MenuItemShopBuy *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Item Shop Sell Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuItemShopSell : public State<Menu>
{
private:
	
	MenuItemShopSell(){}

	// Copy constructor and assignment should be private
	MenuItemShopSell(const MenuItemShopSell&);
	MenuItemShopSell &operator=(const MenuItemShopSell&);
 
public:

	// This is a singleton
	static MenuItemShopSell *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuEquipShop : public State<Menu>
{
private:
	
	MenuEquipShop(){}

	// Copy constructor and assignment should be private
	MenuEquipShop(const MenuEquipShop&);
	MenuEquipShop &operator=(const MenuEquipShop&);
 
public:

	// This is a singleton
	static MenuEquipShop *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Buy Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuEquipShopBuy : public State<Menu>
{
private:
	
	MenuEquipShopBuy(){}

	// Copy constructor and assignment should be private
	MenuEquipShopBuy(const MenuEquipShopBuy&);
	MenuEquipShopBuy &operator=(const MenuEquipShopBuy&);
 
public:

	// This is a singleton
	static MenuEquipShopBuy *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Buy Weapon Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuEquipShopBuyWeapon : public State<Menu>
{
private:
	
	MenuEquipShopBuyWeapon(){}

	// Copy constructor and assignment should be private
	MenuEquipShopBuyWeapon(const MenuEquipShopBuyWeapon&);
	MenuEquipShopBuyWeapon &operator=(const MenuEquipShopBuyWeapon&);
 
public:

	// This is a singleton
	static MenuEquipShopBuyWeapon *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Buy Shield Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuEquipShopBuyShield : public State<Menu>
{
private:
	
	MenuEquipShopBuyShield(){}

	// Copy constructor and assignment should be private
	MenuEquipShopBuyShield(const MenuEquipShopBuyShield&);
	MenuEquipShopBuyShield &operator=(const MenuEquipShopBuyShield&);
 
public:

	// This is a singleton
	static MenuEquipShopBuyShield *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Buy Armour Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuEquipShopBuyArmour : public State<Menu>
{
private:
	
	MenuEquipShopBuyArmour(){}

	// Copy constructor and assignment should be private
	MenuEquipShopBuyArmour(const MenuEquipShopBuyArmour&);
	MenuEquipShopBuyArmour &operator=(const MenuEquipShopBuyArmour&);
 
public:

	// This is a singleton
	static MenuEquipShopBuyArmour *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Buy Accessory Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuEquipShopBuyAccessory : public State<Menu>
{
private:
	
	MenuEquipShopBuyAccessory(){}

	// Copy constructor and assignment should be private
	MenuEquipShopBuyAccessory(const MenuEquipShopBuyAccessory&);
	MenuEquipShopBuyAccessory &operator=(const MenuEquipShopBuyAccessory&);
 
public:

	// This is a singleton
	static MenuEquipShopBuyAccessory *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Sell Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuEquipShopSell : public State<Menu>
{
private:
	
	MenuEquipShopSell(){}

	// Copy constructor and assignment should be private
	MenuEquipShopSell(const MenuEquipShopSell&);
	MenuEquipShopSell &operator=(const MenuEquipShopSell&);
 
public:

	// This is a singleton
	static MenuEquipShopSell *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Sell Weapon Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuEquipShopSellWeapon : public State<Menu>
{
private:
	
	MenuEquipShopSellWeapon(){}

	// Copy constructor and assignment should be private
	MenuEquipShopSellWeapon(const MenuEquipShopSellWeapon&);
	MenuEquipShopSellWeapon &operator=(const MenuEquipShopSellWeapon&);
 
public:

	// This is a singleton
	static MenuEquipShopSellWeapon *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Sell Shield Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuEquipShopSellShield : public State<Menu>
{
private:
	
	MenuEquipShopSellShield(){}

	// Copy constructor and assignment should be private
	MenuEquipShopSellShield(const MenuEquipShopSellShield&);
	MenuEquipShopSellShield &operator=(const MenuEquipShopSellShield&);
 
public:

	// This is a singleton
	static MenuEquipShopSellShield *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Sell Armour Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuEquipShopSellArmour : public State<Menu>
{
private:
	
	MenuEquipShopSellArmour(){}

	// Copy constructor and assignment should be private
	MenuEquipShopSellArmour(const MenuEquipShopSellArmour&);
	MenuEquipShopSellArmour &operator=(const MenuEquipShopSellArmour&);
 
public:

	// This is a singleton
	static MenuEquipShopSellArmour *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Equip Shop Sell Accessory Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuEquipShopSellAccessory : public State<Menu>
{
private:
	
	MenuEquipShopSellAccessory(){}

	// Copy constructor and assignment should be private
	MenuEquipShopSellAccessory(const MenuEquipShopSellAccessory&);
	MenuEquipShopSellAccessory &operator=(const MenuEquipShopSellAccessory&);
 
public:

	// This is a singleton
	static MenuEquipShopSellAccessory *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Inn Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuInn : public State<Menu>
{
private:
	
	MenuInn(){}

	// Copy constructor and assignment should be private
	MenuInn(const MenuInn&);
	MenuInn &operator=(const MenuInn&);
 
public:

	// This is a singleton
	static MenuInn *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Ferry Menu State for the Menu
//
//------------------------------------------------------------------------
class MenuFerry : public State<Menu>
{
private:
	
	MenuFerry(){}

	// Copy constructor and assignment should be private
	MenuFerry(const MenuFerry&);
	MenuFerry &operator=(const MenuFerry&);
 
public:

	// This is a singleton
	static MenuFerry *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Rest Screen State for the Menu
//
//------------------------------------------------------------------------
class MenuRest : public State<Menu>
{
private:
	
	MenuRest(){}

	// Copy constructor and assignment should be private
	MenuRest(const MenuRest&);
	MenuRest &operator=(const MenuRest&);
 
public:

	// This is a singleton
	static MenuRest *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Death Screen State for the Menu
//
//------------------------------------------------------------------------
class MenuDeath : public State<Menu>
{
private:
	
	MenuDeath(){}

	// Copy constructor and assignment should be private
	MenuDeath(const MenuDeath&);
	MenuDeath &operator=(const MenuDeath&);
 
public:

	// This is a singleton
	static MenuDeath *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the UI State for the Menu
//
//------------------------------------------------------------------------
class MenuUI : public State<Menu>
{
private:
	
	MenuUI(){}

	// Copy constructor and assignment should be private
	MenuUI(const MenuUI&);
	MenuUI &operator=(const MenuUI&);
 
public:

	// This is a singleton
	static MenuUI *Instance();
	
	void Enter(Menu *menu){}
	bool Update(Menu *menu, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Menu *menu);
	void Exit(Menu *menu){}
	bool Receive(Menu *menu, const Message &msg){return true;}

};

#endif