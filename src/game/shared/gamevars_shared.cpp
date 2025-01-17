//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//
#include "cbase.h"
#include "gamevars_shared.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#ifdef GAME_DLL
void MPForceCameraCallback( IConVar *var, const char *pOldString, float flOldValue )
{
	if ( mp_forcecamera.GetInt() < OBS_ALLOW_ALL || mp_forcecamera.GetInt() >= OBS_ALLOW_NUM_MODES )
	{
		mp_forcecamera.SetValue( OBS_ALLOW_TEAM );
	}
}
#endif 

// some shared cvars used by game rules
ConVar mp_forcecamera( 
	"mp_forcecamera", 
#ifdef CSTRIKE
	"0", 
#else
	"1",
#endif
	FCVAR_REPLICATED,
	"Restricts spectator modes for dead players"
#ifdef GAME_DLL
	, MPForceCameraCallback 
#endif
	);
	
ConVar mp_allowspectators(
	"mp_allowspectators", 
	"1.0", 
	FCVAR_REPLICATED,
	"toggles whether the server allows spectator mode or not" );

ConVar friendlyfire(
	"mp_friendlyfire",
	"0",
	FCVAR_REPLICATED | FCVAR_NOTIFY,
	"Allows team members to injure other members of their team"
	);

ConVar mp_disable_damage(
	"mp_disable_damage",
	"0",
	FCVAR_REPLICATED | FCVAR_NOTIFY,
	"When set, any damage is disabled"
);

ConVar mp_teammates_are_enemies(
	"mp_teammates_are_enemies",
	"0",
	FCVAR_REPLICATED | FCVAR_NOTIFY,
	"When set, your teammates act as enemies and all players are valid targets."
	);

ConVar mp_buy_anywhere(
	"mp_buy_anywhere",
	"0",
	FCVAR_REPLICATED | FCVAR_NOTIFY,
	"When set, players can buy anywhere, not only in buyzones. 0 = default. 1 = both teams. 2 = Terrorists. 3 = Counter-Terrorists."
	);

ConVar mp_buy_during_immunity(
	"mp_buy_during_immunity",
	"0",
	FCVAR_REPLICATED | FCVAR_NOTIFY,
	"When set, players can buy when immune, ignoring buytime. 0 = default. 1 = both teams. 2 = Terrorists. 3 = Counter-Terrorists."
	);

ConVar mp_fadetoblack( 
	"mp_fadetoblack", 
	"0", 
	FCVAR_REPLICATED | FCVAR_NOTIFY, 
	"fade a player's screen to black when he dies" );


ConVar sv_hudhint_sound( "sv_hudhint_sound", "1", FCVAR_REPLICATED );