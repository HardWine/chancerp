#if defined ban_rcon_included
	#endinput
#endif

#define ban_rcon_included

#include <YSI-Include\YSI\YSI\y_hooks>

stock PrintInt(i)
    printf("int: %d", i);

stock PrintFloat(Float:f)
    printf("float: %f", f);

stock PrintBool(bool:b)
    printf("bool: %s", (b)?("true"):("false"));

stock Print({_, Float}:arg, arg_type=tagof(arg))
{
	printf("arg_type = %i", arg_type);
    switch(arg_type)
    {
        case (tagof(_:)):
            PrintInt(arg);
        case (tagof(Float:)):
            PrintFloat(arg);
        case (tagof(bool:)):
            PrintBool(arg);
    }
}


hook OnRconCommand(cmd[]) {
	print("--Function overloading emulation test--");
    Print(1);
    Print(1.0);
    Print(true);
}