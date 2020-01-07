#pragma once

#include "c_singleton.h"
#include "../security/fnv1a.h"
#include "../security/string_obfuscation.h"
#include "../sdk/c_color.h"
#include "base64.h"
#include <fstream>

using json = nlohmann::json;

#define make_key(var) std::to_string(fnv1a(var))

class c_config : public c_singleton<c_config>
{
public:
	struct config_conf
	{
		struct esp_conf
		{
			struct player
			{
				c_color color, impacts_color, weapon_color;
				bool box, ammo, weapon, info;
				int radar, bar, skeleton;
				int impacts;
			};

			player team, enemy;

			int nade_type;
			c_color nade_color;

			bool hitmarker;
			int hitsound;
			float hitsound_volume;
			bool wep_icons;
		};

		struct chams_conf
		{
			struct chams
			{
				int type;
				c_color color;
				bool xqz;
			};

			chams team, enemy, backtrack, local, arms, weapon;
			bool remove_sleeves;
		};

		struct legit_conf
		{
			bool assist;
			float fov, smooth, backtrack;
			bool only_backtrack;
		};

		struct rage_conf
		{
			struct weapon_conf
			{
				float hitchance, min_dmg, head_scale, body_scale;
			};

			bool enabled, experimental_aa, infinite_duck;
			int slow_walk;
//			bool Resolver[2] = { false, false };
			weapon_conf auto_snipe, scout, awp,	pistol, heavy, misc;
		};


		struct misc_conf
		{
			struct fakelag_conf
			{
				bool enabled;
				float fake_lag_standing, fake_lag_moving, fake_lag_air, fake_lag_slowwalk;
				bool fake_lag_on_peek_delay, disable_on_knife, disable_on_tazer, disable_on_grenade, fake_lag_automatic, disable_on_shooting, disable_on_revolver;
			};
			fakelag_conf fakelag_settings;
			int fake_duck;

			int radio_channel;
			float radio_volume;
			int radio_mute;

			float spike_ping;
			int ping_switch;

			float thirdperson_dist;
			int thirdperson_switch;

			int buy_bot;

			bool clan_tag;
			float aspect_ratio;

			bool engine_radar, no_smoke, no_flash, no_scope, no_fog, indicators, arrows;

			float fov, fov_view;
		};

		esp_conf esp;
		chams_conf chams;
		legit_conf legit;
		rage_conf rage;
		misc_conf misc;
	};

	c_config() = default;

	config_conf& get()
	{
		static config_conf config {
			// esp
			{
				// esp.team
				{
					c_color(120, 120, 255, 255),
					c_color(120, 120, 255, 255),
					c_color(120, 120, 255, 255),
					false,
					false,
					false,
					false,
					0,
					0,
					0
				},
				// esp.enemy
				{
					c_color(230, 70, 140, 255),
					c_color(230, 70, 140, 255),
					c_color(230, 70, 140, 255),
					false,
					false,
					false,
					false,
					0,
					0,
					0
				},
				0,
				c_color::primary(),
				false,
				0,
				100.f,
			},
			// chams
			{
				// chams.team
				{
					0,
					c_color(120, 120, 255, 255),
					false
				},
				// chams.enemy
				{
					0,
					c_color(230, 70, 140, 255),
					false
				},
				// chams.backtrack
				{
					0,
					c_color(70, 225, 230, 255),
					false
				},
				// chams.local
				{
					0,
					c_color::gradient2()
				},
				// chams.arms
				{
					0,
					c_color::primary()
				},
				// chams.weapons
				{
					0,
					c_color::accent()
				},
				false
			},
			// legit
			{
				false,
				0.f,
				0.f,
				0.f
			},
			// rage
			{
				false,	// Rage Enable
				false,	// Experimental AA	
				false,	// Infinite duck
				0,	
				// rage.auto_snipe
				{
					0.f,
					0.f,
					20.f,
					20.f
				},
				// rage.scout
				{
					0.f,
					0.f,
					20.f,
					20.f
				},
				// rage.awp
				{
					0.f,
					0.f,
					20.f,
					20.f
				},
				// rage.pistol
				{
					0.f,
					0.f,
					20.f,
					20.f
				},
				// rage.heavy
				{
					0.f,
					0.f,
					20.f,
					20.f
				},
				// rage.misc
				{
					0.f,
					0.f,
					20.f,
					20.f
				}
			},
			// misc
			{
				false,	// Fakelags | Enable
				2.f,	// Fakelags | Standing
				2.f,	// Fakelags | Moving
				0.f,	// Fakelags | Air
				0.f,	// Fakelags | Slowwalk
				false,	// Fakelags | On Peek Delay
				false,	// Fakelags | Disable on Knife
				false,	// Fakelags | Disable on Taser
				false,	// Fakelags | Disable on Grenade
				false,	// Fakelags | Automatic
				false,	// Fakelags | Disable on Shot
				false,	// Fakelags | Disable on Revolver

				false,	// Fakeduck

				0,		// Radio | Channel
				0.f,	// Radio | Volume
				0,		// Radio | Mute

				0.f,	// Ping | Spike
				0,		// Ping | Switch bind

				120.f,	// Third person | Distance
				0,		// Third person | Switch bind

				0,		// Buy Bot

				false,	// Clan Tag
				35.f,	// Aspect Ratio

				false,	// Engine Radar
				false,	// No Smoke
				false,	// No Flash
				false,	// No Scope
				false,	// No Fog
				false,	// Indicators
				false,	// AA Arrow

				50.f,	// World FOV
				50.f	// Viewmodel FOV
			}
		};

		return config;
	}

