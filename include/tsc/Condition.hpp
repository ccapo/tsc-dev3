#ifndef CONDITION_HPP
#define CONDITION_HPP

#include "Global.hpp"
#include "Stats.hpp"
#include "Utils.hpp"

class Condition
{
	public:
	enum ConditionCategory
	{
		STATS,
		STATUS,
		NCAT
	} category;

	enum ConditionType
	{
		NONE,							// No Condition

		// Positive Stats Modification
		ELIXIR,							// Increased HP and MP
		HPMAX_PLUS,						// Increased HPMAX
		HP_PLUS,						// Increased HP
		MPMAX_PLUS,						// Increased MPMAX
		MP_PLUS,						// Increased MP
		HP_REGEN,						// HP Regenerate
		MP_REGEN,						// MP Regenerate
		STR_PLUS,						// Increased Strength
		SPD_PLUS,						// Increased Speed
		WIL_PLUS,						// Increased Willpower
		ACU_PLUS,						// Increased Acuity

		// Abilities
		FARSIGHTED,						// Increased Visual Perception
		MASK_SCENT,						// Mask Scent from Creatures
		LEVITATION,						// Float Above the Ground
		CREATURE_SENSE,					// Sense Presence of Creatures
		POISON_ANTIDOTE,				// Poison Antidote
		IMMUNE_FIRE,					// Immune to Fire Magic
		IMMUNE_WATER,					// Immune to Water Magic
		IMMUNE_EARTH,					// Immune to Earth Magic
		IMMUNE_WIND,					// Immune to Wind Magic

		MISC,							// Random Condition

		// Negative Stats Modification
		HP_MINUS,						// Decreased HP
		MP_MINUS,						// Decreased MP
		HP_DRAIN,						// HP Drain
		MP_DRAIN,						// MP Drain
		STR_MINUS,						// Decreased Strength
		SPD_MINUS,						// Decreased Speed
		WIL_MINUS,						// Decreased Willpower
		ACU_MINUS,						// Decreased Acuity

		// Afflictions
		NEARSIGHTED,					// Decreased Visual Perception
		CONFUSION,						// Random Movement
		PARALYSIS,						// Inability to Move or Attack
		STUNNED,						// Temporary Immobility
		POISON,							// Decreases HP
		BURDENED,						// Overloaded, Decreases all Stats
		VULNERABLE_FIRE,				// Vulnerable to Fire Magic
		VULNERABLE_WATER,				// Vulnerable to Water Magic
		VULNERABLE_EARTH,				// Vulnerable to Earth Magic
		VULNERABLE_WIND,				// Vulnerable to Wind Magic

		NCONS
	} type;								// Type of Condition

	bool first;							// First time condition is applied
	int duration;						// Duration of condtion (-1 = permanent, 0 = instantaneous)
	int interval;						// The frequency the condition is applied (-1 = once, 0 = every frame)
	int counter;						// Counter used to keep track of the frequency the condition is applied
	Stats stats;						// Stats for Condition
	Status status;						// Status for Condition
	string msgStart;					// Message displayed when Condition starts
	string msgStop;						// Message displayed when Condition stops
	bool displayMsgStart;				// Flag to control if msgStart is displayed
	bool displayMsgStop;				// Flag to control if msgStop is displayed

