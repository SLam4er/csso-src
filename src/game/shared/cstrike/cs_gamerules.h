//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: The TF Game rules object
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//=============================================================================//

#ifndef CS_GAMERULES_H
#define CS_GAMERULES_H

#ifdef _WIN32
#pragma once
#endif


#include "teamplay_gamerules.h"
#include "convar.h"
#include "cs_shareddefs.h"
#include "gamevars_shared.h"

#ifdef CLIENT_DLL
	#include "c_cs_player.h"
	#include "networkstringtable_clientdll.h"
#else
	#include "cs_player.h"
	#include "funfactmgr_cs.h"
#endif

#include "cs_urlretrieveprices.h"

//extern ConVar mp_dynamicpricing;

#define CS_GAMERULES_BLACKMARKET_TABLE_NAME "BlackMarketTable"

#define	WINNER_NONE		0
#define WINNER_DRAW		1
#define WINNER_TER		TEAM_TERRORIST
#define WINNER_CT		TEAM_CT

#define MAX_WEAPON_NAME_POPUP_RANGE 128.0

//=============================================================================
// HPE_BEGIN:
// [tj] Forward declaration so we can track bot suicides in the game rules.
//=============================================================================

class CCSBot;

//=============================================================================
// HPE_END
//=============================================================================

extern ConVar mp_startmoney;
extern ConVar mp_maxmoney;
extern ConVar mp_tkpunish;
extern ConVar mp_c4timer;
extern ConVar mp_buytime;
extern ConVar mp_freezetime;
extern ConVar mp_playerid;
extern ConVar mp_death_drop_gun;
extern ConVar mp_death_drop_grenade;
extern ConVar mp_death_drop_defuser;
extern ConVar ammo_grenade_limit_total;

#ifndef CLIENT_DLL
	extern ConVar mp_autoteambalance;
#endif // !CLIENT_DLL

namespace TeamCashAward
{
	enum Type
	{
		NONE = 0,
		TERRORIST_WIN_BOMB,
		ELIMINATION_HOSTAGE_MAP_T,
		ELIMINATION_HOSTAGE_MAP_CT,
		ELIMINATION_BOMB_MAP,
		WIN_BY_TIME_RUNNING_OUT_HOSTAGE,
		WIN_BY_TIME_RUNNING_OUT_BOMB,
		WIN_BY_DEFUSING_BOMB,
		WIN_BY_HOSTAGE_RESCUE,
		LOSER_BONUS,
		LOSER_BONUS_CONSECUTIVE_ROUNDS,
		RESCUED_HOSTAGE,
		HOSTAGE_ALIVE,
		PLANTED_BOMB_BUT_DEFUSED,
		HOSTAGE_INTERACTION,
		LOSER_ZERO,
		CUSTOM_AWARD,
	};
};

namespace PlayerCashAward
{
	enum Type
	{
		NONE = 0,
		KILL_TEAMMATE,
		KILLED_ENEMY,
		BOMB_PLANTED,
		BOMB_DEFUSED,
		RESCUED_HOSTAGE,
		INTERACT_WITH_HOSTAGE,
		DAMAGE_HOSTAGE,
		KILL_HOSTAGE,
	};
};

//--------------------------------------------------------------------------------------------------------------
struct WeaponProgression
{
	CUtlString m_Name;
	int m_Kills;
};

static WeaponProgression ggWeaponProgressionCT[] =
{
	{ "bizon",		2 },
	{ "ump45",		2 },
	{ "p90",		2 },
	{ "nova",		2 },
	{ "mag7",		2 },
	{ "xm1014",		2 },
	{ "sawedoff",	2 },
	{ "galilar",	2 },
	{ "ak47",		2 },
	{ "m4a1",		2 },
	{ "sg556",		2 },
	{ "aug",		2 },
	{ "awp",		2 },
	{ "scar20",		2 },
	{ "negev",		2 },
	{ "tec9",		2 },
	{ "p250",		2 },
	{ "deagle",		2 },
	{ "fiveseven",	2 },
	{ "elite",		2 },
	{ "knifegg",	1 }
};

struct GGWeaponAliasName
{
	CSWeaponID id;
	const char *aliasName;
};

#define GGLIST_PISTOLS_TOTAL		9
#define GGLIST_RIFLES_TOTAL			7
#define GGLIST_MGS_TOTAL			2
#define GGLIST_SGS_TOTAL			4
#define GGLIST_SMGS_TOTAL			6
#define GGLIST_SNIPERS_TOTAL		3