	static void load_from_file(const std::string& config_path);
	static void save_to_file(const std::string& config_path);
};

inline void to_json(nlohmann::json& j, const c_config::config_conf::esp_conf::player& value)
{
	j = json {
		{ _("color"), value.color },
		{ _("impacts_color"), value.impacts_color },
		{ _("box"), value.box },
		{ _("info"), value.info },
		{ _("weapon"), value.weapon },
		{ _("weapon_color"), value.weapon_color },
		{ _("impacts"), value.impacts },
		{ _("radar"), value.radar },
		{ _("bar"), value.bar },
		{ _("skeleton"), value.skeleton },
	};
}

inline void from_json(const nlohmann::json& j, c_config::config_conf::esp_conf::player& value)
{
	value.color = j.value(_("color"), c_color(120, 120, 255, 255));
	value.impacts_color = j.value(_("impacts_color"), c_color(120, 120, 255, 255));
	value.weapon_color = j.value(_("weapon_color"), c_color(120, 120, 255, 255));
	value.box = j.value(_("box"), false);
	value.info = j.value(_("info"), false);
	value.weapon = j.value(_("weapon"), false);
	value.impacts = j.value(_("impacts"), 0);
	value.radar = j.value(_("radar"), 0);
	value.bar = j.value(_("bar"), 0);
	value.skeleton = j.value(_("skeleton"), 0);
}

inline void to_json(nlohmann::json& j, const c_config::config_conf::esp_conf& value)
{
	j = json {
		{ _("team"), value.team },
		{ _("enemy"), value.enemy },
		{ _("nade_type"), value.nade_type },
		{ _("nade_color"), value.nade_color },
		{ _("hitmarker"), value.hitmarker },
		{ _("hitsound"), value.hitsound },
		{ _("hitsound_volume"), value.hitsound_volume },
	};
}

inline void from_json(const nlohmann::json& j, c_config::config_conf::esp_conf& value)
{
	value.team = j.value(_("team"), c_config::config_conf::esp_conf::player{});
	value.enemy = j.value(_("enemy"), c_config::config_conf::esp_conf::player{});
	value.nade_type = j.value(_("nade_type"), 0);
	value.nade_color = j.value(_("nade_color"), c_color::primary());
	value.hitmarker = j.value(_("hitmarker"), false);
	value.hitsound = j.value(_("hitsound"), 0);
	value.hitsound_volume = j.value(_("hitsound_volume"), 100.f);
}

inline void to_json(nlohmann::json& j, const c_config::config_conf::chams_conf::chams& value)
{
	j = json {
		{ _("type"), value.type },
		{ _("color"), value.color },
		{ _("xqz"), value.xqz }
	};
}

inline void from_json(const nlohmann::json& j, c_config::config_conf::chams_conf::chams& value)
{
	value.type = j.value(_("type"), 0);
	value.color = j.value(_("color"), c_color(120, 120, 255, 255));
	value.xqz = j.value(_("xqz"), false);
}

inline void to_json(nlohmann::json& j, const c_config::config_conf::chams_conf& value)
{
	j = json {
		{ _("team"), value.team },
		{ _("enemy"), value.enemy },
		{ _("backtrack"), value.backtrack },
		{ _("local"), value.local },
		{ _("arms"), value.arms },
		{ _("weapon"), value.weapon },
		{ _("remove_sleeves"), value.remove_sleeves }
	};
}

inline void from_json(const nlohmann::json& j, c_config::config_conf::chams_conf& value)
{
	value.team = j.value(_("team"), c_config::config_conf::chams_conf::chams{});
	value.enemy = j.value(_("enemy"), c_config::config_conf::chams_conf::chams{});
	value.backtrack = j.value(_("backtrack"), c_config::config_conf::chams_conf::chams{});
	value.local = j.value(_("local"), c_config::config_conf::chams_conf::chams{});
	value.arms = j.value(_("arms"), c_config::config_conf::chams_conf::chams{});
	value.weapon = j.value(_("weapon"), c_config::config_conf::chams_conf::chams{});
	value.remove_sleeves = j.value(_("remove_sleeves"), false);
}

