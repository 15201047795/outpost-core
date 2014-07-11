
#include <unittest/harness.h>

#include <l3test/script/engine.h>

using namespace l3test::script;

/*
 * Send data from Lua through a channel to the C++ side.
 */
TEST(EnginePacketTest, sendDataFromLua)
{
	Engine engine;

	engine.setLuaPath("lua_src/?.lua;lua_src/?/init.lua;ext/?/init.lua;ext/?.lua");
	engine.setLuaCPath("bin/lua/?.so");

	Channel::Ptr channel(new Channel);
	engine.registerChannel(channel, "tm");

	engine.execute(R"(
bitstream = require "bitstream"
ccsds = require "packetgenerator.ccsds"

frame = ccsds.transfer_frame {
    frame_header = {
        type = ccsds.TYPE_AD,
        scid = 0x1B,
        vcid = 0,
        sequence_count = 1
    },
    application_data = bitstream.new('\x01\x02\x03')
}

tm:send(frame:bytes())
)");

	ASSERT_TRUE(channel->hasPackets());
	EXPECT_EQ(10U, channel->getPacketLength());

	auto packet = channel->getPacket();

	uint8_t data[10] = { 0x00, 0x1B, 0x00 ,0x09, 0x01, 0x01, 0x02, 0x03, 0xF2, 0x93 };
	EXPECT_ARRAY_EQ(uint8_t, data, packet.data(), 10);
}

/*
 * Receive data in the Lua environment.
 *
 * Failed assert statements inside Lua are reported as uncaught exceptions
 * in googletest.
 */
TEST(EnginePacketTest, sendDataToLua)
{
    Engine engine;

    engine.setLuaPath("lua_src/?.lua;lua_src/?/init.lua;ext/?/init.lua;ext/?.lua");
    engine.setLuaCPath("bin/lua/?.so");

    Channel::Ptr channel(new Channel);
    engine.registerChannel(channel, "tc");

    uint8_t data[10] = { 0x00, 0x1B, 0x00 ,0x09, 0x01, 0x01, 0x02, 0x03, 0xF2, 0x93 };

    channel->append(data, sizeof(data));
    channel->finishPacket();

    engine.execute(R"(
assert = require "luassert"
bitstream = require "bitstream"
ccsds = require "packetgenerator.ccsds"

assert.equals(1, tc:getNumberOfPackets())

packet = tc:get()
tc:next()

frame = ccsds.transfer_frame {
    frame_header = {
        type = ccsds.TYPE_AD,
        scid = 0x1B,
        vcid = 0,
        sequence_count = 1
    },
    application_data = bitstream.new('\x01\x02\x03')
}

assert.same(frame:bytes(), packet)
)");
}