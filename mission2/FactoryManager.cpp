#include "CommonEnum.h"
#include "Module.cpp"

class CarFactory
{
private:
    char carTypeString[4][10] = { "NONE", "SEDAN", "SUV", "TRUCK" };
    vector<EngineVendor* > engineList;
    vector<BreakModuleVendor* > breakSystemList;
    vector<SteeringModuleVendor* > steeringSystemList;
public:

    bool addEngineVendor(EngineVendor* module)
    {
        engineList.push_back(module);
        return true;
    }
    int getEngineCount()
    {
        return (int)engineList.size();
    }
    bool addBreakModuleVendor(BreakModuleVendor* module)
    {
        breakSystemList.push_back(module);
        return true;
    }
    int getBreakModuleCount()
    {
        return (int)breakSystemList.size();
    }
    bool addSteeringModuleVendor(SteeringModuleVendor* module)
    {
        steeringSystemList.push_back(module);
        return true;
    }
    int getSteeringModuleCount()
    {
        return (int)steeringSystemList.size();
    }

    bool CheckEngineSystem(CAR_TYPE car_type, ENGINE_SYSTEM_TYPE endgine_type, bool print_error = false)
    {
        for (EngineVendor* e : engineList)
        {
            if (e->getType() == endgine_type)
            {
                if (e->verifCarType(car_type) == false)
                {
                    if (print_error)
                    {
                        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
                        printf("%s���� %s������ġ ��� �Ұ�\n", carTypeString[car_type], e->getName());
                    }
                    return false;
                }
                else
                    return true;
            }
        }

        if (print_error == true && endgine_type == ENGINE_SYSTEM_TYPE::BROKEN_ENGINE)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        }
        return false;
    }

    bool CheckBreakSystem(CAR_TYPE car_type, BRAKE_SYSTEM_TYPE break_type, STEERING_SYSTEM_TYPE steering_type, bool print_error = false)
    {
        for (BreakModuleVendor* e : breakSystemList)
        {
            if (e->getType() == break_type)
            {
                if (e->verifCarType(car_type))
                {
                    if (e->isOnlyOneSteeringModule())
                    {
                        if (steering_type == e->getOnlySupportSteeringSystem())
                            return true;
                        else
                        {
                            if (print_error)
                            {

                                printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
                                printf("%s������ġ���� %s������ġ �̿� ��� �Ұ�\n", e->getName(), e->getName());
                            }
                            return false;
                        }
                            
                    }
                    return true;
                }
                else
                {
                    if (print_error)
                    {
                        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
                        printf("%s���� %s������ġ ��� �Ұ�\n", carTypeString[car_type], e->getName());
                    }
                    return false;
                }
            }
        }
        return false;
    }

    bool CheckSteeringSystem(CAR_TYPE car_type, STEERING_SYSTEM_TYPE steering_type, bool print_error = false)
    {
        for (SteeringModuleVendor* e : steeringSystemList)
        {
            if (e->getType() == steering_type)
            {
                if (e->verifCarType(car_type) == false)
                {
                    if (print_error)
                    {
                        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
                        printf("%s���� %������ġ ��� �Ұ�\n", carTypeString[car_type], e->getName());
                    }
                    return false;
                }
                else
                    return true;
            }
        }
        return false;
    }


public:
    void printSelectEngine(int type)
    {
        for (EngineVendor* e : engineList)
        {
            if (e->getType() == type)
            {
                printf("%s ������ �����ϼ̽��ϴ�.\n", e->getName());
            }
        }
    }

    void printSelectBreakSystem(int type)
    {
        for (BreakModuleVendor* e : breakSystemList)
        {
            if (e->getType() == type)
            {
                printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", e->getName());
            }
        }
    }

    void printSelectSteeringSystem(int type)
    {
        for (SteeringModuleVendor* e : steeringSystemList)
        {
            if (e->getType() == type)
            {
                printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", e->getName());
            }
        }
    }

    void printModuleList(Car* car )
    {
        CAR_TYPE car_type = car->getCarType();
        if (car_type == CAR_TYPE::SEDAN)
            printf("Car Type : Sedan\n");
        else if (car_type == CAR_TYPE::SUV)
            printf("Car Type : SUV\n");
        else if (car_type == CAR_TYPE::TRUCK)
            printf("Car Type : Truck\n");

        ENGINE_SYSTEM_TYPE engine_type = car->getEngineType();
        BRAKE_SYSTEM_TYPE break_type = car->getBreakSystemType();
        STEERING_SYSTEM_TYPE steering_type = car->getSteeringType();

        for (EngineVendor* e : engineList)
        {
            if (e->getType() == engine_type)
            {
                printf("ENGINE_SYSTEM_TYPE : %s\n", e->getName());
            }
        }

        for (BreakModuleVendor* e : breakSystemList)
        {
            if (e->getType() == break_type)
            {
                printf("Brake System : %s\n", e->getName());
            }
        }

        for (SteeringModuleVendor* e : steeringSystemList)
        {
            if (e->getType() == steering_type)
            {
                printf("STEERING_SYSTEM_TYPE : %s\n", e->getName());
            }
        }
    }
};