inline void to_json(nlohmann::json& j, const c_config::config_conf::legit_conf& value)
{
	j = json {
		{ _("assist"), value.assist },
		{ _("fov"), value.fov },
		{ _("smooth"), value.smooth },
		{ _("backtrack"), value.backtrack }
	};
}

inline void from_json(const nlohmann::json& j, c_config::config_conf::legit_conf& value)
{
	value.assist = j.value(_("assist"), false);
	value.fov = j.value(_("fov"), 0.f);
	value.smooth = j.value(_("smooth"), 0.f);
	value.backtrack = j.value(_("backtrack"), 0.f);
}

inline void to_json(nlohmann::json& j, const c_config::config_conf::rage_conf::weapon_conf& value)
{
	j = json {
		{ _("hitchance"), value.hitchance },
		{ _("min_dmg"), value.min_dmg },
		{ _("head_scale"), value.head_scale },
		{ _("body_scale"), value.body_scale }
	};
}

inline void from_json(const nlohmann::json& j, c_config::config_conf::rage_conf::weapon_conf& value)
{
	value.hitchance = j.value(_("hitchance"), 0.f);
	value.min_dmg = j.value(_("min_dmg"), 0.f);
	value.head_scale = j.value(_("head_scale"), 20.f);
	value.body_scale = j.value(_("body_scale"), 20.f);
}

inline void to_json(nlohmann::json& j, const c_config::config_conf::rage_conf& value)
{
	j = json{
		{ _("enabled"), value.enabled },
		{ _("experimental_aa"), value.experimental_aa },
		{ _("infinite_duck"), value.infinite_duck },
		{ _("slow_walk"), value.slow_walk },
		{ _("auto_snipe"), value.auto_snipe },
		{ _("scout"), value.scout },
		{ _("awp"), value.awp },
		{ _("pistol"), value.pistol },
		{ _("heavy"), value.heavy },
		{ _("misc"), value.misc },
	};
}

inline void from_json(const nlohmann::json& j, c_config::config_conf::rage_conf& value)
{
	value.enabled = j.value(_("enabled"), false);
	value.experimental_aa = j.value(_("experimental_aa"), false);
	value.infinite_duck = j.value(_("infinite_duck"), false);
	value.slow_walk = j.value(_("slow_walk"), 0);
	value.auto_snipe = j.value(_("auto_snipe"), c_config::config_conf::rage_conf::weapon_conf{});
	value.scout = j.value(_("scout"), c_config::config_conf::rage_conf::weapon_conf{});
	value.awp = j.value(_("awp"), c_config::config_conf::rage_conf::weapon_conf{});
	value.pistol = j.value(_("pistol"), c_config::config_conf::rage_conf::weapon_conf{});
	value.heavy = j.value(_("heavy"), c_config::config_conf::rage_conf::weapon_conf{});
	value.misc = j.value(_("misc"), c_config::config_conf::rage_conf::weapon_conf{});
}

inline void to_json(nlohmann::json& j, const c_config::config_conf::misc_conf::fakelag_conf& value)
{
	j = json{
		{ _("enabled"), value.enabled },
		{ _("fake_lag_standing"), value.fake_lag_standing },
		{ _("fake_lag_moving"), value.fake_lag_moving },
		{ _("fake_lag_air"), value.fake_lag_air },
		{ _("fake_lag_slowwalk"), value.fake_lag_slowwalk },
		{ _("fake_lag_on_peek_delay"), value.fake_lag_on_peek_delay },
		{ _("disable_on_knife"), value.disable_on_knife },
		{ _("disable_on_tazer"), value.disable_on_tazer },
		{ _("disable_on_grenade"), value.disable_on_grenade },
		{ _("fake_lag_automatic"), value.fake_lag_automatic },
		{ _("disable_on_shooting"), value.disable_on_shooting },
		{ _("disable_on_revolver"), value.disable_on_revolver }
	};
}

