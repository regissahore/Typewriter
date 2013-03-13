#ifndef VCGOUNITFACTORY_H
#define VCGOUNITFACTORY_H

#include "VAGoUnit.h"

class VCGoUnitFactory : public VAGoUnit
{
public:
    enum UnitType
    {
        OPERATOR_TEST = 0,
        OPERATOR_1 = 1,
        OPERATOR_2 = 2,
        OPERATOR_3 = 3,
        OPERATOR_4 = 4,
        OPERATOR_5 = 5,
        OPERATOR_6 = 6,
        OPERATOR_7 = 7,
        OPERATOR_8 = 8,
        OPERATOR_9 = 9,
        OPERATOR_10 = 10,
        OPERATOR_11 = 11,
        OPERATOR_12 = 12,
        OPERATOR_13 = 13,
        OPERATOR_14 = 14,
        OPERATOR_15 = 15,
        OPERATOR_16 = 16,
        OPERATOR_17 = 17,
        OPERATOR_SERIES_SET = 18
    };
    static VAGoUnit* getUnit(UnitType type);
};

#endif // VCGOUNITFACTORY_H