class CarFactorManager
{
private:
    Car car;
private:
    int question_step = CAR_TYPE_Q;
    CarFactory factory;
public:
    CarFactorManager()
    {
        question_step = CAR_TYPE_Q;
        updateEngineVendor();
        updateBreakSystemVendor();
        updateSteeringSystemVendor();
    }
public:
    bool updateEngineVendor()
    {
        EngineVendor* gm = new EngineVendor(ENGINE_SYSTEM_TYPE::GM, "GM");
        gm->addCompatibleCarType(CAR_TYPE::SEDAN);
        gm->addCompatibleCarType(CAR_TYPE::SUV);
        gm->addCompatibleCarType(CAR_TYPE::TRUCK);
        factory.addEngineVendor(gm);

        EngineVendor* toyota = new EngineVendor(ENGINE_SYSTEM_TYPE::TOYOTA, "TOYOTA");
        toyota->addCompatibleCarType(CAR_TYPE::SEDAN);
        //toyota->addCompatibleCarType(CAR_TYPE::SUV);
        toyota->addCompatibleCarType(CAR_TYPE::TRUCK);
        factory.addEngineVendor(toyota);

        EngineVendor* wia = new EngineVendor(ENGINE_SYSTEM_TYPE::WIA, "WIA");
        wia->addCompatibleCarType(CAR_TYPE::SEDAN);
        wia->addCompatibleCarType(CAR_TYPE::SUV);
        //wia->addCompatibleCarType(CAR_TYPE::TRUCK);
        factory.addEngineVendor(wia);
        return true;
    }

    bool updateBreakSystemVendor()
    {
        BreakModuleVendor* mando = new BreakModuleVendor(BRAKE_SYSTEM_TYPE::MANDO, "MANDO");
        mando->addCompatibleCarType(CAR_TYPE::SEDAN);
        mando->addCompatibleCarType(CAR_TYPE::SUV);
        //mando->addCompatibleCarType(CAR_TYPE::TRUCK);
        factory.addBreakModuleVendor(mando);

        BreakModuleVendor* conti = new BreakModuleVendor(BRAKE_SYSTEM_TYPE::CONTINENTAL, "CONTINENTAL");
        //conti->addCompatibleCarType(CAR_TYPE::SEDAN);
        conti->addCompatibleCarType(CAR_TYPE::SUV);
        conti->addCompatibleCarType(CAR_TYPE::TRUCK);
        factory.addBreakModuleVendor(conti);

        BreakModuleVendor* bosch = new BreakModuleVendor(BRAKE_SYSTEM_TYPE::BOSCH_B, "BOSCH", true, STEERING_SYSTEM_TYPE::BOSCH_S);
        bosch->addCompatibleCarType(CAR_TYPE::SEDAN);
        bosch->addCompatibleCarType(CAR_TYPE::SUV);
        bosch->addCompatibleCarType(CAR_TYPE::TRUCK);
        factory.addBreakModuleVendor(bosch);
        return true;
    }

    bool updateSteeringSystemVendor()
    {
        SteeringModuleVendor* bosch = new SteeringModuleVendor(STEERING_SYSTEM_TYPE::BOSCH_S, "BOSCH");
        bosch->addCompatibleCarType(CAR_TYPE::SEDAN);
        bosch->addCompatibleCarType(CAR_TYPE::SUV);
        bosch->addCompatibleCarType(CAR_TYPE::TRUCK);
        factory.addSteeringModuleVendor(bosch);

        SteeringModuleVendor* mobis = new SteeringModuleVendor(STEERING_SYSTEM_TYPE::MOBIS, "MOBIS");
        mobis->addCompatibleCarType(CAR_TYPE::SEDAN);
        mobis->addCompatibleCarType(CAR_TYPE::SUV);
        mobis->addCompatibleCarType(CAR_TYPE::TRUCK);
        factory.addSteeringModuleVendor(mobis);

        return true;
    }

