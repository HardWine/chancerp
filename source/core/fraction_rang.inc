#if defined fraction_rang_included
	#endinput
#endif

#define fraction_rang_included

forward FractionRang_OnGameModeInit();
forward LoadFractionRang();
forward GetFractionRangTitle(const arrayID, rang[]);
forward FindFractionMaxRang(const fractionid);
forward FindFractionMinRang(const fractionid);

enum 
	fraction_rang_info__ {
		FRI_ID,
		FRI_FractionTitle[MAX_FRACTION_TITLE],
		FRI_FractionID,
		FRI_RangTitle[MAX_RANG_TITLE],
		FRI_RangID,
		FRI_SkinMale,
		FRI_SkinFemale,
		FRI_isInvite,
		FRI_isUninvite,
		FRI_isRang,
		FRI_isGnews,
		FRI_InviteRang,
		FRI_LeaderRang
	};

new 
	FractionRangInfo[MAX_FRACTION_RANG][fraction_rang_info__];
//INSERT INTO `player_fraction`(`PlayerID`, `Fraction`, `Rang`) VALUES (player, fraction, @minrang);
public FractionRang_OnGameModeInit() {
	mysql_pquery(database, 
		"SELECT \
			`ID`, \
			`Fraction`, \
			CONVERT(`Fraction`, SIGNED) as FractionID, \
			`Rang`, \
			CONVERT(`Rang`, SIGNED) as RangID, \
			`SkinMale`, \
			`SkinFemale`, \
			CONVERT(`isInvite`, SIGNED) as isInvite, \
			CONVERT(`isUninvite`, SIGNED) as isUninvite, \
			CONVERT(`isRang`, SIGNED) as isRang, \
			CONVERT(`isGnews`, SIGNED) as isGnews, \
			CONVERT(`InviteRang`, SIGNED) as InviteRang, \
			CONVERT(`LeaderRang`, SIGNED) as LeaderRang \
		FROM \
			"TABLE_FRACTION_RANG"", "LoadFractionRang");
}

public LoadFractionRang() {
	new 
		rows = cache_get_row_count();

	for(new i = 0; i < rows; i++) {
		FractionRangInfo[i][FRI_ID] = cache_get_field_content_int(i, "ID");
		cache_get_field_content(i, "Fraction", FractionRangInfo[i][FRI_FractionTitle]);
		FractionRangInfo[i][FRI_FractionID] = cache_get_field_content_int(i, "FractionID");
		cache_get_field_content(i, "Rang", FractionRangInfo[i][FRI_RangTitle]);
		FractionRangInfo[i][FRI_RangID] = cache_get_field_content_int(i, "RangID");
		FractionRangInfo[i][FRI_SkinMale] = cache_get_field_content_int(i, "SkinMale");
		FractionRangInfo[i][FRI_SkinFemale] = cache_get_field_content_int(i, "SkinFemale");

		FractionRangInfo[i][FRI_isInvite] = cache_get_field_content_int(i, "isInvite");
		FractionRangInfo[i][FRI_isInvite] = FractionRangInfo[i][FRI_isInvite] - 1;
		FractionRangInfo[i][FRI_isUninvite] = cache_get_field_content_int(i, "isUninvite");
		FractionRangInfo[i][FRI_isUninvite] = FractionRangInfo[i][FRI_isUninvite] -1;
		FractionRangInfo[i][FRI_isRang] = cache_get_field_content_int(i, "isRang");
		FractionRangInfo[i][FRI_isRang] = FractionRangInfo[i][FRI_isRang] -1;
		FractionRangInfo[i][FRI_isGnews] = cache_get_field_content_int(i, "isGnews");
		FractionRangInfo[i][FRI_isGnews] = FractionRangInfo[i][FRI_isGnews] -1;

		FractionRangInfo[i][FRI_InviteRang] = cache_get_field_content_int(i, "InviteRang");
		FractionRangInfo[i][FRI_InviteRang] = FractionRangInfo[i][FRI_InviteRang] -1;
		FractionRangInfo[i][FRI_LeaderRang] = cache_get_field_content_int(i, "LeaderRang");
		FractionRangInfo[i][FRI_LeaderRang] = FractionRangInfo[i][FRI_LeaderRang] -1;

		printf("Итерация %i ID = %i Fraction %s (%i) Rang %s (%i) isInvite = %i isIninvite %i", i, 
			FractionRangInfo[i][FRI_ID], 
			FractionRangInfo[i][FRI_FractionTitle],
			FractionRangInfo[i][FRI_FractionID],
			FractionRangInfo[i][FRI_RangTitle],
			FractionRangInfo[i][FRI_RangID],
			FractionRangInfo[i][FRI_isInvite],
			FractionRangInfo[i][FRI_isUninvite]
		);
	
	}
}

public GetFractionRangTitle(const arrayID, rang[]) {
	if(arrayID >= 0 && arrayID < MAX_FRACTION_RANG) {
		strmid(rang, FractionRangInfo[arrayID][FRI_RangTitle], 0, strlen(FractionRangInfo[arrayID][FRI_RangTitle]), MAX_RANG_TITLE);
		return 1;
	}
	return -1;
}

public FindFractionMaxRang(const fractionid) {
	new 
		max_rang = 0;

	for(new i = 0; i < MAX_FRACTION_RANG; i++) {
		if(FractionRangInfo[i][FRI_FractionID] == fractionid) {
			if(i > max_rang) {
				max_rang = i;
			}
			max_rang = i;
			printf("ID = %i iter = %i", FractionRangInfo[i][FRI_FractionID], i);
		}
	}
	return max_rang;
}