#define GGLIST_PISTOLS_START	0
#define GGLIST_PISTOLS_LAST		(GGLIST_PISTOLS_START+GGLIST_PISTOLS_TOTAL-1)
#define GGLIST_RIFLES_START		GGLIST_PISTOLS_LAST+1
#define GGLIST_RIFLES_LAST		(GGLIST_RIFLES_START+GGLIST_RIFLES_TOTAL-1)
#define GGLIST_MGS_START		GGLIST_RIFLES_LAST+1
#define GGLIST_MGS_LAST			(GGLIST_MGS_START+GGLIST_MGS_TOTAL-1)
#define GGLIST_SGS_START		GGLIST_MGS_LAST+1
#define GGLIST_SGS_LAST			(GGLIST_SGS_START+GGLIST_SGS_TOTAL-1)
#define GGLIST_SMGS_START		GGLIST_SGS_LAST+1
#define GGLIST_SMGS_LAST			(GGLIST_SMGS_START+GGLIST_SMGS_TOTAL-1)
#define GGLIST_SNIPERS_START		GGLIST_SMGS_LAST+1
#define GGLIST_SNIPERS_LAST			(GGLIST_SNIPERS_START+GGLIST_SNIPERS_TOTAL-1)

//--------------------------------------------------------------------------------------------------------------
// NOTE: Array must be NULL-terminated
static GGWeaponAliasName ggWeaponAliasNameList[] =
{
	//pistols
	{ WEAPON_DEAGLE, "deagle" },
	{ WEAPON_REVOLVER, "revolver" },
	{ WEAPON_ELITE, "elite" },
	{ WEAPON_FIVESEVEN, "fiveseven" },
	{ WEAPON_GLOCK, "glock" },
	{ WEAPON_TEC9, "tec9" },
	{ WEAPON_HKP2000, "hkp2000" },
	{ WEAPON_USP, "usp_silencer" },
	{ WEAPON_P250, "p250" },

	//rifles
	{ WEAPON_AK47, "ak47" },
	{ WEAPON_AUG, "aug" },
	{ WEAPON_FAMAS, "famas" },
	{ WEAPON_GALILAR, "galilar" },
	{ WEAPON_M4A4, "m4a4" },
	{ WEAPON_M4A1, "m4a1_silencer" },
	{ WEAPON_SG556, "sg556" },

	//mgs
	{ WEAPON_M249, "m249" },
	{ WEAPON_NEGEV, "negev" },

	//shotguns
	{ WEAPON_XM1014, "xm1014" },
	{ WEAPON_MAG7, "mag7" },
	{ WEAPON_SAWEDOFF, "sawedoff" },
	{ WEAPON_NOVA, "nova" },

	//smgs
	{ WEAPON_MAC10, "mac10" },
	{ WEAPON_P90, "p90" },
	{ WEAPON_UMP45, "ump45" },
	{ WEAPON_BIZON, "bizon" },
	{ WEAPON_MP7, "mp7" },
	{ WEAPON_MP9, "mp9" },

	//snipers
	//	{ WEAPON_SSG08, "ssg08" },
	{ WEAPON_SCAR20, "scar20" },
	{ WEAPON_G3SG1, "g3sg1" },
	{ WEAPON_AWP, "awp" },

	{ WEAPON_NONE, "" }
};

#ifdef CLIENT_DLL
	#define CCSGameRules C_CSGameRules
	#define CCSGameRulesProxy C_CSGameRulesProxy
#endif

#ifndef CLIENT_DLL
struct playerscore_t
{
	int iPlayerIndex;
	int iScore;
};

class SpawnPoint : public CServerOnlyPointEntity
{
	DECLARE_CLASS( SpawnPoint, CServerOnlyPointEntity );
	DECLARE_DATADESC();
public:
	SpawnPoint();
	void Spawn( void );
	bool IsEnabled() { return m_bEnabled; }
	void InputSetEnabled( inputdata_t &inputdata );
	void InputSetDisabled( inputdata_t &inputdata );
	void InputToggleEnabled( inputdata_t &inputdata );
	void SetSpawnEnabled( bool bEnabled );

	int		m_iPriority;
	bool	m_bEnabled;
	int		m_nType;

	enum Type
	{
		Default = 0,
		Deathmatch = 1,
		ArmsRace = 2,
	};
};
#endif

class CCSGameRulesProxy : public CGameRulesProxy
{
public:
	DECLARE_CLASS( CCSGameRulesProxy, CGameRulesProxy );
	DECLARE_NETWORKCLASS();
};

class CCSGameRules : public CTeamplayRules
{
public:
	DECLARE_CLASS( CCSGameRules, CTeamplayRules );

	// Stuff that is shared between client and server.
	bool IsFreezePeriod();
	bool IsWarmupPeriod() const;
	float GetWarmupPeriodEndTime() const;	
	bool IsWarmupPeriodPaused();
	void SetWarmupPeriodStartTime( float fl )	{ m_fWarmupPeriodStart = fl; }
	float GetWarmupPeriodStartTime( void )	{ return m_fWarmupPeriodStart; }
	float GetWarmupRemainingTime();

