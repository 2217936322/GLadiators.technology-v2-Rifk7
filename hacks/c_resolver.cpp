#include "c_resolver.h"
#include "../utils/math.h"
#include "c_aimhelper.h"
#include "c_trace_system.h"
#include "../sdk/c_client_entity_list.h"
#include <random>
#include "c_esp.h"
#include "../sdk/c_global_vars_base.cpp"
#include "../utils/math.h"
#include "../utils/c_singleton.h"
#include "../utils/c_config.h"
#include "../sdk/c_net_channel.h"

static std::random_device rd;
static std::mt19937 rng(rd());


// Stickrpg v2 resolver [A good resolver, but not completely redone for the Rifk SDK.]
//void Resolver::AnimationFix(c_cs_player* pEnt, c_cs_player* pLocalEnt/*, c_animation_system::animation* anim*/)
//{
/*	const auto info = animation_system->get_animation_info(anim->player);

	if (!info || !anim->has_anim_state || anim->player->get_info().fakeplayer)
		return; *//*

	if (g::CheatType != 1)
		return;

	// i rly am just to lazy pls dont judge
	static float ShotTime[65];

	static float oldSimtime[65];
	static float storedSimtime[65];

	static c_vector3d oldEyeAngles[65];
	static float oldGoalfeetYaw[65];
	static c_vector3d oldOrigin[65];

	float* PosParams = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(pEnt) + 0x2774);
	bool shot = false;

	auto* AnimState = pEnt->get_anim_state();
	if (!AnimState || !pEnt->anim_overlays() || !PosParams)
		return;

	if (*reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(AnimState) + 0x164) < 0) // sorry had to anti pasta this basically the key to nospread
		*reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(AnimState) + 0x110) = 0.f;

	bool update = false;

	if (storedSimtime[pEnt->index()] != pEnt->get_simtime())
	{
		pEnt->get_client_side_animation() = true;
		pEnt->update_clientside_anim();
		pEnt->clientside_anim() = false;

		update = true;
	}

	oldGoalfeetYaw[pEnt->index()] = AnimState->goal_feet_yaw;

	if (pEnt->get_current_weapon_handle() && !pEnt->IsKnifeorNade())
	{
		if (ShotTime[pEnt->index()] != pEnt->get_last_shot_time())
		{
			shot = true;
			ShotTime[pEnt->index()] = pEnt->get_last_shot_time();
		}
		else
			shot = false;
	}
	else
	{
		shot = false;
		ShotTime[pEnt->index()] = 0.f;
	}

	if (pLocalEnt && pLocalEnt->is_alive())
	{
		float angToLocal = g_Math.NormalizeYaw(g_Math.CalcAngle(pLocalEnt->get_origin(), pEnt->get_origin()).y);

		float Back = g_Math.NormalizeYaw(angToLocal);
		float DesyncFix = 0;

		float Resim = g_Math.NormalizeYaw((ticks_to_time(16) / (pEnt->get_simtime() - oldSimtime[pEnt->index()])) * g_Math.NormalizeYaw(oldEyeAngles[pEnt->index()].y - pEnt->get_eye_angles().y));

		if (Resim > 60.f)
			Resim = 60.f;
		if (Resim < -60.f)
			Resim = -60.f;

		if (config.rage.Resolver[0] && !shot && !isnan(angToLocal) && !isinf(angToLocal) && pEnt != pLocalEnt && pEnt->get_team() != pLocalEnt->get_team())
		{
			float AntiSide = 0.f;

			if (g::MissedShots[pEnt->index()] % 2)	
			{
				if (g_Math.NormalizeYaw(pEnt->get_eye_angles().y - Back) > 0.f)
					AntiSide = -90.f;
				else if (g_Math.NormalizeYaw(pEnt->get_eye_angles().y - Back) < 0.f)
					AntiSide = 90.f;
			}
			else
			{
				if (g_Math.NormalizeYaw(pEnt->get_eye_angles().y - g_Math.NormalizeYaw(Back + 90)) > 0.f)
					AntiSide = 180.f;
				else if (g_Math.NormalizeYaw(pEnt->get_eye_angles().y - g_Math.NormalizeYaw(Back + 90)) < 0.f)
					AntiSide = 0.f;
			}

			float Brute = g_Math.NormalizeYaw(Back + AntiSide);
			float Delta = g_Math.NormalizeYaw(g_Math.NormalizeYaw(Brute - pEnt->get_eye_angles().y) + Resim);

			if (Delta > 60.f) // who needs clamps
				Delta = 60.f;
			if (Delta < -60.f)
				Delta = -60.f;

			Resim += Delta;
			DesyncFix += Delta;

			if (Resim > 60.f)
				Resim = 60.f;
			if (Resim < -60.f)
				Resim = -60.f;
		}

		float Equalized;

		//	if (fabs(g_Math.NormalizeYaw(oldEyeAngles[pEnt->index()].y - pEnt->get_eye_angles().y)) < 60.f) // yea basically im retarded
		Equalized = g_Math.NormalizeYaw(pEnt->get_eye_angles().y + Resim);
		//	else
		//		Equalized = g_Math.NormalizeYaw(pEnt->get_eye_angles().y - Resim);

		if (config.rage.Resolver[0] && !shot && pEnt != pLocalEnt && pEnt->get_team() != pLocalEnt->get_team() && (pEnt->get_flags() & FL_ONGROUND))
			AnimState->goal_feet_yaw = Equalized;
	}

	if (config.rage.Resolver[1] && !shot && pEnt != pLocalEnt && pEnt->get_team() != pLocalEnt->get_team()) // 1337 pitch resolver
	{
		switch (g::MissedShots[pEnt->index()] % 3) // i skip case 0 on purpose noob
		{
		case 1:PosParams[12] = 89.f; break;
		case 2:PosParams[12] = -89.f; break;
		}
	}

	if (shot && pEnt != pLocalEnt && pEnt->get_team() != pLocalEnt->get_team() && PosParams[12] <= -80) // ez shot pitch fix LMAO
		PosParams[12] = 89.f;

	if (update)
	{
		oldEyeAngles[pEnt->index()] = pEnt->get_eye_angles();
		oldSimtime[pEnt->index()] = storedSimtime[pEnt->index()];
		storedSimtime[pEnt->index()] = pEnt->get_simtime();
		oldOrigin[pEnt->index()] = pEnt->get_origin();
	}

	pEnt->set_abs_angles(c_vector3d(0, oldGoalfeetYaw[pEnt->index()], 0));
}

void Resolver::HandleHits(c_cs_player* pEnt, c_cs_player* pLocalEnt)
{
//	auto NetChannel = g_pEngine->get_net_channel();

//	if (!NetChannel)
	if (!net_channel)
		return;

	static float predTime[65];
	static bool init[65];

	static float StoredSimtime[65];
	static float SimDelta[65];

	if (StoredSimtime[pEnt->index()] != pEnt->get_simtime())
	{
		SimDelta[pEnt->index()] = fabs(pEnt->get_simtime() - StoredSimtime[pEnt->index()]);
		StoredSimtime[pEnt->index()] = pEnt->get_simtime();
	}

	if (g::Shot[pEnt->index()])
	{
		if (init[pEnt->index()])
		{
			Resolver::get().pitchHit[pEnt->index()] = pEnt->get_eye_angles().x;
			predTime[pEnt->index()] = global_vars_base->curtime + net_channel->get_latency(flow_incoming) + pLocalEnt->FireRate();  // maybe????
			init[pEnt->index()] = false;
		}

		if (global_vars_base->curtime > predTime[pEnt->index()] && !g::Hit[pEnt->index()])
		{
			g::MissedShots[pEnt->index()] += 1;
			g::Shot[pEnt->index()] = false;
		}
		else if (global_vars_base->curtime <= predTime[pEnt->index()] && g::Hit[pEnt->index()])
			g::Shot[pEnt->index()] = false;

	}
	else
		init[pEnt->index()] = true;

	g::Hit[pEnt->index()] = false;
}

void Resolver::OnCreateMove() // kinda dont need this anymore
{
	if (g::CheatType != 1)
		return;

	if (!config.rage.Resolver[0])
		return;

	if (!g::pLocalEntity->is_alive())
		return;

	if (!g::pLocalEntity->get_current_weapon_handle() || g::pLocalEntity->IsKnifeorNade())
		return;


	for (int i = 1; i <= engine_client()->get_max_clients(); ++i)
	{
		c_base_entity* pPlayerEntity;// = client_entity_list()->get_client_entity(i);
		c_client_entity* pPlayerEntity = client_entity_list()->get_client_entity(i);

		if (!pPlayerEntity
			|| !pPlayerEntity->is_alive()
			|| pPlayerEntity->is_dormant()
			|| pPlayerEntity == g::pLocalEntity
			|| pPlayerEntity->get_team() == g::pLocalEntity->get_team())
		{
			UseFreestandAngle[i] = false;
			continue;
		}

		if (abs(pPlayerEntity->get_velocity().length2d()) > 29.f)
			UseFreestandAngle[pPlayerEntity->index()] = false;

		if (abs(pPlayerEntity->get_velocity().length2d()) <= 29.f && !UseFreestandAngle[pPlayerEntity->index()])
		{
			bool Autowalled = false, HitSide1 = false, HitSide2 = false;

			float angToLocal = g_Math.CalcAngle(g::pLocalEntity->get_origin(), pPlayerEntity->get_origin()).y;
			c_vector3d ViewPoint = g::pLocalEntity->get_origin() + c_vector3d(0, 0, 90);

			c_vector2d Side1 = { (45 * sin(g_Math.GRD_TO_BOG(angToLocal))),(45 * cos(g_Math.GRD_TO_BOG(angToLocal))) };
			c_vector2d Side2 = { (45 * sin(g_Math.GRD_TO_BOG(angToLocal + 180))) ,(45 * cos(g_Math.GRD_TO_BOG(angToLocal + 180))) };

			c_vector2d Side3 = { (50 * sin(g_Math.GRD_TO_BOG(angToLocal))),(50 * cos(g_Math.GRD_TO_BOG(angToLocal))) };
			c_vector2d Side4 = { (50 * sin(g_Math.GRD_TO_BOG(angToLocal + 180))) ,(50 * cos(g_Math.GRD_TO_BOG(angToLocal + 180))) };

			c_vector2d Origin = pPlayerEntity->get_origin();

			c_vector2d OriginLeftRight[] = { c_vector2d(Side1.x, Side1.y), c_vector2d(Side2.x, Side2.y) };

			c_vector2d OriginLeftRightLocal[] = { c_vector2d(Side3.x, Side3.y), c_vector2d(Side4.x, Side4.y) };

			for (int side = 0; side < 2; side++)
			{
				c_vector3d OriginAutowall = { Origin.x + OriginLeftRight[side].x,  Origin.y - OriginLeftRight[side].y , Origin.z + 90 };
				c_vector3d OriginAutowall2 = { ViewPoint.x + OriginLeftRightLocal[side].x,  ViewPoint.y - OriginLeftRightLocal[side].y , ViewPoint.z };

				if (c_aimhelper::get().can_hit(OriginAutowall, ViewPoint, pPlayerEntity))
				{
					if (side == 0)
					{
						HitSide1 = true;
						FreestandAngle[pPlayerEntity->index()] = 90;
					}
					else if (side == 1)
					{
						HitSide2 = true;
						FreestandAngle[pPlayerEntity->index()] = -90;
					}

					Autowalled = true;
				}
				else
				{
					for (int side222 = 0; side222 < 2; side222++)
					{
						c_vector3d OriginAutowall = { Origin.x + OriginLeftRight[side222].x,  Origin.y - OriginLeftRight[side222].y , Origin.z + 90 };

						if (c_aimhelper::get().can_hit(OriginAutowall, OriginAutowall2, pPlayerEntity))
						{
							if (side222 == 0)
							{
								HitSide1 = true;
								FreestandAngle[pPlayerEntity->index()] = 90;
							}
							else if (side222 == 1)	
							{
								HitSide2 = true;
								FreestandAngle[pPlayerEntity->index()] = -90;
							}

							Autowalled = true;
						}
					}
				}
			}

			if (Autowalled)
			{
				if (HitSide1 && HitSide2)
					UseFreestandAngle[pPlayerEntity->index()] = false;
				else
					UseFreestandAngle[pPlayerEntity->index()] = true;
			}
		}
	}
}*/


