#if defined job_system_included
	#endinput
#endif

#define job_system_included

forward Job_OnPlayerConnect(playerid);
forward Job_OnPlayerDisconnect(playerid);
forward Job_OnPlayerDeath(playerid);
forward Job_OnPlayerSpawn(playerid);
forward Job_OnPlayerStateChange(playerid, newstate, oldstate);

enum 
	PlayerJob: {
		JOB_NONE = 0, // Отсутсвует
		JOB_BUS_LS, // Работа водителя автобуса LS
		JOB_BUS_SF, // Работа водителя автобуса SF
		JOB_BUS_LV, // Работа водителя автобуса LV
		JOB_TRASH, // Работа на мусоровозе
		JOB_ARMY_MUSSION // Доставка боеприпасов в армии
	};

new 
	PlayerJob: player_job[MAX_PLAYERS char];

/**
 * [SetPlayerJob устанавливает работу игроку]
 * @param {int} playerid      [ID Игрока]
 * @param {PlayerJob} PlayerJob:job [ID Работы >> PlayerJob]
 */
stock PlayerJob:SetPlayerJob(playerid, PlayerJob:job) {
	return player_job{playerid} = job;
}

/**
 * [GetPlayerJob получает текущую работу игрока >> PlayerJob]
 * @param {int} playerid [ID Игрока]
 */
stock PlayerJob:GetPlayerJob(playerid) {
	return player_job{playerid};
}

/**
 * [ResetPlayerJob сбрасывает работу игрока]
 * @param {int} playerid [ID Игрока]
 */
stock ResetPlayerJob(playerid) {
	player_job{playerid} = JOB_NONE;
	return 1;
}

stock StopPlayerJob(playerid, PlayerJob:job) {
	SendClientMessage(playerid, -1, ""COLOR_ORANGE"Рабочий день завершен.");

	switch(job) {
		case JOB_BUS_LS, JOB_BUS_SF, JOB_BUS_LV: {
			return CallLocalFunction("BusDriver_OnPlayerLeaveJob", "i", playerid);
		}
		case JOB_TRASH: {
			return CallLocalFunction("Trash_OnPlayerLeaveJob", "i", playerid);
		}
	}
	return 1;
}


public Job_OnPlayerConnect(playerid) {
	return ResetPlayerJob(playerid);
}

public Job_OnPlayerDisconnect(playerid) {
	return ResetPlayerJob(playerid);
}

public Job_OnPlayerStateChange(playerid, newstate, oldstate) {
	new 
		PlayerJob: job = GetPlayerJob(playerid);

	if(job != JOB_NONE) {
		if(newstate == PLAYER_STATE_WASTED) { // Игрок умер на работе
			return StopPlayerJob(playerid, job);
		} else if(newstate == PLAYER_STATE_SPAWNED) { // Игрок заспавнился 
			return StopPlayerJob(playerid, job);
		}
	}
	return 0;
}
