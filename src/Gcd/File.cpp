/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// C++ standard includes

// libfalltergeist includes
#include "../Gcd/File.h"
#include "../Exception.h"

// Third party includes

namespace libfalltergeist
{
namespace Gcd
{

File::File(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

File::File(std::ifstream * stream) : Dat::Item(stream)
{
    _initialize();
}

File::~File()
{
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    uint32(); // unknown 1

    // primary stats
    for (unsigned i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++)
    {
        setStat((STAT)i, uint32());
    }

    // secondary stats
    _hitPoints = uint32();
    _actionPoints = uint32();
    _armorClass = uint32();

    uint32(); // unknown 2

    _meleeDamage = uint32();
    _carryWeight = uint32();
    _sequence    = uint32();
    _healingRate = uint32();
    _criticalChance      = uint32();
    _criticalHitModifier = uint32();

    for (unsigned i = (unsigned)DAMAGE::NORMAL; i <= (unsigned)DAMAGE::EXPLOSIVE; i++)
    {
        setDamage((DAMAGE)i, uint32());
    }
    for (unsigned i = (unsigned)DAMAGE::NORMAL; i <= (unsigned)DAMAGE::EXPLOSIVE; i++)
    {
        setResistance((DAMAGE)i, uint32());
    }

    _radiationResistance = uint32();
    _poisonResistance    = uint32();
    _age    = uint32();
    _gender = (GENDER)uint32();

    // bonuses to primary stats
    for (unsigned i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++)
    {
        setStatBonus((STAT)i, uint32());
    }

    // bonuses to secondary stats
    _hitPointsBonus    = uint32();
    _actionPointsBonus = uint32();
    _armorClassBonus   = uint32();

    uint32(); // unknown 3

    _meleeDamageBonus = uint32();
    _carryWeightBonus = uint32();
    _sequenceBonus    = uint32();
    _healingRateBonus = uint32();
    _criticalChanceBonus      = uint32();
    _criticalHitModifierBonus = uint32();

    for (unsigned i = (unsigned)DAMAGE::NORMAL; i <= (unsigned)DAMAGE::EXPLOSIVE; i++)
    {
        setDamageBonus((DAMAGE)i, uint32());
    }
    for (unsigned i = (unsigned)DAMAGE::NORMAL; i <= (unsigned)DAMAGE::EXPLOSIVE; i++)
    {
        setResistanceBonus((DAMAGE)i, uint32());
    }

    _radiationResistanceBonus = uint32();
    _poisonResistanceBonus    = uint32();
    _ageBonus    = uint32();
    _genderBonus = uint32();

    //skills
    for (unsigned i = (unsigned)SKILL::SMALL_GUNS; i <= (unsigned)SKILL::OUTDOORSMAN; i++)
    {
        setSkill((SKILL)i, uint32());
    }

    // unknown
    uint32(); // unknown 4
    uint32(); // unknown 5
    uint32(); // unknown 6
    uint32(); // unknown 7

    // name
    char * name = new char[32]();
    this->readBytes(name, 32);
    setName(name);
    delete [] name;

    _firstTaggedSkill  = (SKILL)int32();
    _secondTaggedSkill = (SKILL)int32();
    _thirdTaggedSkill  = (SKILL)int32();
    _fourthTaggedSkill = (SKILL)int32();
    _firstTrait  = (TRAIT)int32();
    _secondTrait = (TRAIT)int32();
    _characterPoints = uint32();
}

uint32_t File::stat(STAT number) const
{
    if (number > STAT::LUCK) throw Exception("File::stat() - number out of range: " + std::to_string((unsigned)number));
    return _stats.at((unsigned)number);
}

void File::setStat(STAT number, uint32_t value)
{
    if (number > STAT::LUCK) throw Exception("File::setStat() - number out of range: " + std::to_string((unsigned)number));
    _stats.at((unsigned)number) = value;
}

uint32_t File::statBonus(STAT number) const
{
    if (number > STAT::LUCK) throw Exception("File::statBonus() - number out of range: " + std::to_string((unsigned)number));
    return _statsBonus.at((unsigned)number);
}

void File::setStatBonus(STAT number, uint32_t value)
{
    if (number > STAT::LUCK) throw Exception("File::setStatBonus() - number out of range: " + std::to_string((unsigned)number));
    _statsBonus.at((unsigned)number) = value;
}

uint32_t File::skill(SKILL number) const
{
    if (number > SKILL::OUTDOORSMAN) throw Exception("File::skill() - number out of range: " + std::to_string((unsigned)number));
    return _skills.at((unsigned)number);
}

void File::setSkill(SKILL number, uint32_t value)
{
    if (number > SKILL::OUTDOORSMAN) throw Exception("File::setSkill() - number out of range: " + std::to_string((unsigned)number));
    _skills.at((unsigned)number) = value;
}

uint32_t File::damage(DAMAGE type) const
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::damage() - type out of range: " + std::to_string((unsigned)type));
    return _damage.at((unsigned)type);
}

void File::setDamage(DAMAGE type, uint32_t value)
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::setDamage() - type out of range: " + std::to_string((unsigned)type));
    _damage.at((unsigned)type) = value;
}

uint32_t File::damageBonus(DAMAGE type) const
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::damageBonus() - type out of range: " + std::to_string((unsigned)type));
    return _damageBonus.at((unsigned)type);
}

