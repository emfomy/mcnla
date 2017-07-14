function(MCNLA_FLAGS_FN)
  # Create flags

  set(incs "-I${CMAKE_INSTALL_PREFIX}/include")
  foreach(i ${INCS})
    string(REGEX REPLACE "^ " "" i "${i}")
    set(incs "${incs} -isystem ${i}")
  endforeach()
  string(REGEX REPLACE "  +" " " incs "${incs}")
  string(REGEX REPLACE "^ " "" incs "${incs}")

  set(libs "")
  foreach(l ${LIBS})
    string(REGEX REPLACE "^ " "" l "${l}")
    string(SUBSTRING ${l} 0 1 l0)
    if(${l0} MATCHES "-")
      set(libs "${libs} ${l}")
    else()
      set(libs "${libs} -l${l}")
    endif()
  endforeach()
  string(REGEX REPLACE "  +" " " libs "${libs}")
  string(REGEX REPLACE "^ " "" libs "${libs}")

  set(defs "")
  foreach(d ${DEFS})
    string(REGEX REPLACE "^ " "" d "${d}")
    string(SUBSTRING ${d} 0 1 d0)
    if(${d0} MATCHES "-")
      set(defs "${defs} ${d}")
    else()
      set(defs "${defs} -D${d}")
    endif()
  endforeach()
  string(REGEX REPLACE "  +" " " comflgs "${CMAKE_CXX_FLAGS} -DNDEBUG ${COMFLGS} ${defs}")
  string(REGEX REPLACE "^ " "" comflgs "${comflgs}")

  string(REGEX REPLACE "  +" " " lnkflgs "${LNKFLGS}")
  string(REGEX REPLACE "^ " "" lnkflgs "${lnkflgs}")

  # Set flags
  set(MCNLA_INCS "${incs}" PARENT_SCOPE)
  set(MCNLA_LIBS "${libs}" PARENT_SCOPE)
  set(MCNLA_COMFLGS "${comflgs}" PARENT_SCOPE)
  set(MCNLA_LNKFLGS "${lnkflgs}" PARENT_SCOPE)
endfunction()

mcnla_flags_fn()
unset(mcnla_flags_fn)