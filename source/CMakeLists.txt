# 
# External dependencies
# 
find_package(CpuFeatures REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(RapidJSON REQUIRED)
find_package(Boost 1.59 REQUIRED)


# set(GLEW_ROOT /usr CACHE)
# set(GLEW_INCLUDE_DIR /usr/include CACHE)
set(GLEW_USE_STATIC_LIBS TRUE)

# 
# Configuration for all sub-projects
# 

# Generate version-header
configure_file(version.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/${META_PROJECT_NAME}/${META_PROJECT_NAME}-version.h @ONLY)


# 
# Sub-projects
# 

# Libraries
set(IDE_FOLDER "")
add_subdirectory(xinfo)

# Examples
set(IDE_FOLDER "Examples")
add_subdirectory(examples)

# Tests
if(OPTION_BUILD_TESTS AND NOT MINGW)
    set(IDE_FOLDER "Tests")
    add_subdirectory(tests)
endif()


# 
# Deployment
# 

# Deploy generated headers
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/${META_PROJECT_NAME} DESTINATION include COMPONENT dev)