	bool IsTimeOutActive() const { return ( IsTerroristTimeOutActive() || IsCTTimeOutActive() ); }
	bool IsTerroristTimeOutActive() const { return m_bTerroristTimeOutActive; }
	bool IsCTTimeOutActive() const { return m_bCTTimeOutActive; }

	void StartTerroristTimeOut( void );
	void StartCTTimeOut( void );
	void EndTerroristTimeOut( void );
	void EndCTTimeOut( void );

	float GetCTTimeOutRemaining() const { return m_flCTTimeOutRemaining; }
	float GetTerroristTimeOutRemaining() const { return m_flTerroristTimeOutRemaining; }

	int GetCTTimeOuts( ) const { return m_nCTTimeOuts; }
	int GetTerroristTimeOuts( ) const { return m_nTerroristTimeOuts; }

	void StartWarmup( void );
	void EndWarmup( void );

	void SetIsWarmupPeriod( bool bIsWarmup ) { m_bWarmupPeriod = bIsWarmup; }

	virtual bool ShouldCollide( int collisionGroup0, int collisionGroup1 );

	float GetMapRemainingTime();	// time till end of map, -1 if timelimit is disabled
	float GetMapElapsedTime();	// How much time has elapsed since the map started.
	float GetRoundRemainingTime();	// time till end of round
	float GetRoundStartTime();		// When this round started.
	float GetRoundElapsedTime();	// How much time has elapsed since the round started.
	float GetBuyTimeLength();
	int GetRoundLength() const { return m_iRoundTime; }
	int   SelectDefaultTeam( bool ignoreBots = false );
	int   GetHumanTeam();			// TEAM_UNASSIGNED if no restrictions

	void CalculateMaxGunGameProgressiveWeaponIndex( void );
	int GetMaxGunGameProgressiveWeaponIndex( void ) { return m_iMaxGunGameProgressiveWeaponIndex; }

	void	LoadMapProperties();
#ifndef CLIENT_DLL
	bool	UseMapFactionsForThisPlayer( CBasePlayer* pPlayer );
	int		GetMapFactionsForThisPlayer( CBasePlayer* pPlayer );
	bool	MapFactionsDefined( int teamnum );
#endif

	bool IsVIPMap() const;
	bool IsBombDefuseMap() const;
	bool IsHostageRescueMap() const;
	bool IsIntermission() const;
	bool IsLogoMap() const;
	bool IsSpawnPointValid( CBaseEntity *pSpot, CBasePlayer *pPlayer );
	bool IsSpawnPointHiddenFromOtherPlayers( CBaseEntity *pSpot, CBasePlayer *pPlayer, int nHideFromTeam = 0 );

	bool IsBuyTimeElapsed();
	bool IsMatchWaitingForResume( void );
	void SetMatchWaitingForResume( bool pause ) { m_bMatchWaitingForResume = pause; };

	int GetGamemode( void ) { return m_iCurrentGamemode; };

	CNetworkVar( int, m_iCurrentGamemode );

#ifndef CLIENT_DLL
	bool IsArmorFree();
#endif
	bool IsTeammateSolid( void ) const;				// returns true if teammates are solid obstacles in the current game mode

	bool HasHalfTime( void ) const;

	int GetCurrentGunGameWeapon( int nCurrentWeaponIndex, int nTeamID );
	int GetNextGunGameWeapon( int nCurrentWeaponIndex, int nTeamID );
	int GetPreviousGunGameWeapon( int nCurrentWeaponIndex, int nTeamID );
	bool IsFinalGunGameProgressiveWeapon( int nCurrentWeaponIndex, int nTeamID );
	int GetGunGameNumKillsRequiredForWeapon( int nCurrentWeaponIndex, int nTeamID );

	void AddGunGameWeapon( const char* pWeaponName, int nNumKillsToUpgrade, int nTeamID );
	int GetNumProgressiveGunGameWeapons( int nTeamID ) const;
	int GetProgressiveGunGameWeapon( int nWeaponIndex, int nTeamID ) const { return nTeamID == TEAM_CT ? m_GGProgressiveWeaponOrderCT[nWeaponIndex] : m_GGProgressiveWeaponOrderT[nWeaponIndex]; }
	int GetProgressiveGunGameWeaponKillRequirement( int nWeaponIndex, int nTeamID ) const { return nTeamID == TEAM_CT ? m_GGProgressiveWeaponKillUpgradeOrderCT[nWeaponIndex] : m_GGProgressiveWeaponKillUpgradeOrderT[nWeaponIndex]; }

	virtual int	DefaultFOV();

