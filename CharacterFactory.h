#pragma once

#include "MyString.hpp"
#include "Character.h"

class CharacterFactory
{
public:
	static Character* createCharacter(CharacterType type, const MyString& name);

	static Character* createCharacterByName(const MyString& typeName, const MyString& characterName);

	static CharacterType stringToType(const MyString& typeName);

	static MyString typeToString(CharacterType type);

};
