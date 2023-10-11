
find_package(PkgConfig REQUIRED)
find_package(tpeventsbus REQUIRED)

# pkg_check_modules(LIBCPPREST REQUIRED libcpprest2.10)

# Add your source files
set(SOURCES
    OutdatedRegistryException.cpp
)

set(HEADERS
    OutdatedRegistryException.h
    EntryType.h
)

set(INCLUDE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/includes)
set(LIB_OUTPUT_DIR ${CMAKE_BINARY_DIR}/lib)

file(COPY ${HEADERS} DESTINATION ${INCLUDE_OUTPUT_DIR})

add_library(tpregistry STATIC ${SOURCES})
target_link_libraries(tpregistry tpeventsbus)

set_target_properties(tpregistry PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})
export(TARGETS tpregistry FILE tpregistry-config.cmake)

install (
    TARGETS tpregistry
    EXPORT tpregistry-targets DESTINATION lib/tpregistry
    LIBRARY DESTINATION lib/tpregistry
    ARCHIVE DESTINATION lib/tpregistry
    RUNTIME DESTINATION bin/tpregistry
)
install (EXPORT tpregistry-targets DESTINATION lib/tpregistry)
install (FILES ${HEADERS} DESTINATION include/tpregistry)
install (FILES tpregistry-config.cmake DESTINATION lib/tpregistry)