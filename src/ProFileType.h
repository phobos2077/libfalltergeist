#ifndef LIBFALLTERGEIST_PROFILETYPE_H
#define LIBFALLTERGEIST_PROFILETYPE_H

namespace libfalltergeist
{
class DatFileItem;

class ProFileType
{
protected:
    DatFileItem * _datFileItem;

    unsigned int _objectTypeId;
    unsigned int _objectSubtypeId;
    unsigned int _objectId;

    unsigned int _messageId;

    unsigned int _frmTypeId;
             int _frmOffset;
    unsigned int _frmId;

    unsigned int _headFrmTypeId;
    unsigned int _headFrmId;

    unsigned int _lightDistance;
    unsigned int _lightIntencity;

    unsigned int _flags;
    unsigned int _flagsExt;

    unsigned int _scriptTypeId;
    unsigned int _scriptId;

    unsigned int _materialId;
    unsigned int _containerSize;
    unsigned int _weight;
    unsigned int _basePrice;

    unsigned int _inventoryFrmTypeId;
    unsigned int _inventoryFrmId;

    unsigned int _soundId;


public:
    enum { TYPE_ITEM = 0, TYPE_CRITTER, TYPE_SCENERY, TYPE_WALL, TYPE_TILE, TYPE_MISC };
    enum { TYPE_ITEM_ARMOR = 0, TYPE_ITEM_CONTAINER, TYPE_ITEM_DRUG, TYPE_ITEM_WEAPON, TYPE_ITEM_AMMO, TYPE_ITEM_MISC, TYPE_ITEM_KEY };
    enum { TYPE_SCENERY_DOOR = 0, TYPE_SCENERY_STAIR, TYPE_SCENERY_ELEVATOR, TYPE_SCENERY_LADDER_BOTTOM, TYPE_SCENERY_LADDER_TOP, TYPE_SCENERY_GENERIC };

    ProFileType(DatFileItem * datFileItem);
    ~ProFileType();

    DatFileItem * datFileItem();

    void open();

    unsigned int objectTypeId();
    unsigned int objectSubtypeId();
    int frmOffset();

};
}

#endif // LIBFALLTERGEIST_PROFILETYPE_H