	// Get the view vectors for this mod.
	virtual const CViewVectors* GetViewVectors() const;

	void UploadGameStats( void );
	int  GetStartMoney( void );

	void AddHostageRescueTime( void );

	bool IsPlayingClassic( void ) const;

	bool IsPlayingAnyCompetitiveStrictRuleset( void ) const;

	virtual bool IsConnectedUserInfoChangeAllowed( CBasePlayer *pPlayer );

private:

	float GetExplosionDamageAdjustment(Vector & vecSrc, Vector & vecEnd, CBaseEntity *pEntityToIgnore); // returns multiplier between 0.0 and 1.0 that is the percentage of any damage done from vecSrc to vecEnd that actually makes it.
	float GetAmountOfEntityVisible(Vector & src, CBaseEntity *player); // returns a value from 0 to 1 that is the percentage of player visible from src.

	CNetworkVar( bool, m_bFreezePeriod );	 // TRUE at beginning of round, set to FALSE when the period expires
	CNetworkVar( bool, m_bWarmupPeriod );	 // 
	CNetworkVar( float, m_fWarmupPeriodStart );

	CNetworkVar( bool, m_bTerroristTimeOutActive );
	CNetworkVar( bool, m_bCTTimeOutActive );
	CNetworkVar( float, m_flTerroristTimeOutRemaining );
	CNetworkVar( float, m_flCTTimeOutRemaining );
	CNetworkVar( int, m_nTerroristTimeOuts );
	CNetworkVar( int, m_nCTTimeOuts );

	CNetworkVar( bool, m_bMatchWaitingForResume ); // When mp_pause_match is called, this state becomes true and will prevent the next freezetime from ending.
	CNetworkVar( int, m_iRoundTime );		 // (From mp_roundtime) - How many seconds long this round is.
	CNetworkVar( float, m_fRoundStartTime ); // time round has started
	CNetworkVar( float, m_flGameStartTime );
	CNetworkVar( int, m_nOvertimePlaying );
	CNetworkVar( int, m_iHostagesRemaining );
	CNetworkVar( bool, m_bAnyHostageReached );
	CNetworkVar( bool, m_bMapHasBombTarget );
	CNetworkVar( bool, m_bMapHasRescueZone );
	CNetworkVar( bool, m_bLogoMap );		 // If there's an info_player_logo entity, then it's a logo map.
	CNetworkVar( int, m_iNumGunGameProgressiveWeaponsCT );	// total number of CT gun game progressive weapons
	CNetworkVar( int, m_iNumGunGameProgressiveWeaponsT );	// total number of T gun game progressive weapons
	CNetworkArray( int, m_GGProgressiveWeaponOrderCT, 60 );	// CT gun game weapon order and # kills per weapon. Size is meant to be larger than the current number of different weapons defined in the CSWeaponID enum
	CNetworkArray( int, m_GGProgressiveWeaponOrderT, 60 );	// T gun game weapon order and # kills per weapon. Size is meant to be larger than the current number of different weapons defined in the CSWeaponID enum
	CNetworkArray( int, m_GGProgressiveWeaponKillUpgradeOrderCT, 60 );	// CT gun game number of kills per weapon. Size is meant to be larger than the current number of different weapons defined in the CSWeaponID enum
	CNetworkArray( int, m_GGProgressiveWeaponKillUpgradeOrderT, 60 );	// T gun game number of kills per weapon. Size is meant to be larger than the current number of different weapons defined in the CSWeaponID enum
	CNetworkVar( bool, m_bBlackMarket );
	
	int		m_iMapFactionCT;
	int		m_iMapFactionT;

	bool		m_bDontUploadStats;
	
	GamePhase m_gamePhase;

public:
	void SetPhase( GamePhase phase );
	GamePhase GetPhase( void ) const { return m_gamePhase; }

	CNetworkVar( bool, m_bBombDropped );
	CNetworkVar( bool, m_bBombPlanted );
	CNetworkVar( int, m_iRoundWinStatus );

	bool IsBlackMarket( void ) { return m_bBlackMarket; }
	int GetNumHostagesRemaining( void ) { return m_iHostagesRemaining; }

	virtual CBaseCombatWeapon *GetNextBestWeapon( CBaseCombatCharacter *pPlayer, CBaseCombatWeapon *pCurrentWeapon );

	virtual const unsigned char *GetEncryptionKey( void ) { return (unsigned char *)"d7NSuLq2"; } // both the client and server need this key

#ifdef CLIENT_DLL

	DECLARE_CLIENTCLASS_NOBASE(); // This makes datatables able to access our private vars.
	CCSGameRules();

#else

	DECLARE_SERVERCLASS_NOBASE(); // This makes datatables able to access our private vars.

	CCSGameRules();
	virtual ~CCSGameRules();

