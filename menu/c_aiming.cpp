#include "c_aiming.h"
#include "../security/string_obfuscation.h"
#include "framework/c_group_box.h"
#include "framework/c_checkbox.h"
#include "../utils/c_config.h"
#include "framework/c_float_select.h"
#include "framework/c_hotkey_select.h"

c_aiming::c_aiming(const c_vector2d size) : c_flow_layout(size, c_vector2d(12, 12))
{
	add_child(std::make_shared<c_group_box>(__("Legit"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_checkbox, __("Aim Assistance"), config.legit.assist),
		make_child(c_float_select, __("Field of View"), config.legit.fov, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Smoothing"), config.legit.smooth, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Target Range"), config.legit.backtrack, 100.f, 1.f, 1.f)
	}, c_vector2d(275, 75)));
	add_child(std::make_shared<c_group_box>(__("Rage"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_checkbox, __("Enabled"), config.rage.enabled),
		make_child(c_hotkey_select, __("Slowwalk"), config.rage.slow_walk),
		make_child(c_hotkey_select, __("Fakeduck"), config.misc.fake_duck),
		make_child(c_checkbox, __("Infinite Duck"), config.rage.infinite_duck)
	}, c_vector2d(275, 75)));
	add_child(std::make_shared<c_group_box>(__("Auto Sniper"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_float_select, __("Hitchance"), config.rage.auto_snipe.hitchance, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Minimum Damage"), config.rage.auto_snipe.min_dmg, 150.f, 1.f, 1.f),
		make_child(c_float_select, __("Head Scale"), config.rage.auto_snipe.head_scale, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Body Scale"), config.rage.auto_snipe.body_scale, 100.f, 1.f, 1.f)
	}, c_vector2d(275, 75)));
	add_child(std::make_shared<c_group_box>(__("Scout"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_float_select, __("Hitchance"), config.rage.scout.hitchance, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Minimum Damage"), config.rage.scout.min_dmg, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Head Scale"), config.rage.scout.head_scale, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Body Scale"), config.rage.scout.body_scale, 100.f, 1.f, 1.f)
	}, c_vector2d(275, 75)));
	add_child(std::make_shared<c_group_box>(__("AWP"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_float_select, __("Hitchance"), config.rage.awp.hitchance, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Minimum Damage"), config.rage.awp.min_dmg, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Head Scale"), config.rage.awp.head_scale, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Body Scale"), config.rage.awp.body_scale, 100.f, 1.f, 1.f)
	}, c_vector2d(275, 75)));
	add_child(std::make_shared<c_group_box>(__("Pistol"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_float_select, __("Hitchance"), config.rage.pistol.hitchance, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Minimum Damage"), config.rage.pistol.min_dmg, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Head Scale"), config.rage.pistol.head_scale, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Body Scale"), config.rage.pistol.body_scale, 100.f, 1.f, 1.f)
	}, c_vector2d(275, 75)));
	add_child(std::make_shared<c_group_box>(__("Heavy"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_float_select, __("Hitchance"), config.rage.heavy.hitchance, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Minimum Damage"), config.rage.heavy.min_dmg, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Head Scale"), config.rage.heavy.head_scale, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Body Scale"), config.rage.heavy.body_scale, 100.f, 1.f, 1.f)
	}, c_vector2d(275, 75)));
	add_child(std::make_shared<c_group_box>(__("Other"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_float_select, __("Hitchance"), config.rage.misc.hitchance, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Minimum Damage"), config.rage.misc.min_dmg, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Head Scale"), config.rage.misc.head_scale, 100.f, 1.f, 1.f),
		make_child(c_float_select, __("Body Scale"), config.rage.misc.body_scale, 100.f, 1.f, 1.f)
	}, c_vector2d(275, 75)));
}
