-- Copyright Epic Games, Inc. All Rights Reserved.

target('transport-sdk')
    set_kind("headeronly")
    set_group("transports")
    add_headerfiles("**.h")
    add_includedirs("include", {public=true})
