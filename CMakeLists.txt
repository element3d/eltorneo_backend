CMAKE_MINIMUM_REQUIRED(VERSION 3.13 FATAL_ERROR)
PROJECT("GodOfScore")
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

# Set the binary directory to a specific path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

# Specify the output directory for executables and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(third_party/cpr)
#add_subdirectory(third_party/firebase-cpp-sdk)
add_subdirectory(libwebp)
#find_package(WebP)


set (LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)
include_directories(${LIBS_DIR}/pqxx/include)
include_directories(${LIBS_DIR}/openssl/include)
include_directories(${LIBS_DIR}/rapidjson)
include_directories(${LIBS_DIR})
include_directories("C:/Program Files/PostgreSQL/15/include")
link_directories("C:\\Program Files\\PostgreSQL\\12\\lib")
include_directories("C:\\Program Files\\PostgreSQL\\9.6\\include")

add_executable(GodOfScore
    main.cpp

	stlplus/file_system.hpp
	stlplus/file_system.cpp
	stlplus/portability_fixes.hpp
	stlplus/portability_fixes.cpp
	stlplus/wildcard.hpp
	stlplus/wildcard.cpp

  managers/UserManager.h
  managers/UserManager.cpp
  managers/LeaguesManager.cpp
  managers/LeaguesManager.h
  managers/PNManager.h
  managers/PNManager.cpp
#  managers/CarManager.h
#  managers/CarManager.cpp
  managers/PQManager.h
  managers/PQManager.cpp
 # managers/ESerie.h
 # managers/ESerie.cpp
 # managers/EMake.h
 # managers/EMake.cpp
 # managers/EModel.h
 # managers/EModel.cpp


	routes/League.h
	routes/League.cpp
	routes/Team.h
	routes/Team.cpp
  routes/AuthRoute.h
  routes/AuthRoute.cpp
 # routes/UsersRoute.h
 # routes/UsersRoute.cpp
  routes/LeaguesRoute.h
  routes/LeaguesRoute.cpp
  routes/TeamsRoute.h
	routes/TeamsRoute.cpp
	routes/MatchesRoute.h
	routes/MatchesRoute.cpp
	routes/MatchesInitializer.h
	routes/MatchesInitializer.cpp
	routes/PredictsRoute.h
	routes/PredictsRoute.cpp

#	routes/CarsRoute.h
  #routes/CarsRoute.cpp
  routes/ImageUtils.h
  routes/ImageUtils.cpp

  routes/AnalyticsRoute.h
  routes/AnalyticsRoute.cpp

  routes/CachedTable.h
  routes/CachedTable.cpp
)


target_link_libraries(GodOfScore 
	#${LIBS_DIR}/pqxx/lib/x64/pqxx.lib
         webp
        webpdecoder
       # ${WebP_LIBRARIES}

     # libcrypto
       # libssl
#	libpq
  cpr::cpr
	#pthread
	"C:\\Program Files\\PostgreSQL\\15\\lib\\libpq.lib"
	${LIBS_DIR}/openssl/lib/x64/libssl.lib
	${LIBS_DIR}/openssl/lib/x64/libcrypto.lib
)


add_executable(elTorneo_cron
    cron_main.cpp
	managers/PQManager.h
	managers/PQManager.cpp
	managers/PNManager.h
	managers/PNManager.cpp
	routes/Team.h
	routes/Team.cpp
)

target_link_libraries(elTorneo_cron 
	#${LIBS_DIR}/pqxx/lib/x64/pqxx.lib
         webp
        webpdecoder
       # ${WebP_LIBRARIES}

     # libcrypto
       # libssl
#	libpq
  cpr::cpr
	#pthread
	"C:\\Program Files\\PostgreSQL\\15\\lib\\libpq.lib"
	${LIBS_DIR}/openssl/lib/x64/libssl.lib
	${LIBS_DIR}/openssl/lib/x64/libcrypto.lib
)