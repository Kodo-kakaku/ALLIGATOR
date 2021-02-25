# CMakeList.txt: проект CMake для Alligator_cmake; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

set (THIS Alligator)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${THIS} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${THIS} VERSION 0.0.1)
endif()

add_executable (Alligator_cmake   "main.cpp" "alligator.h" "keeper.h")

set_target_properties(Alligator_cmake PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(Alligator_cmake
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(Alligator_cmake PRIVATE
        /W4
    )
else ()
    target_compile_options(Alligator_cmake PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


if (NOT DEFINED ENV{PC_00330_80000_00000_AA472})
    
    set(CPACK_GENERATOR DEB)

    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

    set(CPACK_PACKAGE_CONTACT cdandrey@gmail.com)

    include(CPack)

endif()
