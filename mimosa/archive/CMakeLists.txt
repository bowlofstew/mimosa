add_library(mimosa-archive
  writer.cc)

install(FILES
  entry.hh
  writer.hh
  DESTINATION include/mimosa/archive/)

target_link_libraries(mimosa-archive mimosa archive)

install(TARGETS mimosa-archive
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
