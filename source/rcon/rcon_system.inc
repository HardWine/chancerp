#if defined rcon_system_included
    #endinput
#endif

#define rcon_system_included

#include <YSI-Include\YSI\YSI\y_hooks>

hook OnRconCommand(cmd[]) {
    new
        command[32],
        subparams[64];

    if(!sscanf(cmd, "s[32]s[64]", command, subparams)) {
        if(strcmp(command, "Player.GetPlayerAccID", false) == 0) {
            new
                result = Player.GetPlayerAccID(subparams);

            printf("Player.GetPlayerAccID(%s) = %i", subparams, result);
            return Y_HOOKS_BREAK_RETURN_1;
        } else if(strcmp(command, "Ban.IsAccBanned", false) == 0) {
            new
                result = Ban.IsAccBanned(strval(subparams));

            printf("Ban.IsAccBanned(%s) = %i", subparams, result);
            return Y_HOOKS_BREAK_RETURN_1;
        } else if(strcmp(command, "Fraction.PrintArray", false) == 0) {
            new
                result = Fraction.PrintArray(strval(subparams));

            printf("Fraction.PrintArray(%s) = %i", subparams, result);
            return Y_HOOKS_BREAK_RETURN_1;
        } else if(strcmp(command, "Fraction.SetLeader", false) == 0) {
            new
                arrayID,
                accID;

            if(!sscanf(subparams, "ii", arrayID, accID)) {
                new
                    result = Fraction.SetLeader(arrayID, accID);
                printf("Fraction.SetLeader(%i, %i) = %i", arrayID, accID, result);
            }
            return Y_HOOKS_BREAK_RETURN_1;
        } else if(strcmp(command, "Fraction.ResetLeader", false) == 0) {
            new
                result = Fraction.ResetLeader(strval(subparams));

            printf("Fraction.ResetLeader(%s) = %i", subparams, result);
            return Y_HOOKS_BREAK_RETURN_1;
        }
    }

    return Y_HOOKS_BREAK_RETURN_1;
}