    file(GLOB_RECURSE SRCFILES "*.cpp")

    file(GLOB ABILITY_FILES "abilities/*.cpp" "console/inputManager.cpp")
    
    list(REMOVE_ITEM SRCFILES ${ABILITY_FILES})


    target_sources(seabattle PRIVATE ${SRCFILES})