void File::setDamageBonus(DAMAGE type, uint32_t value)
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::setDamageBonus() - type out of range: " + std::to_string((unsigned)type));
    _damageBonus.at((unsigned)type) = value;
}

uint32_t File::resistance(DAMAGE type) const
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::resistance() - type out of range: " + std::to_string((unsigned)type));
    return _resistance.at((unsigned)type);
}

void File::setResistance(DAMAGE type, uint32_t value)
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::setResistance() - type out of range: " + std::to_string((unsigned)type));
    _resistance.at((unsigned)type) = value;
}

uint32_t File::resistanceBonus(DAMAGE type) const
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::resistanceBonus() - type out of range: " + std::to_string((unsigned)type));
    return _resistanceBonus.at((unsigned)type);
}

void File::setResistanceBonus(DAMAGE type, uint32_t value)
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::setResistanceBonus() - type out of range: " + std::to_string((unsigned)type));
    _resistanceBonus.at((unsigned)type) = value;
}

void File::setHitPoints(uint32_t hitPoints)
{
    _hitPoints = hitPoints;
}

uint32_t File::hitPoints() const
{
    return _hitPoints;
}

void File::setActionPoints(uint32_t actionPoints)
{
    _actionPoints = actionPoints;
}

uint32_t File::actionPoints() const
{
    return _actionPoints;
}

void File::setArmorClass(uint32_t armorClass)
{
    _armorClass = armorClass;
}

uint32_t File::armorClass() const
{
    return _armorClass;
}

void File::setMeleeDamage(uint32_t meleeDamage)
{
    _meleeDamage = meleeDamage;
}

uint32_t File::meleeDamage() const
{
    return _meleeDamage;
}

void File::setCarryWeight(uint32_t carryWeight)
{
    _carryWeight = carryWeight;
}

uint32_t File::carryWeight() const
{
    return _carryWeight;
}

void File::setSequence(uint32_t sequence)
{
    _sequence = sequence;
}

uint32_t File::sequence() const
{
    return _sequence;
}

void File::setHealingRate(uint32_t healingRate)
{
    _healingRate = healingRate;
}

uint32_t File::healingRate() const
{
    return _healingRate;
}

void File::setCriticalChance(uint32_t criticalChance)
{
    _criticalChance = criticalChance;
}

uint32_t File::criticalChance() const
{
    return _criticalChance;
}

void File::setCriticalHitModifier(uint32_t criticalHitModifier)
{
    _criticalHitModifier = criticalHitModifier;
}

uint32_t File::criticalHitModifier() const
{
    return _criticalHitModifier;
}

void File::setRadiationResistance(uint32_t radiationResistance)
{
    _radiationResistance = radiationResistance;
}

uint32_t File::radiationResistance() const
{
    return _radiationResistance;
}

void File::setPoisonResistance(uint32_t poisonResistance)
{
    _poisonResistance = poisonResistance;
}

uint32_t File::poisonResistance() const
{
    return _poisonResistance;
}

void File::setAge(uint32_t age)
{
    _age = age;
}

uint32_t File::age() const
{
    return _age;
}

void File::setGender(GENDER gender)
{
    _gender = gender;
}

GENDER File::gender() const
{
    return _gender;
}

void File::setHitPointsBonus(uint32_t hitPointsBonus)
{
    _hitPointsBonus = hitPointsBonus;
}

