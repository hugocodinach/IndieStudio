cmake_minimum_required(VERSION 3.11)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -g3")

SET(INCLUDE_DIRECTORY "./include")
SET(INCLUDE_DIRECTORY_UI "./include/UI")
SET(INCLUDE_DIRECTORY_UI_OBJ "./include/UI/Obj")
SET(INCLUDE_DIRECTORY_UI_SCENE "./include/UI/Scene")
SET(INCLUDE_DIRECTORY_AUDIO "./include/musicPlayer")
SET(INCLUDE_DIRECTORY_NETWORK_COMMUNICATION "./include/NetworkCommunication")
SET(INCLUDE_DIRECTORY_SCORES "./scores/include/")


add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

include_directories(${INCLUDE_DIRECTORY_UI})
include_directories(${INCLUDE_DIRECTORY_UI_OBJ})
include_directories(${INCLUDE_DIRECTORY_UI_SCENE})
include_directories(${INCLUDE_DIRECTORY_NETWORK_COMMUNICATION})
include_directories(${INCLUDE_DIRECTORY})
include_directories(${INCLUDE_DIRECTORY_AUDIO})
include_directories(${INCLUDE_DIRECTORY_SCORES})

if (WIN32)
    SET(INCLUDE_SFML "C:/Users/KLAIMAN/SFML-2.5.1/include")
    include_directories(${INCLUDE_SFML})
    SET(INCLUDE_IRR "C:/Users/KLAIMAN/irrlicht-1.8.4/include")
    include_directories(${INCLUDE_IRR})
    SET(INCLUDE_BOOST "C:/Users/KLAIMAN/boost_1_66_0")
    include_directories(${INCLUDE_BOOST})
endif(WIN32)

add_executable(
		bomberman

        src/main.cpp
        src/actionHandler/ActionHandler.cpp
        src/actionHandler/MapHandler.cpp
        src/actionHandler/EventManager.cpp
        src/actor/AI.cpp
        src/actor/AActor.cpp
        src/actor/Bomberman.cpp
        src/Obj/BlockDestruct.cpp
        src/PersSelection/PersSelection.cpp
        src/Obj/GameObj.cpp
        src/Obj/Bomb.cpp
        src/Obj/Camera.cpp
        src/Obj/DynamicObj.cpp
        src/Bonus/Bonus.cpp
        src/Bonus/WallPass.cpp
        src/controller/Controller.cpp
        src/Podium/PodiumManager.cpp
        src/gameModule/GameModule.cpp
        src/SplashScreen/SpashScreen.cpp
        src/SaverLoader/Saver.cpp
        src/SaverLoader/Loader.cpp
        src/UI/Obj/AInterfaceObj.cpp
        src/UI/Obj/UIButton.cpp
        src/UI/Obj/UIText.cpp
        src/UI/Obj/UIImage.cpp
        src/UI/Obj/UILateralMenu.cpp
        src/UI/Obj/UILateralText.cpp
        src/UI/Obj/UISmartText.cpp
        src/UI/Obj/UISmartListBox.cpp
		src/UI/Obj/UIEditBox.cpp
        src/UI/Scene/InterfaceMenu.cpp
        src/UI/Scene/InterfacePlay.cpp
        src/UI/Scene/InterfaceKeyBinding.cpp
        src/UI/Scene/InterfaceLocalLobby.cpp
		src/UI/Scene/InterfaceOption.cpp
		src/UI/Scene/InterfaceServerConnect.cpp
		src/UI/Scene/InterfaceServerRoom.cpp
		src/UI/Scene/InterfaceServerLobby.cpp
        src/UI/Scene/AInterfaceScene.cpp
        src/UI/Scene/InterfaceHelp.cpp
        src/UI/InterfaceManager.cpp
        src/NetworkCommunication/NetworkClient.cpp
        src/keyHandler/key.cpp

        src/Status/Status.cpp
        src/Particle/Particle.cpp
        src/Particle/TreeParticles.cpp
        src/Particle/PersoParticles.cpp
        src/Particle/MecheParticles.cpp
        src/Particle/ExplosionParticles.cpp
        src/utils.cpp
        src/musicPlayer/music.cpp
        src/musicPlayer/musicPlayer.cpp
        src/musicPlayer/sound.cpp
        scores/src/scores.cpp
)

if (WIN32)
    SET(LIBTHREAD "C:/Users/KLAIMAN/boost_1_66_0/stage_x86/lib/libboost_thread-vc141-mt-x32-1_66.lib")
    SET(LIBSYS "C:/Users/KLAIMAN/boost_1_66_0/stage_x86/lib/libboost_system-vc141-mt-x32-1_66.lib")
    SET(LIBTIME "C:/Users/KLAIMAN/boost_1_66_0/stage_x86/lib/libboost_timer-vc141-mt-x32-1_66.lib")
    SET(LIBDATE "C:/Users/KLAIMAN/boost_1_66_0/stage_x86/lib/libboost_date_time-vc141-mt-x32-1_66.lib")
    SET(LIBIOSTREAM "C:/Users/KLAIMAN/boost_1_66_0/stage_x86/lib/libboost_iostreams-vc141-mt-x32-1_66.lib")
    SET(LIBREGEX "C:/Users/KLAIMAN/boost_1_66_0/stage_x86/lib/libboost_regex-vc141-mt-x32-1_66.lib")
    SET(LIBIRR "C:/Users/KLAIMAN/irrlicht-1.8.4/lib/Win32-visualstudio/Irrlicht.lib")
    SET(LIBAUDIO "C:/Users/KLAIMAN/SFML-2.5.1/lib/sfml-audio.lib")
    
    target_link_libraries(bomberman ${LIBIRR} ${LIBSYS} ${LIBTHREAD}  ${LIBTIME} ${LIBDATE} ${LIBIOSTREAM} ${LIBREGEX} ${LIBAUDIO})

endif(WIN32)

if (UNIX)
    target_link_libraries(bomberman Irrlicht GL X11 Xrandr Xi Xxf86vm boost_system boost_thread boost_timer pthread boost_iostreams sfml-audio)

endif (UNIX)