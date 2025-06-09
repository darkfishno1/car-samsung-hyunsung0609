#include "CommonEnum.h"
#include "FactoryManager.cpp"
#ifdef _DEBUG
#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
    return 0;
}
#else
int main()
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

        manager.ProcessAnswer( answer);
	}
}
#endif