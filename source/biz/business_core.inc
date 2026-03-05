#if defined _business_core_included
	#endinput
#endif
#define _business_core_included

#define MAX_BUSINESS			99

enum BInfo {ID, OwnerID, Taxes, Products, Income, Text3D:textlbl, Rob};
new BusinessInfo[MAX_BUSINESS][BInfo];

stock LoadBusiness() {
	new query_string[256];

	mysql_format(database, query_string, sizeof query_string, "SELECT b.ID, IFNULL(b.OwnerID, -1) AS OwnerID, b.Taxes, b.Products, b.Income, IFNULL(a.Name, \"Отсутствует\") AS OwnerName FROM bizz AS b LEFT OUTER JOIN players AS a ON b.OwnerID = a.ID ORDER BY b.ID");
	mysql_pquery(database, query_string, "GetBusiness");
}

forward GetBusiness();
public GetBusiness() {

	new rows = cache_get_row_count();
	if(rows)
	{

	for(new i = 0; i < rows; i++)
		{
			BusinessInfo[i][ID] = cache_get_field_content_int(i,"ID");
			BusinessInfo[i][OwnerID] = cache_get_field_content_int(i,"OwnerID");
			BusinessInfo[i][Taxes] = cache_get_field_content_int(i,"Taxes");
			BusinessInfo[i][Products] = cache_get_field_content_int(i,"Products");
			BusinessInfo[i][Income] = cache_get_field_content_int(i,"Income");
			BusinessInfo[i][Rob] = 0;

			new owner_name[MAX_PLAYER_NAME + 1];
			cache_get_field_content(i,"OwnerName", owner_name);

			format(small_string, sizeof small_string, "Бизнеc #%i\n\
				%s\n\
				Владелец: %s\n", 
				BusinessInfo[i][ID],
				Properties[i][IName],
				owner_name
				);

			BusinessInfo[i][textlbl] = CreateDynamic3DTextLabel(small_string, -1, 
				Pickup[i][ent_X], Pickup[i][ent_Y], Pickup[i][ent_Z],
				MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
			);
		}
	}
}

