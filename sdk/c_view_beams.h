#pragma once

#include "macros.h"

enum
{
	TE_BEAMPOINTS = 0x00,		// beam effect between two points
	TE_SPRITE = 0x01,	// additive sprite, plays 1 cycle
	TE_BEAMDISK = 0x02,	// disk that expands to max radius over lifetime
	TE_BEAMCYLINDER = 0x03,		// cylinder that expands to max radius over lifetime
	TE_BEAMFOLLOW = 0x04,		// create a line of decaying beam segments until entity stops moving
	TE_BEAMRING = 0x05,		// connect a beam ring to two entities
	TE_BEAMSPLINE = 0x06,
	TE_BEAMRINGPOINT = 0x07,
	TE_BEAMLASER = 0x08,		// Fades according to viewpoint
	TE_BEAMTESLA = 0x09,
};
enum
{
	FBEAM_STARTENTITY = 0x00000001,
	FBEAM_ENDENTITY = 0x00000002,
	FBEAM_FADEIN = 0x00000004,
	FBEAM_FADEOUT = 0x00000008,
	FBEAM_SINENOISE = 0x00000010,
	FBEAM_SOLID = 0x00000020,
	FBEAM_SHADEIN = 0x00000040,
	FBEAM_SHADEOUT = 0x00000080,
	FBEAM_ONLYNOISEONCE = 0x00000100,		// Only calculate our noise once
	FBEAM_NOTILE = 0x00000200,
	FBEAM_USE_HITBOXES = 0x00000400,		// Attachment indices represent hitbox indices instead when this is set.
	FBEAM_STARTVISIBLE = 0x00000800,		// Has this client actually seen this beam's start entity yet?
	FBEAM_ENDVISIBLE = 0x00001000,		// Has this client actually seen this beam's end entity yet?
	FBEAM_ISACTIVE = 0x00002000,
	FBEAM_FOREVER = 0x00004000,
	FBEAM_HALOBEAM = 0x00008000,		// When drawing a beam with a halo, don't ignore the segments and endwidth
	FBEAM_REVERSED = 0x00010000,
	NUM_BEAM_FLAGS = 17	// KEEP THIS UPDATED!
};

struct beam_info
{
	int32_t	type;

	c_base_entity* start_entity;
	int32_t	start_attachment;
	c_base_entity* end_entity;
	int32_t	end_attachment;

	c_vector3d start;
	c_vector3d end;

	int32_t	model_index;
	const char* model_name;

	int32_t	halo_index;
	const char* halo_name;
	float halo_scale;

	float life;
	float width;
	float end_width;
	float fade_length;
	float amplitude;

	float brightness;
	float speed;

	int32_t	start_frame;
	float frame_rate;

	float red;
	float green;
	float blue;

	bool renderable;
	int32_t	segments;
	int32_t	flags;

	c_vector3d center;
	float start_radius;
	float end_radius;

	beam_info ()
	{
		type = 0;
		segments = -1;
		model_name = nullptr;
		halo_name = nullptr;
		model_index = -1;
		halo_index = -1;
		renderable = true;
		flags = 0;
	}
};

class c_view_render_beams
{
public:
	inline static c_view_render_beams* get()
	{
		static auto view_render_beams = *reinterpret_cast<c_view_render_beams**>(
			sig("client_panorama.dll", "8D 43 FC B9 ? ? ? ? 50 A1") + 0x4);

		return view_render_beams;
	}

	vfunc(4, draw_beam(void* beam), void(__thiscall*)(c_view_render_beams*, void*))(beam)
	vfunc(12, create_beam_points(beam_info& info), void*(__thiscall*)(c_view_render_beams*, beam_info&))(info)
};

#define view_render_beams c_view_render_beams::get()