	void DumpTimers( void ) const;	// debugging to help track down a stuck server (rare?)

	CBaseEntity *GetPlayerSpawnSpot( CBasePlayer *pPlayer );

	static void EndRound();

	virtual void PlayerKilled( CBasePlayer *pVictim, const CTakeDamageInfo &info );
	virtual void Think();

	void SwitchTeamsAtRoundReset( void );

	void ClearGunGameData( void );

	void FreezePlayers( void );
	void UnfreezeAllPlayers( void );

	// Called at the end of GameFrame (i.e. after all game logic has run this frame)
	virtual void EndGameFrame( void );

	// Called when game rules are destroyed by CWorld
	virtual void LevelShutdown( void );

	virtual bool ClientCommand( CBaseEntity *pEdict, const CCommand &args );
	virtual void PlayerSpawn( CBasePlayer *pPlayer );
			void ShowSpawnPoints();

	virtual void ClientCommandKeyValues( edict_t *pEntity, KeyValues *pKeyValues );

	// [menglish] Set up anything for all players that changes based on new players spawning mid-game
	//				Find and return fun fact data
	// [pfreese] Tracking of "pistol" round
	virtual void SpawningLatePlayer(CCSPlayer* pLatePlayer);

	bool IsPistolRound();

	void HostageKilled() { m_hostageWasKilled = true; }
	void HostageInjured() { m_hostageWasInjured = true; }

	bool WasHostageKilled() { return m_hostageWasKilled; }
	bool WasHostageInjured() { return m_hostageWasInjured; }

    // [tj] So game rules can react to damage taken
    void PlayerTookDamage(CCSPlayer* player, const CTakeDamageInfo &damageInfo);


	virtual bool PlayTextureSounds( void ) { return true; }
	// Let the game rules specify if fall death should fade screen to black
	virtual bool  FlPlayerFallDeathDoesScreenFade( CBasePlayer *pl ) { return FALSE; }

	virtual void  RadiusDamage( const CTakeDamageInfo &info, const Vector &vecSrcIn, float flRadius, int iClassIgnore, CBaseEntity *pEntityIgnore );
	void RadiusDamage( const CTakeDamageInfo &info, const Vector &vecSrcIn, float flRadius, int iClassIgnore, bool bIgnoreWorld );

	virtual void UpdateClientData( CBasePlayer *pl );

	virtual CCSPlayer* CheckAndAwardAssists( CCSPlayer* pCSVictim, CCSPlayer* pKiller );

	// Death notices
	virtual void		DeathNotice( CBasePlayer *pVictim, const CTakeDamageInfo &info );

	virtual void			InitDefaultAIRelationships( void );

	virtual const char *GetGameDescription( void ) { return "Counter-Strike: Source Offensive"; }  // this is the game name that gets seen in the server browser
	virtual const char *AIClassText(int classType);

	virtual bool FShouldSwitchWeapon( CBasePlayer *pPlayer, CBaseCombatWeapon *pWeapon );

	virtual const char *SetDefaultPlayerTeam( CBasePlayer *pPlayer );

	// Called before entities are created
	virtual void LevelInitPreEntity();

	// Called after the map has finished loading.
	virtual void LevelInitPostEntity();

	virtual float FlPlayerFallDamage( CBasePlayer *pPlayer );

	virtual void ClientDisconnected( edict_t *pClient );

	// Recreate all the map entities from the map data (preserving their indices),
	// then remove everything else except the players.
	// Also get rid of all world decals.
	void CleanUpMap();

	void CheckFreezePeriodExpired();
	void CheckRoundTimeExpired();

	// check if the scenario has been won/lost
	// return true if the scenario is over, false if the scenario is still in progress
	bool CheckWinConditions( void );

	void TerminateRound( float tmDelay, int reason );

	// [tj] A place to check achievements that occur at the end of the round
	void ProcessEndOfRoundAchievements(int iWinnerTeam, int iReason);

	// The following round-related functions are called as follows:
	//
	// At Match Start:
	//		PreRestartRound() -> RestartRound() -> PostRestartRound()
	//
	// During Subsequent Round Gameplay:
	//		RoundWin() is called at the point when the winner of the round has been determined - prior to free-play commencing
	//		PreRestartRound() is called with 1 second remaining prior to the round officially ending (This is after a round
	//						  winner has been chosen and players are allowed to continue playing)
	//		RoundEnd() is then called when the round has completely ended
	//		RestartRound() is then called immediately after RoundEnd()
	//		PostRestartRound() is called immediately after RestartRound() has completed
	void PreRestartRound( void );
	void RestartRound( void );
	void RoundWin( void );
	void BalanceTeams( void );
	void HandleScrambleTeams( void );
	void HandleSwapTeams( void );
	void MoveHumansToHumanTeam( void );
	bool TeamFull( int team_id );
	int	 MaxNumPlayersOnTerrTeam();
	int  MaxNumPlayersOnCTTeam();
	bool TeamStacked( int newTeam_id, int curTeam_id  );
	bool FPlayerCanRespawn( CBasePlayer *pPlayer );
	void UpdateTeamScores();
	void CheckMapConditions();
	void MarkLivingPlayersOnTeamAsNotReceivingMoneyNextRound(int team);