    bool CheckCarAnswer(const int answer)
    {
        if (question_step == CAR_TYPE_Q && !(answer >= CAR_TYPE::SEDAN && answer <= CAR_TYPE::TRUCK))
        {
            printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
            delay(MENU_DELAY_TIME);
            return false;
        }
        return true;
    }

    bool CheckEngineAnswer(const int answer)
    {
        int count = factory.getEngineCount();
        if (question_step == ENGINE_SYSTEM_Q && !(answer >= BACK_TO_MENU && answer <= count + 1))
        {
            printf("ERROR :: ������ 1 ~ %d ������ ���� ����\n", count + 1);
            delay(MENU_DELAY_TIME);
            return false;
        }
        return true;
    }

    bool CheckBreakSystemAnswer(const int answer)
    {
        int count = factory.getBreakModuleCount();
        if (question_step == BREAK_SYSTEM_Q && !(answer >= BACK_TO_MENU && answer <= count))
        {
            printf("ERROR :: ������ġ�� 1 ~ %d ������ ���� ����\n", count);
            delay(MENU_DELAY_TIME);
            return false;
        }
        return true;
    }

    bool CheckSteeringSystemAnswer(const int answer)
    {
        int count = factory.getSteeringModuleCount();
        if (question_step == STEERING_SYSTEM_Q && !(answer >= BACK_TO_MENU && answer <= count))
        {
            printf("ERROR :: ������ġ�� 1 ~ %d ������ ���� ����\n", count);
            delay(MENU_DELAY_TIME);
            return false;
        }
        return true;
    }

public:

    int isValidCheck()
    {
        if (factory.CheckEngineSystem(car.getCarType(), car.getEngineType()) == false)
            return false;

        if (factory.CheckBreakSystem(car.getCarType(), car.getBreakSystemType(), car.getSteeringType()) == false)
            return false;

        if (factory.CheckSteeringSystem(car.getCarType(), car.getSteeringType()) == false)
            return false;
        
        return true;
    }

    bool ProcessAnswer(const int answer)
    {
        if (question_step == CAR_TYPE_Q)
        {
            selectCarType(answer);
            delay(MENU_DELAY_TIME);
            question_step = ENGINE_SYSTEM_Q;
        }
        else if (question_step == ENGINE_SYSTEM_Q)
        {
            selectEngine(answer);
            delay(MENU_DELAY_TIME);
            question_step = BREAK_SYSTEM_Q;
        }
        else if (question_step == BREAK_SYSTEM_Q)
        {
            selectbrakeSystem(answer);
            delay(MENU_DELAY_TIME);
            question_step = STEERING_SYSTEM_Q;
        }
        else if (question_step == STEERING_SYSTEM_Q)
        {
            selectSteeringSystem(answer);
            delay(MENU_DELAY_TIME);
            question_step = RUN_TEST;
        }
        else if (question_step == RUN_TEST && answer == RUN_PRODUCT_CAR)
        {
            runProducedCar();
            delay(PRODUCT_DELAY_TIME);
        }
        else if (question_step == RUN_TEST && answer == RUN_TEST_CAR)
        {
            printf("Test...\n");
            delay(TEST_DELAY_TIME);
            testProducedCar();
            delay(PRODUCT_DELAY_TIME);
        }

        return true;
    }

    bool checkAnswer(const int answer)
    {
        if(CheckCarAnswer(answer) == false)
            return false;

        if (CheckEngineAnswer(answer) == false)
            return false;

        if (CheckBreakSystemAnswer(answer) == false)
            return false;

        if (CheckSteeringSystemAnswer(answer) == false)
            return false;

        if (question_step == RUN_TEST && !(answer >= BACK_TO_MENU && answer <= END_OF_TEST_SYSTEM_TYPE))
        {
            printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
            delay(MENU_DELAY_TIME);
            return false;
        }

        // ó������ ���ư���
        if (answer == BACK_TO_MENU && question_step == RUN_TEST)
        {
            question_step = CAR_TYPE_Q;
            return false;
        }

        // �������� ���ư���
        if (answer == BACK_TO_MENU && question_step >= ENGINE_SYSTEM_Q)
        {
            question_step -= 1;
            return false;
        }

        return true;
    }


