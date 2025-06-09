#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"
#define MENU_DELAY_TIME 800
#define TEST_DELAY_TIME 1500
#define PRODUCT_DELAY_TIME 2000
#define BACK_TO_MENU 0


int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

enum QUESTION_TYPE
{
    CAR_TYPE_Q,
    ENGINE_SYSTEM_Q,
    BREAK_SYSTEM_Q,
    STEERING_SYSTEM_Q,
    RUN_TEST,
};

enum CAR_TYPE
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum ENGINE_SYSTEM_TYPE
{
    INIT_ENGINE_TYPEE = BACK_TO_MENU,
    GM = 1,
    TOYOTA,
    WIA,
    BROKEN_ENGINE,
    END_OF_ENGINE_TYPE = BROKEN_ENGINE
};

enum BRAKE_SYSTEM_TYPE
{
    INIT_BREAK_SYSTEM = BACK_TO_MENU,
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B,
    END_OF_BREAK_SYSTEM_TYPE = BOSCH_B
};

enum STEERING_SYSTEM_TYPE
{
    INIT_STEERING_SYSTEM = BACK_TO_MENU,
    BOSCH_S = 1,
    MOBIS,
    END_OF_STEERING_SYSTEM_TYPE = MOBIS
};

enum TEST_SYSTEM_TYPE
{
    INIT_TEST_SYSTEM = BACK_TO_MENU,
    RUN_PRODUCT_CAR,
    RUN_TEST_CAR,
    END_OF_TEST_SYSTEM_TYPE = RUN_TEST_CAR
};

enum ANSWER_TYPE
{
    EXIT_MENU = 0,
    NOT_NUMBER = 1,
    NUMBER = 2
};

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

void printSelectCarType()
{
    printf(CLEAR_SCREEN);

    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}

void printSelectEngine()
{
    printf(CLEAR_SCREEN);
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
}