uint32_t File::hitPointsBonus() const
{
    return _hitPointsBonus;
}

void File::setActionPointsBonus(uint32_t actionPointsBonus)
{
    _actionPointsBonus = actionPointsBonus;
}

uint32_t File::actionPointsBonus() const
{
    return _actionPointsBonus;
}

void File::setArmorClassBonus(uint32_t armorClassBonus)
{
    _armorClassBonus = armorClassBonus;
}

uint32_t File::armorClassBonus() const
{
    return _armorClassBonus;
}

void File::setMeleeDamageBonus(uint32_t meleeDamageBonus)
{
    _meleeDamageBonus = meleeDamageBonus;
}

uint32_t File::meleeDamageBonus() const
{
    return _meleeDamageBonus;
}

void File::setCarryWeightBonus(uint32_t carryWeightBonus)
{
    _carryWeightBonus = carryWeightBonus;
}

uint32_t File::carryWeightBonus() const
{
    return _carryWeightBonus;
}

void File::setSequenceBonus(uint32_t sequenceBonus)
{
    _sequenceBonus = sequenceBonus;
}

uint32_t File::sequenceBonus() const
{
    return _sequenceBonus;
}

void File::setHealingRateBonus(uint32_t healingRateBonus)
{
    _healingRateBonus = healingRateBonus;
}

uint32_t File::healingRateBonus() const
{
    return _healingRateBonus;
}

void File::setCriticalChanceBonus(uint32_t criticalChanceBonus)
{
    _criticalChanceBonus = criticalChanceBonus;
}

uint32_t File::criticalChanceBonus() const
{
    return _criticalChanceBonus;
}

void File::setCriticalHitModifierBonus(uint32_t criticalHitModifierBonus)
{
    _criticalHitModifierBonus = criticalHitModifierBonus;
}

uint32_t File::criticalHitModifierBonus() const
{
    return _criticalHitModifierBonus;
}

void File::setRadiationResistanceBonus(uint32_t radiationResistanceBonus)
{
    _radiationResistanceBonus = radiationResistanceBonus;
}

uint32_t File::radiationResistanceBonus() const
{
    return _radiationResistanceBonus;
}

void File::setPoisonResistanceBonus(uint32_t poisonResistanceBonus)
{
    _poisonResistanceBonus = poisonResistanceBonus;
}

uint32_t File::poisonResistanceBonus() const
{
    return _poisonResistanceBonus;
}

void File::setAgeBonus(uint32_t ageBonus)
{
    _ageBonus = ageBonus;
}

uint32_t File::ageBonus() const
{
    return _ageBonus;
}

void File::setGenderBonus(uint32_t genderBonus)
{
    _genderBonus = genderBonus;
}

uint32_t File::genderBonus() const
{
    return _genderBonus;
}

void File::setName(std::string name)
{
    _name = name;
}

std::string File::name() const
{
    return _name;
}

void File::setFirstTaggedSkill(SKILL firstTaggedSkill)
{
    _firstTaggedSkill = firstTaggedSkill;
}

SKILL File::firstTaggedSkill() const
{
    return _firstTaggedSkill;
}

void File::setSecondTaggedSkill(SKILL secondTaggedSkill)
{
    _secondTaggedSkill = secondTaggedSkill;
}

SKILL File::secondTaggedSkill() const
{
    return _secondTaggedSkill;
}

void File::setThirdTaggedSkill(SKILL thirdTaggedSkill)
{
    _thirdTaggedSkill = thirdTaggedSkill;
}

SKILL File::thirdTaggedSkill() const
{
    return _thirdTaggedSkill;
}

void File::setFourthTaggedSkill(SKILL fourthTaggedSkill)
{
    _fourthTaggedSkill = fourthTaggedSkill;
}

SKILL File::fourthTaggedSkill() const
{
    return _fourthTaggedSkill;
}

void File::setFirstTrait(TRAIT firstTrait)
{
    _firstTrait = firstTrait;
}

TRAIT File::firstTrait() const
{
    return _firstTrait;
}

void File::setSecondTrait(TRAIT secondTrait)
{
    _secondTrait = secondTrait;
}

TRAIT File::secondTrait() const
{
    return _secondTrait;
}

void File::setCharacterPoints(uint32_t characterPoints)
{
    _characterPoints = characterPoints;
}

uint32_t File::characterPoints() const
{
    return _characterPoints;
}

}
}
