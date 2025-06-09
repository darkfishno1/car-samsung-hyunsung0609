#include "CommonEnum.h"

class EngineVendor
{
private:
    char name[256];
    ENGINE_SYSTEM_TYPE type;
    vector<CAR_TYPE> availableCarTypeList;
public:
    bool addCompatibleCarType(CAR_TYPE type)
    {
        availableCarTypeList.push_back(type);

        return true;
    }
    bool verifCarType(CAR_TYPE type)
    {
        for (auto i : availableCarTypeList)
        {
            if (i == type)
                return true;
        }
        return false;
    }
public:
    EngineVendor(ENGINE_SYSTEM_TYPE engine_type, const char* str)
    {
        type = engine_type;
        strcpy(name, str);
    }

    ENGINE_SYSTEM_TYPE getType()
    {
        return type;
    }
    const char* getName()
    {
        return name;
    }
};


class BreakModuleVendor
{
private:
    char name[256];
    BRAKE_SYSTEM_TYPE type;
    vector<CAR_TYPE> availableCarTypeList;
    bool isNotCompatible = false;
    STEERING_SYSTEM_TYPE onlySupportSterring = STEERING_SYSTEM_TYPE::END_OF_STEERING_SYSTEM_TYPE;
public:
    bool addCompatibleCarType(CAR_TYPE type)
    {
        availableCarTypeList.push_back(type);

            
        return true;
    }
    bool verifCarType(CAR_TYPE type)
    {
        for (auto i : availableCarTypeList)
        {
            if (i == type)
                return true;
        }
        return false;
    }
    bool isOnlyOneSteeringModule()
    {
        return isNotCompatible;
    }
    STEERING_SYSTEM_TYPE getOnlySupportSteeringSystem()
    {
        return onlySupportSterring;
    }
public:
    BreakModuleVendor(BRAKE_SYSTEM_TYPE break_type, const char* str, bool isNotCompatible = false, STEERING_SYSTEM_TYPE onlySupportSterringType = STEERING_SYSTEM_TYPE::END_OF_STEERING_SYSTEM_TYPE)
    {
        type = break_type;
        strcpy(name, str);
        if (isNotCompatible == true)
        {
            this->isNotCompatible = true;
            onlySupportSterring = onlySupportSterringType;
        }
    }

    BRAKE_SYSTEM_TYPE getType()
    {
        return type;
    }
    const char* getName()
    {
        return name;
    }
};


class SteeringModuleVendor
{
private:
    char name[256];
    STEERING_SYSTEM_TYPE type;
    vector<CAR_TYPE> availableCarTypeList;
public:
    bool addCompatibleCarType(CAR_TYPE type)
    {
        availableCarTypeList.push_back(type);
        return true;
    }
    bool verifCarType(CAR_TYPE type)
    {
        for (auto i : availableCarTypeList)
        {
            if (i == type)
                return true;
        }
        return false;
    }
public:
    SteeringModuleVendor(STEERING_SYSTEM_TYPE streeing_type, const char* str)
    {
        type = streeing_type;
        strcpy(name, str);
    }

    STEERING_SYSTEM_TYPE getType()
    {
        return type;
    }
    const char* getName()
    {
        return name;
    }
};



class Car
{
private:
    CAR_TYPE carType;
    ENGINE_SYSTEM_TYPE engineType;
    BRAKE_SYSTEM_TYPE breakType;
    STEERING_SYSTEM_TYPE steeringType;

public:
    void setCarType(CAR_TYPE type)
    {
        carType = type;
    }
    void SetEngineType(ENGINE_SYSTEM_TYPE type)
    {
        engineType = type;
    }
    void SetBreakSystemType(BRAKE_SYSTEM_TYPE type)
    {
        breakType = type;
    }
    void SetSteeringType(STEERING_SYSTEM_TYPE type)
    {
        steeringType = type;
    }

    CAR_TYPE getCarType()
    {
        return carType;
    }
    ENGINE_SYSTEM_TYPE getEngineType()
    {
        return engineType;
    }
    BRAKE_SYSTEM_TYPE getBreakSystemType()
    {
        return breakType;
    }
    STEERING_SYSTEM_TYPE getSteeringType()
    {
        return steeringType;
    }


};