	// Check various conditions to end the map.
	bool CheckGameOver();
	bool CheckFragLimit();

	void CheckLevelInitialized();
	void CheckRestartRound();

	virtual bool FPlayerCanTakeDamage( CBasePlayer *pPlayer, CBaseEntity *pAttacker, const CTakeDamageInfo &info );
	virtual int IPointsForKill( CBasePlayer *pAttacker, CBasePlayer *pKilled );

	bool CanPlayerHearTalker( CBasePlayer* pListener, CBasePlayer *pSpeaker, bool bTeamOnly );
	virtual bool PlayerCanHearChat( CBasePlayer *pListener, CBasePlayer *pSpeaker, bool bTeamOnly );


	// Checks if it still needs players to start a round, or if it has enough players to start rounds.
	// Starts a round and returns true if there are enough players.
	bool NeededPlayersCheck( bool &bNeededPlayers );

	// Setup counts for m_iNumTerrorist, m_iNumCT, m_iNumSpawnableTerrorist, m_iNumSpawnableCT, etc.
	void InitializePlayerCounts(
		int &NumAliveTerrorist,
		int &NumAliveCT,
		int &NumDeadTerrorist,
		int &NumDeadCT
		);

	// Check to see if the round is over for the various game types. Terminates the round
	// and returns true if the round should end.
	bool PrisonRoundEndCheck();
	bool BombRoundEndCheck( bool bNeededPlayers );
	bool HostageRescueRoundEndCheck( bool bNeededPlayers );

	// Check to see if the teams exterminated each other. Ends the round and returns true if so.
	bool TeamExterminationCheck(
		int NumAliveTerrorist,
		int NumAliveCT,
		int NumDeadTerrorist,
		int NumDeadCT,
		bool bNeededPlayers
		);

	void ReadMultiplayCvars();
	void SwapAllPlayers();

	void BroadcastSound( const char *sound, int team = -1 );


	// GUN GAME PROGRESSIVE FUNCTION
	bool GunGameProgressiveEndCheck( void );


	// VIP FUNCTIONS
	bool VIPRoundEndCheck( bool bNeededPlayers );
	void PickNextVIP();


	// BOMB MAP FUNCTIONS
	void GiveC4();
	bool IsThereABomber();
	bool IsThereABomb();

	// HOSTAGE MAP FUNCTIONS
	void HostageTouched();


	// Sets up g_pPlayerResource.
	virtual void CreateStandardEntities();
	virtual const char *GetChatPrefix( bool bTeamOnly, CBasePlayer *pPlayer );
	virtual const char *GetChatLocation( bool bTeamOnly, CBasePlayer *pPlayer );
	virtual const char *GetChatFormat( bool bTeamOnly, CBasePlayer *pPlayer );
	void ClientSettingsChanged( CBasePlayer *pPlayer );

	bool IsCareer( void ) const		{ return false; }		// returns true if this is a CZ "career" game

	virtual bool FAllowNPCs( void );

	struct GrenadeRecording_t
	{
		Vector vecSrc;
		QAngle vecAngles;
		Vector vecVel;
		AngularImpulse angImpulse;
		CBaseCombatCharacter *pPlayer;
		CSWeaponID weaponID;
		bool bIsValid;
	};

#ifndef CLIENT_DLL
	void RecordGrenadeThrow( Vector vecSrc, QAngle vecAngles, Vector vecVel, AngularImpulse angImpulse, CBaseCombatCharacter *pPlayer, CSWeaponID weaponID );
	void RethrowLastGrenade();
	GrenadeRecording_t m_pLastGrenade;
#endif

protected:
	virtual void GoToIntermission( void );

public:
	void SetOvertimePlaying( int nOvertimePlaying ) { m_nOvertimePlaying = nOvertimePlaying; }

	void SetScrambleTeamsOnRestart( bool scramble ) { m_bScrambleTeamsOnRestart = scramble; }
	bool GetScrambleTeamsOnRestart( void ) { return m_bScrambleTeamsOnRestart; }

	void SetSwapTeamsOnRestart( bool swapTeams ) { m_bSwapTeamsOnRestart = swapTeams; }
	bool GetSwapTeamsOnRestart( void ) { return m_bSwapTeamsOnRestart; }

