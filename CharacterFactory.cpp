#include "CharacterFactory.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"

Character* CharacterFactory::createCharacter(CharacterType type, const MyString& name)
{
	switch (type)
	{
	case CharacterType::Warrior: return new Warrior(name);
	case CharacterType::Mage: return new Mage(name);
	case CharacterType::Archer: return new Archer(name);
	default: return nullptr;
	}
}

Character* CharacterFactory::createCharacterByName(const MyString& typeName, const MyString& characterName)
{
	CharacterType type = stringToType(typeName);

	return createCharacter(type, characterName);
}

CharacterType CharacterFactory::stringToType(const MyString& typeName)
{
	if (typeName == "Warrior") return CharacterType::Warrior;
	if (typeName == "Mage") return CharacterType::Mage;
	if (typeName == "Archer") return CharacterType::Archer;
	return CharacterType::Warrior;
}

MyString CharacterFactory::typeToString(CharacterType type)
{
	switch (type)
	{
	case CharacterType::Warrior: return MyString("Warrior");
	case CharacterType::Mage: return MyString("Mage");
	case CharacterType::Archer: return MyString("Archer");
	default: return MyString("Warrior");
	}
}
