#pragma once

#include <wayland-client.h>

struct wl_objects
{
	struct wl_display*			display;
	struct wl_registry*			registry;
	struct wl_compositor*		compositor;
	struct wl_registry_listener	registry_listener;
};

struct wl_objects objects;

int end(int code);

#define ERR_FAILED_TO_CONNECT_TO_WAYLAND_DISPLAY	1
#define ERR_CANNOT_FIND_COMPOSITOR					2