	bool IsFriendlyFireOn();
	bool IsDamageDisabled();

	bool	IsLastRoundBeforeHalfTime( void );

	int		GetRoundsPlayed() { return m_iNumCTWins + m_iNumTerroristWins; }

	virtual void	SetAllowWeaponSwitch( bool allow );
	virtual bool	GetAllowWeaponSwitch( void );

	// VARIABLES FOR ALL TYPES OF MAPS
	bool m_bLevelInitialized;
	//int m_iRoundWinStatus;		// 1 == CT's won last round, 2 == Terrorists did, 3 == Draw, no winner
	int m_iTotalRoundsPlayed;
	int m_iUnBalancedRounds;	// keeps track of the # of consecutive rounds that have gone by where one team outnumbers the other team by more than 2

	// GAME TIMES
	int m_iFreezeTime;		// (From mp_freezetime) - How many seconds long the intro round (when players are frozen) is.
	float m_flRestartRoundTime;	// the global time when the round is supposed to end, if this is not 0

	int m_iNumTerrorist;		// The number of terrorists on the team (this is generated at the end of a round)
	int m_iNumCT;				// The number of CTs on the team (this is generated at the end of a round)
	int m_iNumSpawnableTerrorist;
	int m_iNumSpawnableCT;
	CUtlVector< int > m_arrSelectedHostageSpawnIndices; // The indices of hostage spawn locations selected for the match

	bool m_bFirstConnected;
	bool m_bCompleteReset;		// Set to TRUE to have the scores reset next time round restarts
	bool m_bScrambleTeamsOnRestart;
	bool m_bSwapTeamsOnRestart;

	short m_iNumCTWins;
	short m_iNumCTWinsThisPhase;
	short m_iNumTerroristWins;
	short m_iNumTerroristWinsThisPhase;

	int m_iNumConsecutiveCTLoses;		//SupraFiend: the number of rounds the CTs have lost in a row.
	int m_iNumConsecutiveTerroristLoses;//SupraFiend: the number of rounds the Terrorists have lost in a row.

	int m_iSpawnPointCount_Terrorist;		// Number of Terrorist spawn points
	int m_iSpawnPointCount_CT;				// Number of CT spawn points

	bool m_bTCantBuy;			// Who can and can't buy.
	bool m_bCTCantBuy;
	bool m_bMapHasBuyZone;

	int m_iLoserBonus;			// SupraFiend: the amount of money the losing team gets. This scales up as they lose more rounds in a row
	float m_tmNextPeriodicThink;

	float m_fWarmupNextChatNoticeTime;


	// HOSTAGE RESCUE VARIABLES
	int		m_iHostagesRescued;
	int		m_iHostagesTouched;
	float	m_flNextHostageAnnouncement;

    // [tj] Accessor for weapons donation ability
    bool GetCanDonateWeapon() { return m_bCanDonateWeapons; }

    // [tj] flawless and lossless round related flags
    bool m_bNoTerroristsKilled;
    bool m_bNoCTsKilled;
    bool m_bNoTerroristsDamaged;
    bool m_bNoCTsDamaged;

    // [tj] Find out if dropped weapons count as donations
    bool m_bCanDonateWeapons;

	// [tj] Keep track of first kill
	CHandle<CCSPlayer> m_pFirstKill;
	float m_firstKillTime;

	// [menglish] Keep track of first blood
	CHandle<CCSPlayer> m_pFirstBlood;
	float m_firstBloodTime;


    // [dwenger] Rescue-related achievement values
    CHandle<CCSPlayer> m_pLastRescuer;
    int     m_iNumRescuers;

	bool m_hostageWasInjured;
	bool m_hostageWasKilled;

	// [menglish] Fun Fact Manager
	CCSFunFactMgr *m_pFunFactManager;

	// [tj] To avoid rewriting the same piece of code, we can get all the information
	//		we want from one call that fills in an array of structures.
	struct TeamPlayerCounts
	{
		int totalPlayers;
		int totalAlivePlayers;
		int totalDeadPlayers; //sum of killedPlayers + suicidedPlayers + unenteredPlayers
		int killedPlayers;
		int suicidedPlayers;
		int unenteredPlayers;
	};

	void GetPlayerCounts(TeamPlayerCounts teamCounts[TEAM_MAXCOUNT]);

	int m_nLastFreezeEndBeep;


	// PRISON ESCAPE VARIABLES
	int		m_iHaveEscaped;
	bool	m_bMapHasEscapeZone;
	int		m_iNumEscapers;
	int		m_iNumEscapeRounds;		// keeps track of the # of consecutive rounds of escape played.. Teams will be swapped after 8 rounds


