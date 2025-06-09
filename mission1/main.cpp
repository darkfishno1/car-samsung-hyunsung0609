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

int processInputData(int &answer)
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

bool checkAnswer(int& step, const int answer)
{
    if (step == CAR_TYPE_Q && !(answer >= CAR_TYPE::SEDAN && answer <= CAR_TYPE::TRUCK))
    {
        printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
        delay(MENU_DELAY_TIME);
        return false;
    }
    if (step == ENGINE_SYSTEM_Q && !(answer >= BACK_TO_MENU && answer <= ENGINE_SYSTEM_TYPE::END_OF_ENGINE_TYPE))
    {
        printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
        delay(MENU_DELAY_TIME);
        return false;
    }

    if (step == BREAK_SYSTEM_Q && !(answer >= BACK_TO_MENU && answer <= BRAKE_SYSTEM_TYPE::END_OF_BREAK_SYSTEM_TYPE))
    {
        printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
        delay(MENU_DELAY_TIME);
        return false;
    }

    if (step == STEERING_SYSTEM_Q && !(answer >= BACK_TO_MENU && answer <= STEERING_SYSTEM_TYPE::END_OF_STEERING_SYSTEM_TYPE))
    {
        printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
        delay(MENU_DELAY_TIME);
        return false;
    }

    if (step == RUN_TEST && !(answer >= BACK_TO_MENU && answer <= END_OF_TEST_SYSTEM_TYPE))
    {
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
        delay(MENU_DELAY_TIME);
        return false;
    }

    // ó������ ���ư���
    if (answer == BACK_TO_MENU && step == RUN_TEST)
    {
        step = CAR_TYPE_Q;
        return false;
    }

    // �������� ���ư���
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
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (answer == CAR_TYPE::SUV)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (answer == CAR_TYPE::TRUCK)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void selectEngine(int answer)
{
    stack[ENGINE_SYSTEM_Q] = answer;
    if (answer == ENGINE_SYSTEM_TYPE::GM)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (answer == ENGINE_SYSTEM_TYPE::TOYOTA)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (answer == ENGINE_SYSTEM_TYPE::WIA)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void selectbrakeSystem(int answer)
{
    stack[BREAK_SYSTEM_Q] = answer;
    if (answer == BRAKE_SYSTEM_TYPE::MANDO)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == BRAKE_SYSTEM_TYPE::CONTINENTAL)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == BRAKE_SYSTEM_TYPE::BOSCH_B)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void selectSteeringSystem(int answer)
{
    stack[STEERING_SYSTEM_Q] = answer;
    if (answer == STEERING_SYSTEM_TYPE::BOSCH_S)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == STEERING_SYSTEM_TYPE::MOBIS)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
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
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (stack[ENGINE_SYSTEM_Q] == ENGINE_SYSTEM_TYPE::BROKEN_ENGINE)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
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

            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[CAR_TYPE_Q] == SEDAN && stack[BREAK_SYSTEM_Q] == CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (stack[CAR_TYPE_Q] == SUV && stack[ENGINE_SYSTEM_Q] == TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (stack[CAR_TYPE_Q] == TRUCK && stack[ENGINE_SYSTEM_Q] == WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (stack[CAR_TYPE_Q] == TRUCK && stack[BREAK_SYSTEM_Q] == MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (stack[BREAK_SYSTEM_Q] == BOSCH_B && stack[STEERING_SYSTEM_Q] != BOSCH_S)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}