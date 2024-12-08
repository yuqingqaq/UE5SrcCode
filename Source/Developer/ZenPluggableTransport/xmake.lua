-- Copyright Epic Games, Inc. All Rights Reserved.

set_warnings("allextra", "error")
set_languages("cxx20")

includes('transport-sdk')
includes('zenbase')

if is_plat("windows") then
    includes("winsock")
end
