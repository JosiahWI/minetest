target_sources(common
  PRIVATE
    address.cpp
    connection.cpp
    connectionthreads.cpp
    networkpacket.cpp
    serverpackethandler.cpp
    serveropcodes.cpp
    socket.cpp
)

target_sources(minetest
  PRIVATE
    clientopcodes.cpp
    clientpackethandler.cpp
)