	Condition(): category(STATS), type(NONE), first(true), duration(0), interval(0), counter(0), stats(Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)), status(Status(0, 0, 0)), msgStart("msgStart"), msgStop("msgStop"), displayMsgStart(false), displayMsgStop(false) {}

	Condition(ConditionType type, int duration, int interval, Stats stats, Status status, string msgStart, string msgStop): category(STATS), type(type), first(true), duration(duration), interval(interval), counter(0), stats(stats), status(status), msgStart(msgStart), msgStop(msgStop), displayMsgStart(false), displayMsgStop(false) {}

	Condition(ConditionType type): type(type), first(true), counter(0)
	{
		category = STATS;

		switch( type )
		{
			case NONE:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "msgStart";
				msgStop = "msgStop";
				displayMsgStart = false;
				displayMsgStop = false;
				break;
			}
			case ELIXIR:
			{
				category = STATUS;
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(1000, 1000, 0);
				msgStart = "You Feel All Warm And Fuzzy Inside!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case HPMAX_PLUS:
			{
				duration = -1;
				interval = 0;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(10, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "Physically, You Feel A Lot Better!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case HP_PLUS:
			{
				category = STATUS;
				duration = 0;
				interval = 0;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(10, 0, 0);
				msgStart = "Physically, You Feel A Lot Better!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case MPMAX_PLUS:
			{
				duration = -1;
				interval = 0;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 10, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "Mentally, You Feel A Lot Better!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case MP_PLUS:
			{
				category = STATUS;
				duration = 0;
				interval = 0;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 10, 0);
				msgStart = "Mentally, You Feel A Lot Better!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case HP_REGEN:
			{
				category = STATUS;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(1, 0, 0);
				duration = -1;
				interval = 2*(STRMAX - 10);
				msgStart = "msgStart";
				msgStop = "msgStop";
				displayMsgStart = false;
				displayMsgStop = false;
				break;
			}
			case MP_REGEN:
			{
				category = STATUS;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 1, 0);
				duration = -1;
				interval = 2*(WILMAX - 10);
				msgStart = "msgStart";
				msgStop = "msgStop";
				displayMsgStart = false;
				displayMsgStop = false;
				break;
			}
			case STR_PLUS:
			{
				duration = -1;
				interval = 0;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 5, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Feel A Lot Stronger";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case SPD_PLUS:
			{
				duration = -1;
				interval = 0;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 5, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Start To Move Faster";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case WIL_PLUS:
			{
				duration = -1;
				interval = 0;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 5, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Feel A Lot More Driven";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case ACU_PLUS:
			{
				duration = -1;
				interval = 0;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 5);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "Mentally, You Feel A Lot More Focused";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case FARSIGHTED:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "Your Preception Increases";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case MASK_SCENT:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Are Able To Mask Your Scent";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case LEVITATION:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Begin To Float Above The Ground!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case CREATURE_SENSE:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Are Able To Sense The Creaures In Your Vicinity";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case POISON_ANTIDOTE:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Are No Longer Poisoned!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case IMMUNE_FIRE:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Are Immune To Fire Attacks!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case IMMUNE_WATER:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Are Immune To Water Attacks!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case IMMUNE_EARTH:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Are Immune To Earth Attacks!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case IMMUNE_WIND:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Are Immune To Wind Attacks!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}

			case MISC:
			{
				duration = -1; //10*FPSMAX;
				interval = 0;

				double xi[10];
				for(int i = 0; i < 10; i++) xi[i] = Gaussian<double>(10.0, 5.0);
				int hpmax = 10; //static_cast<int>(xi[0]);
				int ap = 0; //static_cast<int>(xi[1]);
				int dp = 0; //static_cast<int>(xi[2]);
				int str = 5; //static_cast<int>(xi[3]);
				int spd = 5; //static_cast<int>(xi[4]);
				int mpmax = 10; //static_cast<int>(xi[5]);
				int map = 0; //static_cast<int>(xi[6]);
				int mdp = 0; //static_cast<int>(xi[7]);
				int wil = 5; //static_cast<int>(xi[8]);
				int acu = 5; //static_cast<int>(xi[9]);

				cout << hpmax << ", " << ap << ", " << dp << ", " << str << ", " << spd << endl;
				cout << mpmax << ", " << map << ", " << mdp << ", " << wil << ", " << acu << endl;

				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "msgStart";
				msgStop = "msgStop";
				displayMsgStart = false;
				displayMsgStop = false;
				break;
			}

			case HP_MINUS:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(-10, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(-10, 0, 0);
				msgStart = "Physically, You Feel A Lot Better!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case MP_MINUS:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, -10, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, -10, 0);
				msgStart = "Mentally, You Feel A Lot Better!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case HP_DRAIN:
			{
				category = STATUS;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(-1, 0, 0);
				duration = -1;
				interval = 2*(STRMAX - 10);
				msgStart = "msgStart";
				msgStop = "msgStop";
				displayMsgStart = false;
				displayMsgStop = false;
				break;
			}
			case MP_DRAIN:
			{
				category = STATUS;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, -1, 0);
				duration = -1;
				interval = 2*(WILMAX - 10);
				msgStart = "msgStart";
				msgStop = "msgStop";
				displayMsgStart = false;
				displayMsgStop = false;
				break;
			}
			case NEARSIGHTED:
			{
				duration = 10*FPSMAX;
				interval = 0;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "Your Preception Decreases";
				msgStop = "Your Preception Returns";
				displayMsgStart = true;
				displayMsgStop = true;
				break;
			}
			case CONFUSION:
			{
				duration = 10*FPSMAX;
				interval = 0;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Begin To Feel Very Disoriented";
				msgStop = "You Feel A Lot Less Confused";
				displayMsgStart = true;
				displayMsgStop = true;
				break;
			}
			case PARALYSIS:
			{
				duration = 10*FPSMAX;
				interval = 0;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, -1000, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Are Paralyzed!";
				msgStop = "You Are Able To Move Again!";
				displayMsgStart = true;
				displayMsgStop = true;
				break;
			}
			case STUNNED:
			{
				duration = FPSMAX/2;
				interval = 0;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, -1000, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "msgStart";
				msgStop = "msgStop";
				displayMsgStart = false;
				displayMsgStop = false;
				break;
			}
			case POISON:
			{
				category = STATUS;
				duration = 10*FPSMAX;
				interval = FPSMAX;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(-1, 0, 0);
				msgStart = "You've Been Poisoned!";
				msgStop = "You No Longer Feel Poisoned";
				displayMsgStart = true;
				displayMsgStop = true;
				break;
			}
			case BURDENED:
			{
				duration = 1;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, -1, -1, 0, -2, 0, -1, -1, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Feel Your Belongings Weighing You Down";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case VULNERABLE_FIRE:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Are Vulnerable To Fire Attacks!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case VULNERABLE_WATER:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Are Vulnerable To Water Attacks!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case VULNERABLE_EARTH:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Are Vulnerable To Earth Attacks!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			case VULNERABLE_WIND:
			{
				duration = 0;
				interval = -1;
				// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
				stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				// Status(hp, mp, xpnext)
				status = Status(0, 0, 0);
				msgStart = "You Are Vulnerable To Wind Attacks!";
				msgStop = "msgStop";
				displayMsgStart = true;
				displayMsgStop = false;
				break;
			}
			default: break;
		}
	}

	virtual ~Condition() {}

	// Returns true if condition has finished
	inline bool Update()
	{
		bool result = false;

		// If the duration for this condition is zero, return true
		if( duration == 0 )
		{
			result = true;
		}
		else
		{
			// Otherwise decrease duration
			if( duration > 0 ) duration--;
		}

		// If duration is positive or negative, then return false
		return result;
	}
};

/*class ConditionList
{
	public:
	bool first;
	int max_size;						// Maximum number of ConditionList. -1 = Unlimited
	TCODList<Condition *> inventory;	// Inventory of ConditionList

	ConditionList(): first(true), max_size(-1) {}

	virtual ~ConditionList()
	{
		inventory.clear();
	}

	inline bool addToFront(Condition *condition)
	{
		// Inventory is full
		if( max_size > 0 && inventory.size() > max_size ) return false;

		inventory.push(condition);
		return true;
	}

	inline bool addToBack(Condition *condition)
	{
		// Inventory is full
		if( max_size > 0 && inventory.size() > max_size ) return false;

		inventory.insertBefore(condition, 0);
		return true;
	}

	inline void remove(Condition *condition)
	{
		inventory.remove(condition);
	}
};*/

class ConditionList2
{
	public:
	bool first;
	int max_size;				// Maximum number of ConditionList. -1 = Unlimited
	list<Condition> inventory;	// Inventory of ConditionList

	ConditionList2(): first(true), max_size(-1) {}

	virtual ~ConditionList2()
	{
		inventory.clear();
	}

	inline bool addToFront(Condition condition)
	{
		// Inventory is full
		if( max_size > 0 && inventory.size() > max_size ) return false;

		inventory.push_back(condition);
		return true;
	}

	inline bool addToBack(Condition condition)
	{
		// Inventory is full
		if( max_size > 0 && inventory.size() > max_size ) return false;

		inventory.push_front(condition);
		return true;
	}

	inline void remove(list<Condition>::iterator &it)
	{
		it = inventory.erase(it);
		it--;
	}
};

#endif