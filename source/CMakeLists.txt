
find_package(PkgConfig REQUIRED)


# pkg_check_modules(LIBCPPREST REQUIRED libcpprest2.10)

# Add your source files
set(SOURCES
)

set(HEADERS
)

set(INCLUDE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/includes)
set(LIB_OUTPUT_DIR ${CMAKE_BINARY_DIR}/lib)

file(COPY ${HEADERS} DESTINATION ${INCLUDE_OUTPUT_DIR})

add_library(TP.CPP.Registry ${SOURCES})


set_target_properties(TP.CPP.Registry PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})
export(TARGETS TP.CPP.Registry FILE TP.CPP.RegistryConfig.cmake)

install (TARGETS TP.CPP.Registry DESTINATION /usr/local/lib)
install (FILES ${HEADERS} DESTINATION /usr/local/include/tpregistry)