inline void from_json(const nlohmann::json& j, c_config::config_conf::misc_conf::fakelag_conf& value)
{
	value.enabled = j.value(_("enabled"), false);
	value.fake_lag_standing = j.value(_("fake_lag_standing"), 0);
	value.fake_lag_moving = j.value(_("fake_lag_moving"), 0);
	value.fake_lag_air = j.value(_("fake_lag_air"), 0);
	value.fake_lag_slowwalk = j.value(_("fake_lag_slowwalk"), 0);
	value.fake_lag_on_peek_delay = j.value(_("fake_lag_on_peek_delay"), false);
	value.disable_on_knife = j.value(_("disable_on_knife"), false);
	value.disable_on_tazer = j.value(_("disable_on_tazer"), false);
	value.disable_on_grenade = j.value(_("disable_on_grenade"), false);
	value.fake_lag_automatic = j.value(_("fake_lag_automatic"), false);
	value.disable_on_shooting = j.value(_("disable_on_shooting"), false);
	value.disable_on_revolver = j.value(_("disable_on_revolver"), false);
}

inline void to_json(nlohmann::json& j, const c_config::config_conf::misc_conf& value)
{
	j = json {
		{ _("fakelag_settings"), value.fakelag_settings },
		{ _("fake_duck"), value.fake_duck },

		{ _("radio_channel"), value.radio_channel },
		{ _("radio_volume"), value.radio_volume },
		{ _("radio_mute"), value.radio_mute },

		{ _("aspect_ratio"), value.aspect_ratio },

		{ _("spike_ping"), value.spike_ping },
		{ _("ping_switch"), value.ping_switch },

		{ _("thirdperson_dist"), value.thirdperson_dist },
		{ _("thirdperson_switch"), value.thirdperson_switch },

		{ _("buy_bot"), value.buy_bot },

		{ _("clan_tag"), value.clan_tag },

		{ _("engine_radar"), value.engine_radar },
		{ _("no_smoke"), value.no_smoke },
		{ _("no_flash"), value.no_flash },
		{ _("no_scope"), value.no_scope },
		{ _("no_fog"), value.no_fog},
		{ _("indicators"), value.indicators },
		{ _("arrows"), value.arrows },

		{ _("fov"), value.fov },
		{ _("fov_view"), value.fov_view }
	};
}

inline void from_json(const nlohmann::json& j, c_config::config_conf::misc_conf& value)
{
	value.fakelag_settings = j.value(_("fakelag_settings"), c_config::config_conf::misc_conf::fakelag_conf{});
	value.fake_duck = j.value(_("fake_duck"), 0);

	value.radio_channel = j.value(_("radio_channel"), 0);
	value.radio_volume = j.value(_("radio_volume"), 100.f);
	value.radio_mute = j.value(_("radio_mute"), 0);

	value.aspect_ratio = j.value(_("aspect_ratio"), 35.f);

	value.spike_ping = j.value(_("spike_ping"), 0.f);
	value.ping_switch = j.value(_("ping_switch"), 0);

	value.thirdperson_dist = j.value(_("thirdperson_dist"), 0.f);
	value.thirdperson_switch = j.value(_("thirdperson_switch"), 0);

	value.buy_bot = j.value(_("buy_bot"), 0);

	value.clan_tag = j.value(_("clan_tag"), false);

	value.engine_radar = j.value(_("engine_radar"), false);
	value.no_smoke = j.value(_("no_smoke"), false);
	value.no_flash = j.value(_("no_flash"), false);
	value.no_scope = j.value(_("no_scope"), false);
	value.no_fog = j.value(_("no_fog"), false);
	value.indicators = j.value(_("indicators"), false);
	value.arrows = j.value(_("arrows"), false);

	value.fov = j.value(_("fov"), 50.f);
	value.fov_view = j.value(_("fov_view"), 50.f);
}

inline void to_json(nlohmann::json& j, const c_config::config_conf& value)
{
	j = json {
		{ _("esp"), value.esp },
		{ _("chams"), value.chams },
		{ _("legit"), value.legit },
		{ _("rage"), value.rage },
		{ _("misc"), value.misc }
	};
}

inline void from_json(const nlohmann::json& j, c_config::config_conf& value)
{
	value.esp = j.value(_("esp"), c_config::config_conf::esp_conf{});
	value.chams = j.value(_("chams"), c_config::config_conf::chams_conf{});
	value.legit = j.value(_("legit"), c_config::config_conf::legit_conf{});
	value.rage = j.value(_("rage"), c_config::config_conf::rage_conf{});
	value.misc = j.value(_("misc"), c_config::config_conf::misc_conf{});
}

inline void c_config::load_from_file(const std::string& config_path)
{
	std::ifstream file(config_path);
	std::stringstream rage;
	rage << file.rdbuf();

	if (rage.str().empty())
		return;

	auto cfg = base64::decode(rage.str());
	from_json(json::parse(cfg), instance()->get());
}

inline void c_config::save_to_file(const std::string& config_path)
{
	json exp;
	to_json(exp, instance()->get());
	const auto str = base64::encode(exp.dump());

	std::ofstream file(config_path);
	file << str;
}

#define config c_config::instance()->get()
