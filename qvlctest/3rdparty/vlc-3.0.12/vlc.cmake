set(VlcMasterIncludePath "${CMAKE_CURRENT_LIST_DIR}/include")

if(MINGW)
    set(libvlccore "${CMAKE_CURRENT_LIST_DIR}/build/libvlccore.dll")
    set(libvlc "${CMAKE_CURRENT_LIST_DIR}/build/libvlc.dll")
    set(axvlc "${CMAKE_CURRENT_LIST_DIR}/build/axvlc.dll")
    set(npvlc "${CMAKE_CURRENT_LIST_DIR}/build/npvlc.dll")
endif()