    int processInputData(int& answer)
    {
        char buf[100];

        printf("INPUT > ");
        fgets(buf, sizeof(buf), stdin);

        // ���� ���๮�� ����
        char* context = nullptr;
        strtok_s(buf, "\r", &context);
        strtok_s(buf, "\n", &context);

        if (isExit(buf) == true)
            return EXIT_MENU;
        if (convertNumber(buf, answer) == false)
            return NOT_NUMBER;

        return NUMBER;
    }

    bool printMenu()
    {
        const int selectedQuestion = question_step;
        if (selectedQuestion < CAR_TYPE_Q || RUN_TEST < selectedQuestion)
            return false;

        if (selectedQuestion == CAR_TYPE_Q)
        {
            printSelectCarType();
        }
        else if (selectedQuestion == ENGINE_SYSTEM_Q)
        {
            printSelectEngine();
        }
        else if (selectedQuestion == BREAK_SYSTEM_Q)
        {
            printSelectbrakeSystem();
        }
        else if (selectedQuestion == STEERING_SYSTEM_Q)
        {
            printSelectSteeringSystem();
        }
        else if (selectedQuestion == RUN_TEST)
        {
            printRunTest();
        }
        printf("===============================\n");

        return true;
    }


private:

    void runProducedCar()
    {
        if (isValidCheck() == false)
        {
            printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
        }
        else
        {
            if (car.getEngineType() == ENGINE_SYSTEM_TYPE::BROKEN_ENGINE)
            {
                printf("������ ���峪�ֽ��ϴ�.\n");
                printf("�ڵ����� �������� �ʽ��ϴ�.\n");
            }
            else
            {
                factory.printModuleList(&car);
                printf("�ڵ����� ���۵˴ϴ�.\n");
            }
        }
    }


    void testProducedCar()
    {
        if (factory.CheckEngineSystem(car.getCarType(), car.getEngineType(), true) == false)
            return;
        if (factory.CheckBreakSystem(car.getCarType(), car.getBreakSystemType(), car.getSteeringType(), true) == false)
            return;
        if (factory.CheckSteeringSystem(car.getCarType(), car.getSteeringType(), true) == false)
            return;

        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }

    void selectCarType(int answer)
    {
        car.setCarType(static_cast<CAR_TYPE>(answer));
        if (answer == CAR_TYPE::SEDAN)
            printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
        if (answer == CAR_TYPE::SUV)
            printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
        if (answer == CAR_TYPE::TRUCK)
            printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
    }

    void selectEngine(int answer)
    {
        car.SetEngineType(static_cast<ENGINE_SYSTEM_TYPE>(answer));
        factory.printSelectEngine(static_cast<ENGINE_SYSTEM_TYPE>(answer));
    }

    void selectbrakeSystem(int answer)
    {
        car.SetBreakSystemType(static_cast<BRAKE_SYSTEM_TYPE>(answer));
        factory.printSelectEngine(static_cast<ENGINE_SYSTEM_TYPE>(answer));
    }

    void selectSteeringSystem(int answer)
    {
        car.SetSteeringType(static_cast<STEERING_SYSTEM_TYPE>(answer));
        factory.printSelectSteeringSystem(static_cast<STEERING_SYSTEM_TYPE>(answer));

    }

    void delay(int ms)
    {
        volatile int sum = 0;
        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < 1000; j++)
            {
                for (int t = 0; t < ms; t++)
                {
                    sum++;
                }
            }
        }
    }

    bool isExit(const char* text)
    {
        if (!strcmp(text, "exit"))
        {
            printf("���̹���\n");
            return true;
        }
        return false;
    }

    bool convertNumber(const char* text, int& ret)
    {
        // ���ڷ� �� ������� Ȯ��
        char* checkNumber;
        ret = strtol(text, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

        // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
        if (*checkNumber != '\0')
        {
            printf("ERROR :: ���ڸ� �Է� ����\n");
            delay(MENU_DELAY_TIME);
            return false;
        }

        return true;
    }

    void printSelectCarType()
    {
        printf(CLEAR_SCREEN);

        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("� ���� Ÿ���� �����ұ��?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    }

    void printSelectEngine()
    {
        printf(CLEAR_SCREEN);
        printf("� ������ ž���ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. ���峭 ����\n");
    }

    void printSelectbrakeSystem()
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    }

    void printSelectSteeringSystem()
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    }

    void printRunTest()
    {
        printf(CLEAR_SCREEN);
        printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
        printf("� ������ �ұ��?\n");
        printf("0. ó�� ȭ������ ���ư���\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }
};