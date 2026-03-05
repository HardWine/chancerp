local interop = require "interop"
local public = interop.public
local SendClientMessage, SetPlayerHealth
import(interop.native) -- assigns SendClientMessage and SetPlayerHealth from interop.native.SendClientMessage and interop.native.SetPlayerHealth

local COLOR_WHITE = 0xFFFFFFFF

local function tofloat(num) -- when calling native functions with a float parameter, a float value must be ensured
  return 0.0 + num
end

function public.OnPlayerConnect(playerid) -- adding a function to the "public" table automatically registers the callback (based on the name)
  SendClientMessage(playerid, COLOR_WHITE, "Hello from Lua!") -- calling a native function requires almost no modifications
end

local commands = {}

function commands.hp(playerid, params)
  local hp = tonumber(params)
  if not hp then
    return SendClientMessage(playerid, COLOR_WHITE, "Usage: /hp [value]")
  end
  SetPlayerHealth(playerid, tofloat(hp))
  SendClientMessage(playerid, COLOR_WHITE, "Your health was set to "..hp.."!")
  return true
end

function public.OnPlayerCommandText(playerid, cmdtext)
  playerid = interop.asinteger(playerid) -- YALP cannot guess the type of the arguments, so they must be explicitly converted
  cmdtext = interop.asstring(cmdtext)

  local ret
  cmdtext:gsub("^/([^ ]+) ?(.*)$", function(cmd, params)
    local handler = commands[string.lower(cmd)]
    if handler then
      ret = handler(playerid, params)
    end
  end)
  return ret
end

print("Lua script initialized!")