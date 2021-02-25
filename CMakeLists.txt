cmake_minimum_required(VERSION 3.2)

project(ip_sortus VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
 

configure_file(version.h.in version.h)

add_executable(alligator main.cpp)
add_library (keep keeper.h)
add_library (alligat alligator.h)
#add_executable(test_version test_version.cpp)

set_target_properties(alligator keep alligat PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(alligator
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(alligator PRIVATE
        Alligator
)

if (MSVC)
    target_compile_options(alligator PRIVATE
        /W4
    )
    target_compile_options(keep PRIVATE
        /W4
    )
    target_compile_options(alligat PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(alligator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(keep PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
      target_compile_options(alligat PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS alligator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