void printSelectbrakeSystem()
{
    printf(CLEAR_SCREEN);
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void printSelectSteeringSystem()
{
    printf(CLEAR_SCREEN);
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void printRunTest()
{
    printf(CLEAR_SCREEN);
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

bool printMenu(int selectedQuestion)
{
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

bool isExit(const char* text)
{
    if (!strcmp(text, "exit"))
    {
        printf("바이바이\n");
        return true;
    }
    return false;
}

bool convertNumber(const char* text, int& ret)
{
    // 숫자로 된 대답인지 확인
    char* checkNumber;
    ret = strtol(text, &checkNumber, 10); // 문자열을 10진수로 변환

    // 입력받은 문자가 숫자가 아니라면
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(MENU_DELAY_TIME);
        return false;
    }

    return true;
}

int processInputData(int &answer)
{
    char buf[100];

    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (isExit(buf) == true)
        return EXIT_MENU;
    if (convertNumber(buf, answer) == false)
        return NOT_NUMBER;

    return NUMBER;
}

bool checkAnswer(int& step, const int answer)
{
    if (step == CAR_TYPE_Q && !(answer >= CAR_TYPE::SEDAN && answer <= CAR_TYPE::TRUCK))
    {
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
        delay(MENU_DELAY_TIME);
        return false;
    }
    if (step == ENGINE_SYSTEM_Q && !(answer >= BACK_TO_MENU && answer <= ENGINE_SYSTEM_TYPE::END_OF_ENGINE_TYPE))
    {
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
        delay(MENU_DELAY_TIME);
        return false;
    }

    if (step == BREAK_SYSTEM_Q && !(answer >= BACK_TO_MENU && answer <= BRAKE_SYSTEM_TYPE::END_OF_BREAK_SYSTEM_TYPE))
    {
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
        delay(MENU_DELAY_TIME);
        return false;
    }

    if (step == STEERING_SYSTEM_Q && !(answer >= BACK_TO_MENU && answer <= STEERING_SYSTEM_TYPE::END_OF_STEERING_SYSTEM_TYPE))
    {
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
        delay(MENU_DELAY_TIME);
        return false;
    }

    if (step == RUN_TEST && !(answer >= BACK_TO_MENU && answer <= END_OF_TEST_SYSTEM_TYPE))
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        delay(MENU_DELAY_TIME);
        return false;
    }

    // 처음으로 돌아가기
    if (answer == BACK_TO_MENU && step == RUN_TEST)
    {
        step = CAR_TYPE_Q;
        return false;
    }

    // 이전으로 돌아가기
    if (answer == BACK_TO_MENU && step >= ENGINE_SYSTEM_Q)
    {
        step -= 1;
        return false;
    }

    return true;
}


bool ProcessAnswer(int& step, const int answer)
{
    if (step == CAR_TYPE_Q)
    {
        selectCarType(answer);
        delay(MENU_DELAY_TIME);
        step = ENGINE_SYSTEM_Q;
    }
    else if (step == ENGINE_SYSTEM_Q)
    {
        selectEngine(answer);
        delay(MENU_DELAY_TIME);
        step = BREAK_SYSTEM_Q;
    }
    else if (step == BREAK_SYSTEM_Q)
    {
        selectbrakeSystem(answer);
        delay(MENU_DELAY_TIME);
        step = STEERING_SYSTEM_Q;
    }
    else if (step == STEERING_SYSTEM_Q)
    {
        selectSteeringSystem(answer);
        delay(MENU_DELAY_TIME);
        step = RUN_TEST;
    }
    else if (step == RUN_TEST && answer == RUN_PRODUCT_CAR)
    {
        runProducedCar();
        delay(PRODUCT_DELAY_TIME);
    }
    else if (step == RUN_TEST && answer == RUN_TEST_CAR)
    {
        printf("Test...\n");
        delay(TEST_DELAY_TIME);
        testProducedCar();
        delay(PRODUCT_DELAY_TIME);
    }

    return true;
}

int main()
{
    int step = CAR_TYPE_Q;
    int answer = 0;
    int answer_ret = EXIT_MENU;

    while (1)
    {
        printMenu(step);
        answer_ret = processInputData(answer);

        if (answer_ret == ANSWER_TYPE::EXIT_MENU)
            break;
        if (answer_ret == ANSWER_TYPE::NOT_NUMBER)
            continue;
        if (checkAnswer(step, answer) == false)
            continue;

        ProcessAnswer(step, answer);
    }
}

void selectCarType(int answer)
{
    stack[CAR_TYPE_Q] = answer;
    if (answer == CAR_TYPE::SEDAN)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (answer == CAR_TYPE::SUV)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (answer == CAR_TYPE::TRUCK)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void selectEngine(int answer)
{
    stack[ENGINE_SYSTEM_Q] = answer;
    if (answer == ENGINE_SYSTEM_TYPE::GM)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (answer == ENGINE_SYSTEM_TYPE::TOYOTA)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (answer == ENGINE_SYSTEM_TYPE::WIA)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void selectbrakeSystem(int answer)
{
    stack[BREAK_SYSTEM_Q] = answer;
    if (answer == BRAKE_SYSTEM_TYPE::MANDO)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (answer == BRAKE_SYSTEM_TYPE::CONTINENTAL)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (answer == BRAKE_SYSTEM_TYPE::BOSCH_B)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(int answer)
{
    stack[STEERING_SYSTEM_Q] = answer;
    if (answer == STEERING_SYSTEM_TYPE::BOSCH_S)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (answer == STEERING_SYSTEM_TYPE::MOBIS)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

int isValidCheck()
{
    if (stack[CAR_TYPE_Q] == SEDAN && stack[BREAK_SYSTEM_Q] == CONTINENTAL)
    {
        return false;
    }
    else if (stack[CAR_TYPE_Q] == SUV && stack[ENGINE_SYSTEM_Q] == TOYOTA)
    {
        return false;
    }
    else if (stack[CAR_TYPE_Q] == TRUCK && stack[ENGINE_SYSTEM_Q] == WIA)
    {
        return false;
    }
    else if (stack[CAR_TYPE_Q] == TRUCK && stack[BREAK_SYSTEM_Q] == MANDO)
    {
        return false;
    }
    else if (stack[BREAK_SYSTEM_Q] == BOSCH_B && stack[STEERING_SYSTEM_Q] != BOSCH_S)
    {
        return false;
    }
    /*
    else if (stack[BREAK_SYSTEM_Q] != BOSCH_B && stack[STEERING_SYSTEM_Q] == BOSCH_S)
    {
        return false;
    }
    */
    else
    {
        return true;
    }
    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
        if (stack[ENGINE_SYSTEM_Q] == ENGINE_SYSTEM_TYPE::BROKEN_ENGINE)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        }
        else
        {
            if (stack[CAR_TYPE_Q] == CAR_TYPE::SEDAN)
                printf("Car Type : Sedan\n");
            if (stack[CAR_TYPE_Q] == CAR_TYPE::SUV)
                printf("Car Type : SUV\n");
            if (stack[CAR_TYPE_Q] == CAR_TYPE::TRUCK)
                printf("Car Type : Truck\n");
            if (stack[ENGINE_SYSTEM_Q] == ENGINE_SYSTEM_TYPE::GM)
                printf("ENGINE_SYSTEM_TYPE : GM\n");
            if (stack[ENGINE_SYSTEM_Q] == ENGINE_SYSTEM_TYPE::TOYOTA)
                printf("ENGINE_SYSTEM_TYPE : TOYOTA\n");
            if (stack[ENGINE_SYSTEM_Q] == ENGINE_SYSTEM_TYPE::WIA)
                printf("ENGINE_SYSTEM_TYPE : WIA\n");
            if (stack[BREAK_SYSTEM_Q] == BRAKE_SYSTEM_TYPE::MANDO)
                printf("Brake System : Mando");
            if (stack[BREAK_SYSTEM_Q] == BRAKE_SYSTEM_TYPE::CONTINENTAL)
                printf("Brake System : Continental\n");
            if (stack[BREAK_SYSTEM_Q] == BRAKE_SYSTEM_TYPE::BOSCH_B)
                printf("Brake System : Bosch\n");
            if (stack[STEERING_SYSTEM_Q] == STEERING_SYSTEM_TYPE::BOSCH_S)
                printf("STEERING_SYSTEM_TYPE : Bosch\n");
            if (stack[STEERING_SYSTEM_Q] == STEERING_SYSTEM_TYPE::MOBIS)
                printf("STEERING_SYSTEM_TYPE : Mobis\n");

            printf("자동차가 동작됩니다.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[CAR_TYPE_Q] == SEDAN && stack[BREAK_SYSTEM_Q] == CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (stack[CAR_TYPE_Q] == SUV && stack[ENGINE_SYSTEM_Q] == TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (stack[CAR_TYPE_Q] == TRUCK && stack[ENGINE_SYSTEM_Q] == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (stack[CAR_TYPE_Q] == TRUCK && stack[BREAK_SYSTEM_Q] == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (stack[BREAK_SYSTEM_Q] == BOSCH_B && stack[STEERING_SYSTEM_Q] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}