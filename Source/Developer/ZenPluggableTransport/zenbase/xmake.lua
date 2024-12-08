-- Copyright Epic Games, Inc. All Rights Reserved.

target('zenbase')
    set_kind("headeronly")
    set_group("libs")
    add_headerfiles("**.h")
    add_includedirs("include", {public=true})
