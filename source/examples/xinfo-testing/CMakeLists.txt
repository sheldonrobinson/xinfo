
# 
# External dependencies
# 

# find_package(THIRDPARTY REQUIRED)
find_package(RapidJSON REQUIRED)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
find_package(X11 REQUIRED)
endif()

# 
# Executable name and options
# 

# Target name
set(target xinfo-testing)

# Exit here if required dependencies are not met
message(STATUS "Example ${target}")


# 
# Sources
# 

set(sources
    main.cpp
)


# 
# Create executable
# 

# Build executable
add_executable(${target}
    MACOSX_BUNDLE
    ${sources}
)

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})


# 
# Project options
# 

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)


# 
# Include directories
# 

target_include_directories(${target}
    PRIVATE
    ${DEFAULT_INCLUDE_DIRECTORIES}
    ${PROJECT_BINARY_DIR}/source/include
    ${RapidJSON_INCLUDE_DIRS}
)


# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LIBRARIES}
    ${META_PROJECT_NAME}::xinfo
)


# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
    ${DEFAULT_COMPILE_DEFINITIONS}
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
target_link_libraries(${target}
    PRIVATE
    ${X11_LIBRARIES} -lGL -lGLX -lGLdispatch -lXdmcp -lXau -lxcb -lbsd -ldl -lrt 
)
endif()


#
# Target Health
#

perform_health_checks(
    ${target}
    ${sources}
)

generate_coverage_report(${target})


# 
# Deployment
# 

# Executable
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT examples
    BUNDLE  DESTINATION ${INSTALL_BIN} COMPONENT examples
)