////


// Rikf7 Resolver [with anti-paste]
void c_resolver::resolve(c_animation_system::animation* anim)
{
	const auto info = animation_system->get_animation_info(anim->player);

	if (!info || !anim->has_anim_state || anim->player->get_info().fakeplayer)
		return;

	if (info->brute_state == resolver_start)
//		info->brute_yaw = std::uniform_int_distribution<int>(0, 1)(rng) ? -0.f : 0.f;
		info->brute_yaw = -info->brute_yaw;


	anim->anim_state.goal_feet_yaw = math::normalize_yaw(anim->anim_state.goal_feet_yaw + info->brute_yaw);
}

void c_resolver::resolve_shot(resolver::shot& shot)
{
	if (!config.rage.enabled || shot.manual)
		return;

	const auto player = reinterpret_cast<c_cs_player*>(client_entity_list()->get_client_entity(shot.record.index));

	if (player != shot.record.player)
		return;

	const auto hdr = model_info_client()->get_studio_model(shot.record.player->get_model());

	if (!hdr)
		return;

	const auto info = animation_system->get_animation_info(player);

	if (!info)
		return;

	const auto angle = math::calc_angle(shot.start, shot.server_info.impacts.back());
	c_vector3d forward;
	math::angle_vectors(angle, forward);
	const auto end = shot.server_info.impacts.back() + forward * 2000.f;
	const auto spread_miss = !c_aimhelper::can_hit_hitbox(shot.start, end, &shot.record, hdr, shot.hitbox);

	if (shot.server_info.damage > 0)
	{
		static const auto hit_msg = __("Hit %s in %s for %d damage.");
		_rt(hit, hit_msg);
		char msg[255];

		switch (shot.server_info.hitgroup)
		{
		case hitgroup_head:
			sprintf_s(msg, hit, player->get_info().name, _("head"), shot.server_info.damage);
			break;
		case hitgroup_chest:
			sprintf_s(msg, hit, player->get_info().name, _("chest"), shot.server_info.damage);
			break;
		case hitgroup_stomach:
			sprintf_s(msg, hit, player->get_info().name, _("stomach"), shot.server_info.damage);
			break;
		case hitgroup_leftarm:
			sprintf_s(msg, hit, player->get_info().name, _("left arm"), shot.server_info.damage);
			break;
		case hitgroup_rightarm:
			sprintf_s(msg, hit, player->get_info().name, _("left arm"), shot.server_info.damage);
			break;
		case hitgroup_leftleg:
			sprintf_s(msg, hit, player->get_info().name, _("left leg"), shot.server_info.damage);
			break;
		case hitgroup_rightleg:
			sprintf_s(msg, hit, player->get_info().name, _("right leg"), shot.server_info.damage);
			break;
		default:
			sprintf_s(msg, hit, player->get_info().name, _("body"), shot.server_info.damage);
			break;
		}

		logging->info(msg);
	}
	else if (spread_miss)
	{
		logging->info(_("Missed shot due to spread."));
		++info->missed_due_to_spread;
	}
	//else if (shot.server_info.damage > 100)
	//{
	//	static const auto hit_msg = __("Killed %s in %s.");
	//	_rt(hit, hit_msg);
	//	char msg[255];

	//	switch (shot.server_info.hitgroup)
	//	{
	//	case hitgroup_head:
	//		sprintf_s(msg, hit, player->get_info().name, _("head"));
	//		break;
	//	case hitgroup_chest:
	//		sprintf_s(msg, hit, player->get_info().name, _("chest"));
	//		break;
	//	case hitgroup_stomach:
	//		sprintf_s(msg, hit, player->get_info().name, _("stomach"));
	//		break;
	//	case hitgroup_leftarm:
	//		sprintf_s(msg, hit, player->get_info().name, _("left arm"));
	//		break;
	//	case hitgroup_rightarm:
	//		sprintf_s(msg, hit, player->get_info().name, _("left arm"));
	//		break;
	//	case hitgroup_leftleg:
	//		sprintf_s(msg, hit, player->get_info().name, _("left leg"));
	//		break;
	//	case hitgroup_rightleg:
	//		sprintf_s(msg, hit, player->get_info().name, _("right leg"));
	//		break;
	//	default:
	//		sprintf_s(msg, hit, player->get_info().name, _("body"));
	//		break;
	//	}

	//	logging->info(msg);
	//}

	if (!shot.record.player->is_alive() || shot.record.player->get_info().fakeplayer
		|| !shot.record.has_anim_state || !shot.record.player->get_anim_state() || !info)
		return;

	// note old brute_yaw.
	const auto old_brute_yaw = info->brute_yaw;

	// check deviation from server.
	auto backup = c_animation_system::animation(shot.record.player);
	shot.record.apply(player);
	const auto trace = trace_system->wall_penetration(shot.start, end, &shot.record);
	auto does_match = (trace.has_value() && trace.value().hitgroup == shot.server_info.hitgroup)
		|| (!trace.has_value() && spread_miss);

	// start brute.
	if (!does_match)
	{
		switch (info->brute_state)
		{
		case resolver_start:
			info->brute_state = resolver_brute1;
			info->brute_yaw = std::uniform_int_distribution<int>(0, 1)(rng) ? -60.f : 60.f;
			logging->debug("BRUTE: NONE -> -60/+60");
			break;
		case resolver_brute1:
			info->brute_state = resolver_brute2;
			info->brute_yaw = std::uniform_int_distribution<int>(0, 1)(rng) ? -90.f : 90.f;
			logging->debug("BRUTE: -60/+60 -> -90/+90");
			break;
		case resolver_brute2:
			info->brute_state = resolver_brute3;
			info->brute_yaw = std::uniform_int_distribution<int>(0, 1)(rng) ? -120.f : 120.f;
			logging->debug("BRUTE: -120/+120 -> -90/+90");
			break;
		case resolver_brute3:
			info->brute_state = resolver_brute4;
			info->brute_yaw = std::uniform_int_distribution<int>(0, 1)(rng) ? -60.f : 60.f;
			logging->debug("BRUTE: -90/+90 -> -60/+60");
			break;
		case resolver_brute4:
			info->brute_state = resolver_brute5;
			info->brute_yaw = std::uniform_int_distribution<int>(0, 1)(rng) ? -45.f : 45.f;
			logging->debug("BRUTE: -60/+60 -> -45/+45");
			break;
		case resolver_brute5:
			info->brute_state = resolver_brute6;
			info->brute_yaw = std::uniform_int_distribution<int>(0, 1)(rng) ? -30.f : 30.f;
			logging->debug("BRUTE: -45/+45 -> -30/+30");
			break;
		default:
		case resolver_brute6:
			info->brute_yaw = std::uniform_int_distribution<int>(0, 1)(rng) ? -75.f : 75.f;
			logging->debug("BRUTE: -30/+30 -> -75/+75");
			break;
		}

	// rifk7 brute
	//	switch (info->brute_state)
	//	{
	//	case resolver_start:
	//		info->brute_state = resolver_inverse;
	//		info->brute_yaw = -info->brute_yaw;
	//		logging->debug("BRUTE: START -> INVERSE");
	//		break;
	//	case resolver_inverse:
	//		info->brute_state = resolver_no_desync;
	//		logging->debug("BRUTE: INVERSE -> NONE");
	//		info->brute_yaw = 0.f;
	//		break;
	//	case resolver_no_desync:
	//		info->brute_state = resolver_jitter;
	//		info->brute_yaw = std::uniform_int_distribution<int>(0, 1)(rng) ? -120.f : 120.f;
	//		logging->debug("BRUTE: NONE -> JITTER");
	//		break;
	//	default:
	//	case resolver_jitter:
	//		info->brute_yaw = -info->brute_yaw;
	//		logging->debug("BRUTE: JITTER -> JITTER");
	//		break;
	//	}
	// rifk7 brute

	}

	// apply changes.
	if (!info->frames.empty())
	{
		c_animation_system::animation* previous = nullptr;

		// jump back to the beginning.
		*player->get_anim_state() = info->frames.back().anim_state;

		for (auto it = info->frames.rbegin(); it != info->frames.rend(); ++it)
		{
			auto& frame = *it;
			const auto frame_player = reinterpret_cast<c_cs_player*>(
				client_entity_list()->get_client_entity(frame.index));

			if (frame_player == frame.player
				&& frame.player == player)
			{
				// re-run complete animation code and repredict all animations in between!
				frame.anim_state = *player->get_anim_state();
				frame.apply(player);
				player->get_flags() = frame.flags;
				*player->get_animation_layers() = frame.layers;
				player->get_simtime() = frame.sim_time;

				info->update_animations(&frame, previous);
				frame.abs_ang.y = player->get_anim_state()->goal_feet_yaw;
				frame.flags = player->get_flags();
				*player->get_animation_layers() = frame.layers;
				frame.build_server_bones(player);
				previous = &frame;
			}
		}
	}
}

