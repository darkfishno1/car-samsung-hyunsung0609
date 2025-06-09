#include "gmock/gmock.h"
#include "FactoryManager.cpp"

using namespace testing;

TEST(Group, TC1) {
	Car car;
	car.setCarType(CAR_TYPE::SEDAN);
	EXPECT_EQ(CAR_TYPE::SEDAN, car.getCarType());
}

TEST(FactoryManager, FULL_TEST)
{
    CarFactorManager manager;
    int answer = 0;
    int answer_ret = EXIT_MENU;

    while (1)
    {
        manager.printMenu();
        answer_ret = manager.processInputData(answer);
        if (answer_ret == ANSWER_TYPE::EXIT_MENU)
            break;
        if (answer_ret == ANSWER_TYPE::NOT_NUMBER)
            continue;
        if (manager.checkAnswer(answer) == false)
            continue;

        manager.ProcessAnswer(answer);
    }
}