	// VIP VARIABLES
	int		m_iMapHasVIPSafetyZone;	// 0 = uninitialized;   1 = has VIP safety zone;   2 = DOES not have VIP safetyzone
	CHandle<CCSPlayer> m_pVIP;
	int		m_iConsecutiveVIP;


	// BOMB MAP VARIABLES
	bool	m_bTargetBombed;	// whether or not the bomb has been bombed
	bool	m_bBombDefused;	// whether or not the bomb has been defused
	bool	m_bMapHasBombZone;
//	bool	m_bBombDropped; -- moved to network cvars
//	bool	m_bBombPlanted; -- moved to network cvars
	EHANDLE m_pLastBombGuy;

	int		TeamCashAwardValue( int reason );
	int		PlayerCashAwardValue( int reason );
	void	AddTeamAccount( int team, int reason );
	void	AddTeamAccount( int team, int reason, int amount, const char* szAwardText = NULL );

	int GetOvertimePlaying( void ) const { return m_nOvertimePlaying; }

	int GetNumWinsToClinch( void ) const;

public:
	CBaseEntity* GetNextSpawnpoint( int teamNumber );

	void DoCoopSpawnAndNavInit( void );
	void AddSpawnPointToMasterList( SpawnPoint* pSpawnPoint );
	void GenerateSpawnPointListsFirstTime( void );
	void RefreshCurrentSpawnPointLists( void );

	void ShuffleSpawnPointLists( void );
	void ShuffleMasterSpawnPointLists( void );
	void SortSpawnPointLists( void );
	void SortMasterSpawnPointLists( void );
	void ShufflePlayerList( CUtlVector< CCSPlayer* > &playersList );

protected:
	CUtlVector< SpawnPoint* >	m_CTSpawnPointsMasterList;			// The master list of CT spawn points (contains all points whether enabled or disabled)
	CUtlVector< SpawnPoint* >	m_TerroristSpawnPointsMasterList;	// The master list of Terrorist spawn points (contains all points whether enabled or disabled)

	int m_iNextCTSpawnPoint;						// Used when picking the next CT spawn point to assign
	int m_iNextTerroristSpawnPoint;					// Used when picking the next Terrorist spawn point to assign
	CUtlVector< SpawnPoint* >	m_CTSpawnPoints;		// List of CT spawn points sorted by their priorities
	CUtlVector< SpawnPoint* >	m_TerroristSpawnPoints;	// List of Terrorist spawn points sorted by their priorities

private:

	// Don't allow switching weapons while gaining new technologies
	bool			m_bAllowWeaponSwitch;

	bool			m_bRoundTimeWarningTriggered;

	float			m_flLastThinkTime;

public:



	void AddPricesToTable( weeklyprice_t prices );
	virtual void CreateCustomNetworkStringTables( void );

#endif


#ifdef GAME_DLL
public:
	virtual void	GetTaggedConVarList( KeyValues *pCvarTagList );
#endif

public:
	const weeklyprice_t *GetBlackMarketPriceList( void );

	int GetBlackMarketPriceForWeapon( int iWeaponID );
	int GetBlackMarketPreviousPriceForWeapon( int iWeaponID );

	void SetBlackMarketPrices( bool bSetDefaults );

	bool IsSwitchingTeamsAtRoundReset( void ) { return m_bSwitchingTeamsAtRoundReset; }

	float CheckTotalSmokedLength( float flRadius, Vector vecGrenadePos, Vector from, Vector to );

	// Black market
	INetworkStringTable *m_StringTableBlackMarket;
	const weeklyprice_t *m_pPrices;

protected:
	bool m_bHasTriggeredRoundStartMusic;

private:
	bool m_bSwitchingTeamsAtRoundReset;
	int m_iMaxGunGameProgressiveWeaponIndex;
};

//-----------------------------------------------------------------------------
// Gets us at the team fortress game rules
//-----------------------------------------------------------------------------

inline CCSGameRules* CSGameRules()
{
	return static_cast<CCSGameRules*>(g_pGameRules);
}

#define IGNORE_SPECTATORS true
int UTIL_HumansInGame( bool ignoreSpectators = false );


//-----------------------------------------------------------------------------
// Music Selection
//-----------------------------------------------------------------------------

#ifdef CLIENT_DLL
void PlayMusicSelection( IRecipientFilter& filter, CsMusicType_t nMusicType );
#endif


//-----------------------------------------------------------------------------
// Purpose: Useful utility functions
//-----------------------------------------------------------------------------
#ifdef CLIENT_DLL

#else

	class CTFTeam;
	CTFTeam *GetOpposingTeam( CTeam *pTeam );
	bool EntityPlacementTest( CBaseEntity *pMainEnt, const Vector &vOrigin, Vector &outPos, bool bDropToGround );

#endif

#endif // TF_GAMERULES_H
