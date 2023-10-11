get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(${SELF_DIR}/tpregistry-targets.cmake)
get_filename_component(tpregistry_INCLUDE_DIRS "${SELF_DIR}/../../include/tpregistry" ABSOLUTE)
