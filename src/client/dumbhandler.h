/*
Minetest
Copyright (C) 2010-2013 celeron55, Perttu Ahola <celeron55@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#pragma once

#include "client/inputhandler.h"
#include "gui/mainmenumanager.h"
#include <zmqpp/zmqpp.hpp>
#include <string>

class DumbClientInputHandler : public InputHandler
{
public:
	DumbClientInputHandler(MyEventReceiver *receiver, std::string zmq_port) :
			m_receiver(receiver)
	{	
		/*std::string address = std::string("tcp://127.0.0.1:") + zmq_port;
		std::cout << "Try to connect to: " << address << std::endl;
		try {
			client.connect(address);
		} catch (zmqpp::zmq_internal_exception &e) {
			errorstream << "ZeroMQ error: " << e.what() << " (port: " << zmq_port << ")"
						<< std::endl;
			throw e;
		};*/
	};

	virtual bool isKeyDown(GameKeyType k) { return keyIsDown[keycache.key[k]]; }
	virtual bool wasKeyDown(GameKeyType k)
	{
		bool b = keyWasDown[keycache.key[k]];
		if (b)
			keyWasDown.unset(keycache.key[k]);
		return b;
	}
	virtual bool wasKeyPressed(GameKeyType k) { return keyWasPressed[keycache.key[k]]; }
	virtual bool wasKeyReleased(GameKeyType k) { return keyWasReleased[keycache.key[k]]; }
	virtual bool cancelPressed() { return keyWasDown[keycache.key[KeyType::ESC]]; }
	virtual float getMovementSpeed()
	{
		bool f = keyIsDown[keycache.key[KeyType::FORWARD]],
			 b = keyIsDown[keycache.key[KeyType::BACKWARD]],
			 l = keyIsDown[keycache.key[KeyType::LEFT]],
			 r = keyIsDown[keycache.key[KeyType::RIGHT]];
		if (f || b || l || r) {
			// if contradictory keys pressed, stay still
			if (f && b && l && r)
				return 0.0f;
			else if (f && b && !l && !r)
				return 0.0f;
			else if (!f && !b && l && r)
				return 0.0f;
			return 1.0f; // If there is a keyboard event, assume maximum speed
		}
		return 0.0f;
	}
	virtual float getMovementDirection()
	{
		float x = 0, z = 0;

		/* Check keyboard for input */
		if (keyIsDown[keycache.key[KeyType::FORWARD]])
			z += 1;
		if (keyIsDown[keycache.key[KeyType::BACKWARD]])
			z -= 1;
		if (keyIsDown[keycache.key[KeyType::RIGHT]])
			x += 1;
		if (keyIsDown[keycache.key[KeyType::LEFT]])
			x -= 1;

		if (x != 0 || z != 0) /* If there is a keyboard event, it takes priority */
			return atan2(x, z);
		return movementDirection;
	}
	virtual v2s32 getMousePos() { return mousepos; }
	virtual void setMousePos(s32 x, s32 y) { mousepos = v2s32(x, y); }

	virtual s32 getMouseWheel()
	{
		s32 a = mouse_wheel;
		mouse_wheel = 0;
		return a;
	}

	virtual void clearWasKeyPressed() { keyWasPressed.clear(); }
	virtual void clearWasKeyReleased() { keyWasReleased.clear(); }
	void clearInput()
	{
		keyIsDown.clear();
		keyWasDown.clear();
		keyWasPressed.clear();
		keyWasReleased.clear();

		mouse_wheel = 0;
	}

	void simulateEvent(const SEvent &event) {
		m_receiver->m_input_blocked = false;
		if (event.EventType == EET_MOUSE_INPUT_EVENT) {
			// we need this call to trigger GUIEvents
			// e.g. for updating selected/hovered elements
			// in the inventory
			// BUT somehow only simulating with this call
			// does not trigger any mouse movement at all..
			guienv->postEventFromUser(event);
		}
		// .. which is why we need this second call
		// TODO is it possible to have all behaviors with one call?
		m_receiver->OnEvent(event);
		m_receiver->m_input_blocked = true;
	}

	virtual void step(float dtime);

	std::vector<std::string> mouseButtons = {"dig", "middle", "place"};
	std::unordered_map<std::string, KeyPress> mouseButtonMap = {
		{"dig", "KEY_LBUTTON"},
		{"middle", "KEY_MBUTTON"},
		{"place", "KEY_RBUTTON"},
	};
	std::string keyPrefix = "keymap_";
	// TODO make this configurable?
	std::vector<std::string> supportedKeys = {
			"jump",
			"forward",
			"backward",
			"left",
			"right",
			"jump",
			"sneak",
			"dig",
			"middle", // middle mouse not part of standard key map
			"place",
			"drop",
			"hotbar_next",
			"hotbar_previous",
			"slot1",
			"slot2",
			"slot3",
			"slot4",
			"slot5",
			"slot6",
			"slot7",
			"slot8",
			"esc", // esc is not part of the standard key map
			"inventory",
			"aux1",
			// "chat", "cmd", // these result in errors
			"zoom",
			"autoforward",
			"pitchmove",
			"freemove",
			"fastmove",
			"noclip",
			"screenshot",
	};

	zmqpp::socket *socket;

private:
	// Event receiver to simulate events
	MyEventReceiver *m_receiver = nullptr;

	// ZMQ objects
	zmqpp::context context;

	// Whether a GUI (inventory/menu) was open
	bool wasGuiOpen = false;

	// The state of the mouse wheel
	s32 mouse_wheel = 0;

	// The current state of keys
	KeyList keyIsDown;

	// Like keyIsDown but only reset when that key is read
	KeyList keyWasDown;

	// Whether a key has just been pressed
	KeyList keyWasPressed;

	// Whether a key has just been released
	KeyList keyWasReleased;

	// Mouse observables
	v2s32 mousepos;
	v2s32 mousespeed;

	// Player observables
	float movementSpeed;
	float movementDirection;
};