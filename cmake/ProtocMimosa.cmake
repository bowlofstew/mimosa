macro(mimosa_protoc name)
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${name}.pb.h ${CMAKE_CURRENT_SOURCE_DIR}/${name}.pb.cc
    COMMAND protoc --plugin=${mimosa_BINARY_DIR}/mimosa/rpc/gen/protoc-gen-mimosa --mimosa_out=. ${name}.proto
    DEPENDS protoc-gen-mimosa ${name}.proto
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  set_source_files_properties(
    ${CMAKE_CURRENT_SOURCE_DIR}/${name}.pb.h
    ${CMAKE_CURRENT_SOURCE_DIR}/${name}.pb.cc
    PROPERTIES GENERATED true)
endmacro(mimosa_protoc)
