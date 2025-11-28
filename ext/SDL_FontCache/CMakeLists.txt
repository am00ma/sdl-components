cmake_minimum_required(VERSION 3.20)
project(SDL_FontCache VERSION 0.10.0 LANGUAGES C)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

add_library(FontCache
    SDL_FontCache.h
    SDL_FontCache.c
)
include_directories(
  ${SDL2_INCLUDE_DIR}
  ${SDL2TTF_INCLUDE_DIRS})
target_include_directories(FontCache PUBLIC .)
target_link_libraries(
  FontCache PUBLIC
  ${SDL2_LIBRARY}
  ${SDL2TTF_LIBRARIES}
  ${CMAKE_DL_LIBS})
install(TARGETS FontCache DESTINATION lib)
install(FILES ./SDL_FontCache.h DESTINATION include)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION lib/pkgconfig)

option(SDL_FONTCACHE_BUILD_TESTS "Build tests" OFF)
if(SDL_FONTCACHE_BUILD_TESTS)
  add_executable(
    FontCache-tests
    test/main.c)
  file(COPY test/utf8_sample.txt DESTINATION ${CMAKE_BINARY_DIR})
  file(COPY test/fonts/FreeSans.ttf DESTINATION ${CMAKE_BINARY_DIR}/fonts)
  target_include_directories(FontCache PUBLIC .)
  target_link_libraries(FontCache-tests FontCache ${CMAKE_DL_LIBS} m)
endif()
