#include "c_conf.h"
#include "../c_rifk.h"
#include "../security/string_obfuscation.h"
#include "framework/c_group_box.h"
#include "framework/c_button.h"
#include "../utils/c_config.h"

c_conf::c_conf(const c_vector2d size) : c_flow_layout(size, c_vector2d(12, 12))
{
	static const auto rage = __("C:\\GLadiators.technology\\rage.cfg");
	static const auto legit = __("C:\\GLadiators.technology\\legit.cfg");
	static const auto slot1 = __("C:\\GLadiators.technology\\slot1.cfg");
	static const auto slot2 = __("C:\\GLadiators.technology\\slot2.cfg");
	static const auto slot3 = __("C:\\GLadiators.technology\\slot3.cfg");
	static const auto slot4 = __("C:\\GLadiators.technology\\slot4.cfg");
	static const auto slot5 = __("C:\\GLadiators.technology\\slot5.cfg");
	static const auto slot6 = __("C:\\GLadiators.technology\\slot6.cfg");
	static const auto slot7 = __("C:\\GLadiators.technology\\slot7.cfg");
	static const auto slot8 = __("C:\\GLadiators.technology\\slot8.cfg");
	static const auto slot9 = __("C:\\GLadiators.technology\\slot9.cfg");
	static const auto slot10 = __("C:\\GLadiators.technology\\slot10.cfg");

	add_child(std::make_shared<c_group_box>(__("Rage"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_button, __("Load Rage"), c_vector2d(8, 4), []() -> void
		{
			_rt(ra, rage);
			char path[MAX_PATH];
			sprintf_s(path, ra, loader_info.loader_path);
			c_config::load_from_file(path);
		}),
			make_child(c_button, __("Save Rage"), c_vector2d(8, 4), []() -> void
		{
			_rt(ra, rage);
			char path[MAX_PATH];
			sprintf_s(path, ra, loader_info.loader_path);
			c_config::save_to_file(path);
		})
	}, c_vector2d(275, 40)));

	add_child(std::make_shared<c_group_box>(__("Legit"), std::initializer_list<std::shared_ptr<c_drawable>> {
			make_child(c_button, __("Load Legit"), c_vector2d(8, 4), []() -> void
		{
			_rt(le, legit);
			char path[MAX_PATH];
			sprintf_s(path, le, loader_info.loader_path);
			c_config::load_from_file(path);
		}),
			make_child(c_button, __("Save Legit"), c_vector2d(8, 4), []() -> void
		{
			_rt(le, legit);
			char path[MAX_PATH];
			sprintf_s(path, le, loader_info.loader_path);
			c_config::save_to_file(path);
		})
	}, c_vector2d(275, 40)));

	add_child(std::make_shared<c_group_box>(__("Slot 1"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_button, __("Load Slot 1"), c_vector2d(8, 4), []() -> void
			{
				_rt(le, slot1);
				char path[MAX_PATH];
				sprintf_s(path, le, loader_info.loader_path);
				c_config::load_from_file(path);
			}),
			make_child(c_button, __("Save Slot 1"), c_vector2d(8, 4), []() -> void
				{
					_rt(le, legit);
					char path[MAX_PATH];
					sprintf_s(path, le, loader_info.loader_path);
					c_config::save_to_file(path);
				})
	}, c_vector2d(275, 40)));

	add_child(std::make_shared<c_group_box>(__("Slot 2"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_button, __("Load Slot 2"), c_vector2d(8, 4), []() -> void
			{
				_rt(le, slot2);
				char path[MAX_PATH];
				sprintf_s(path, le, loader_info.loader_path);
				c_config::load_from_file(path);
			}),
			make_child(c_button, __("Save Slot 2"), c_vector2d(8, 4), []() -> void
				{
					_rt(le, legit);
					char path[MAX_PATH];
					sprintf_s(path, le, loader_info.loader_path);
					c_config::save_to_file(path);
				})
	}, c_vector2d(275, 40)));

	add_child(std::make_shared<c_group_box>(__("Slot 3"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_button, __("Load Slot 3"), c_vector2d(8, 4), []() -> void
			{
				_rt(le, slot3);
				char path[MAX_PATH];
				sprintf_s(path, le, loader_info.loader_path);
				c_config::load_from_file(path);
			}),
			make_child(c_button, __("Save Slot 3"), c_vector2d(8, 4), []() -> void
				{
					_rt(le, legit);
					char path[MAX_PATH];
					sprintf_s(path, le, loader_info.loader_path);
					c_config::save_to_file(path);
				})
	}, c_vector2d(275, 40)));

	add_child(std::make_shared<c_group_box>(__("Slot 4"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_button, __("Load Slot 4"), c_vector2d(8, 4), []() -> void
			{
				_rt(le, slot4);
				char path[MAX_PATH];
				sprintf_s(path, le, loader_info.loader_path);
				c_config::load_from_file(path);
			}),
			make_child(c_button, __("Save Slot 4"), c_vector2d(8, 4), []() -> void
				{
					_rt(le, legit);
					char path[MAX_PATH];
					sprintf_s(path, le, loader_info.loader_path);
					c_config::save_to_file(path);
				})
	}, c_vector2d(275, 40)));

	add_child(std::make_shared<c_group_box>(__("Slot 5"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_button, __("Load Slot 5"), c_vector2d(8, 4), []() -> void
			{
				_rt(le, slot5);
				char path[MAX_PATH];
				sprintf_s(path, le, loader_info.loader_path);
				c_config::load_from_file(path);
			}),
			make_child(c_button, __("Save Slot 5"), c_vector2d(8, 4), []() -> void
				{
					_rt(le, legit);
					char path[MAX_PATH];
					sprintf_s(path, le, loader_info.loader_path);
					c_config::save_to_file(path);
				})
	}, c_vector2d(275, 40)));

	add_child(std::make_shared<c_group_box>(__("Slot 6"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_button, __("Load Slot 6"), c_vector2d(8, 4), []() -> void
			{
				_rt(le, slot6);
				char path[MAX_PATH];
				sprintf_s(path, le, loader_info.loader_path);
				c_config::load_from_file(path);
			}),
			make_child(c_button, __("Save Slot 6"), c_vector2d(8, 4), []() -> void
				{
					_rt(le, legit);
					char path[MAX_PATH];
					sprintf_s(path, le, loader_info.loader_path);
					c_config::save_to_file(path);
				})
	}, c_vector2d(275, 40)));

	add_child(std::make_shared<c_group_box>(__("Slot 7"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_button, __("Load Slot 7"), c_vector2d(8, 4), []() -> void
			{
				_rt(le, slot7);
				char path[MAX_PATH];
				sprintf_s(path, le, loader_info.loader_path);
				c_config::load_from_file(path);
			}),
			make_child(c_button, __("Save Slot 7"), c_vector2d(8, 4), []() -> void
				{
					_rt(le, legit);
					char path[MAX_PATH];
					sprintf_s(path, le, loader_info.loader_path);
					c_config::save_to_file(path);
				})
	}, c_vector2d(275, 40)));

	add_child(std::make_shared<c_group_box>(__("Slot 8"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_button, __("Load Slot 8"), c_vector2d(8, 4), []() -> void
			{
				_rt(le, slot8);
				char path[MAX_PATH];
				sprintf_s(path, le, loader_info.loader_path);
				c_config::load_from_file(path);
			}),
			make_child(c_button, __("Save Slot 8"), c_vector2d(8, 4), []() -> void
				{
					_rt(le, legit);
					char path[MAX_PATH];
					sprintf_s(path, le, loader_info.loader_path);
					c_config::save_to_file(path);
				})
	}, c_vector2d(275, 40)));

	add_child(std::make_shared<c_group_box>(__("Slot 9"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_button, __("Load Slot 9"), c_vector2d(8, 4), []() -> void
			{
				_rt(le, slot9);
				char path[MAX_PATH];
				sprintf_s(path, le, loader_info.loader_path);
				c_config::load_from_file(path);
			}),
			make_child(c_button, __("Save Slot 9"), c_vector2d(8, 4), []() -> void
				{
					_rt(le, legit);
					char path[MAX_PATH];
					sprintf_s(path, le, loader_info.loader_path);
					c_config::save_to_file(path);
				})
	}, c_vector2d(275, 40)));

	add_child(std::make_shared<c_group_box>(__("Slot 10"), std::initializer_list<std::shared_ptr<c_drawable>> {
		make_child(c_button, __("Load Slot 10"), c_vector2d(8, 4), []() -> void
			{
				_rt(le, slot10);
				char path[MAX_PATH];
				sprintf_s(path, le, loader_info.loader_path);
				c_config::load_from_file(path);
			}),
			make_child(c_button, __("Save Slot 10"), c_vector2d(8, 4), []() -> void
				{
					_rt(le, legit);
					char path[MAX_PATH];
					sprintf_s(path, le, loader_info.loader_path);
					c_config::save_to_file(path);
				})
	}, c_vector2d(275, 40)));
}
