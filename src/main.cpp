#include "screenwave.hpp"

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <wayland-client.h>

static void global_registry_handler(void* data, struct wl_registry* registry, uint32_t id, const char* interface, uint32_t version)
{
	printf("Got a registry event for %s, id %d.\n", interface, id);
	if(strcmp(interface, "wl_compositor") == 0)
		objects.compositor = (struct wl_compositor*)wl_registry_bind(
			objects.registry,
			id,
			&wl_compositor_interface,
			1
		);
}

static void global_registry_remover(void* data, struct wl_registry* registry, uint32_t id)
{
	printf("Got a registry remove event for id %d.\n", id);
}

int main(int argc, char* argv[])
{
	objects.display = wl_display_connect(NULL);
	if(!objects.display)
		end(ERR_FAILED_TO_CONNECT_TO_WAYLAND_DISPLAY);

	objects.registry 						= wl_display_get_registry(objects.display);
	
	objects.registry_listener.global 		= global_registry_handler;
	objects.registry_listener.global_remove = global_registry_remover;

	wl_registry_add_listener(objects.registry, &objects.registry_listener, NULL);

	wl_display_dispatch(objects.display);
	wl_display_roundtrip(objects.display);

	if(objects.compositor == NULL)
		end(ERR_CANNOT_FIND_COMPOSITOR);

	end(0);
}

int end(int code)
{
	#define CodeExit(code, message)					\
		case code:									\
			std::cerr << message << std::endl;		\
			exit(code);								\
			break;

	if(code != ERR_FAILED_TO_CONNECT_TO_WAYLAND_DISPLAY)
	{
		wl_display_disconnect(objects.display);
		if(code != 0)
			printf("Disconnected from display due to error.\n");
		else
			printf("Disconnected from Wayland display.\n");
	}

	switch(code)
	{
		case 0:
			exit(0);
			break;

		CodeExit(
			ERR_FAILED_TO_CONNECT_TO_WAYLAND_DISPLAY,
			"Failed to connect to Wayland display."
		);

		CodeExit(
			ERR_CANNOT_FIND_COMPOSITOR,
			"Cannot find Wayland compositor."
		);

		default:
			std::cerr << "Unknown error, return code " << code << "." << std::endl;
			exit(code);
			break;
	}
}