macro(add_dependency)
  cmake_parse_arguments(ARG ""
                            "GIT;TAG;BINARY"
                            ""
                            ${ARGN})
  set(REPOSITORY_URL https://github.com/${ARG_GIT})

  # Create a unique identifier for the dependency
  string(MAKE_C_IDENTIFIER "${ARG_GIT}" DEPENDENCY_ID)
  string(TOLOWER "${DEPENDENCY_ID}" DEPENDENCY_ID)

  get_property(IS_DEPENDENCY_PRESENT GLOBAL PROPERTY ${DEPENDENCY_ID}_VERSION SET)

  # Check if the dependency is already present
  if(${IS_DEPENDENCY_PRESENT})
    get_property(${DEPENDENCY_ID}_VERSION GLOBAL PROPERTY ${DEPENDENCY_ID}_VERSION)
    # Check that the version is the same
    if(NOT ${DEPENDENCY_ID}_VERSION STREQUAL ARG_TAG)
      message(FATAL_ERROR "Dependency ${ARG_GIT} version mismatched\n\t${${DEPENDENCY_ID}_VERSION} != ${ARG_TAG}")
    endif()
  else()
    message(STATUS "Configuring ${ARG_GIT}")

    # Define the version
    set_property(GLOBAL PROPERTY ${DEPENDENCY_ID}_VERSION ${ARG_TAG})

    # Check if released version
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
      if(NOT ${ARG_TAG} MATCHES "^tags/.*")
        message(WARNING "Using ${ARG_GIT} with unreleased version ${ARG_TAG}")
      endif()
    endif()

    # Fetch the repository
    FetchContent_Declare(${DEPENDENCY_ID}
      GIT_REPOSITORY ${REPOSITORY_URL}
      GIT_TAG ${ARG_TAG}
      SOURCE_SUBDIR __none__
    )
    FetchContent_MakeAvailable(${DEPENDENCY_ID})

    # Add cmake build if it exists
    if(EXISTS "${${DEPENDENCY_ID}_SOURCE_DIR}/CMakeLists.txt")
      add_subdirectory(${${DEPENDENCY_ID}_SOURCE_DIR} ${${DEPENDENCY_ID}_SOURCE_DIR}/../${DEPENDENCY_ID}-build)
    endif()

    # Handle python executable if it exists
    if(NOT DEFINED ${DEPENDENCY_ID}_EXECUTABLE)
      if(EXISTS "${${DEPENDENCY_ID}_SOURCE_DIR}/pyproject.toml")
        execute_process(COMMAND ${Python3_EXECUTABLE} -m pip install -e ${${DEPENDENCY_ID}_SOURCE_DIR} OUTPUT_QUIET RESULT_VARIABLE rv)
        if("${rv}" STREQUAL "0")
          set(${DEPENDENCY_ID}_EXECUTABLE ${VENV_DIR}/bin/${ARG_BINARY} CACHE STRING "path to the ${DEPENDENCY_ID} executable")
        endif()
      endif()
    endif()
  endif()
endmacro()
