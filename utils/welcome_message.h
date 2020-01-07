#pragma once

#include <sstream>
#include "../security/string_obfuscation.h"

static const auto welcome_message = []() -> std::pair<std::string, char>
{
	std::stringstream str;
	str << _(
		"                     _______           ___      __          _		\n"
		"                    / ___/ /  ___ ____/ (_)__ _/ /____  ___( )___	\n"
		"                   / (_ / /__/ _ `/ _  / / _ `/ __/ _ \\/ __//(_-<	\n"
		"                   \\___/____/\\_,_/\\_,_/_/\\_,_/\\__/\\___/_/   /___/	\n"
		"                                                                   \n"
	);
	str << _("------------------------------------------------------------------------------------") << std::endl;
	str << _("Built on ") << _(__DATE__) << _(" at ") << _(__TIME__) << _(" | v2.3.0 ") << std::endl;
	str << _("------------------------------------------------------------------------------------") << std::endl;

	constexpr auto key = random::_char<__COUNTER__>::value;
	auto txt = str.str();

	for (auto& c : txt)
		c ^= key;

	return std::make_pair(txt, key);
}();