void c_resolver::register_shot(resolver::shot&& s)
{
	shots.emplace_front(std::move(s));
}

void c_resolver::on_player_hurt(c_game_event* event)
{
	const auto attacker = event->get_int(_("attacker"));
	const auto attacker_index = engine_client()->get_player_for_user_id(attacker);

	if (attacker_index != engine_client()->get_local_player())
		return;

	if (shots.empty())
		return;

	resolver::shot* last_confirmed = nullptr;

	for (auto it = shots.rbegin(); it != shots.rend(); it = next(it))
	{
		if (it->confirmed && !it->skip)
		{
			last_confirmed = &*it;
			break;
		}
	}

	if (!last_confirmed)
		return;

	const auto userid = event->get_int(_("userid"));
	const auto index = engine_client()->get_player_for_user_id(userid);

	if (index != last_confirmed->record.index)
		return;

	last_confirmed->server_info.index = index;
	last_confirmed->server_info.damage = event->get_int(_("dmg_health"));
	last_confirmed->server_info.hitgroup = event->get_int(_("hitgroup"));
}

void c_resolver::on_bullet_impact(c_game_event* event)
{
	const auto userid = event->get_int(_("userid"));
	const auto index = engine_client()->get_player_for_user_id(userid);

	if (index != engine_client()->get_local_player())
		return;

	if (shots.empty())
		return;

	resolver::shot* last_confirmed = nullptr;

	for (auto it = shots.rbegin(); it != shots.rend(); it = next(it))
	{
		if (it->confirmed && !it->skip)
		{
			last_confirmed = &*it;
			break;
		}
	}

	if (!last_confirmed)
		return;

	last_confirmed->impacted = true;
	last_confirmed->server_info.impacts.emplace_back(event->get_float(_("x")),
		event->get_float(_("y")),
		event->get_float(_("z")));
}

void c_resolver::on_weapon_fire(c_game_event* event)
{
	const auto userid = event->get_int(_("userid"));
	const auto index = engine_client()->get_player_for_user_id(userid);

	if (index != engine_client()->get_local_player())
		return;

	if (shots.empty())
		return;

	resolver::shot* last_unconfirmed = nullptr;

	for (auto it = shots.rbegin(); it != shots.rend(); it = next(it))
	{
		if (!it->confirmed)
		{
			last_unconfirmed = &*it;
			break;
		}

		it->skip = true;
	}

	if (!last_unconfirmed)
		return;

	last_unconfirmed->confirmed = true;
}


void c_resolver::on_render_start()
{
	for (auto it = shots.begin(); it != shots.end();)
	{
		if (it->time + 1.f < global_vars_base->curtime)
			it = shots.erase(it);
		else
			it = next(it);
	}

	for (auto it = shots.begin(); it != shots.end();)
	{
		if (it->confirmed && it->impacted)
		{
			resolve_shot(*it);
			c_esp::draw_local_impact(it->start, it->server_info.impacts.back());
			it = shots.erase(it);
		}
		else
			it = next(it);
	}
}
// Rikf7 Resolver [with anti-paste]