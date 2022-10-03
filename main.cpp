#include "openmp/openmp.h"

#include <iostream>

using namespace std;

int main()
{
    int topic;
    int task;
    cout<<"Specify the topic: ";
    cin>>topic;
    switch (topic)
    {
        case 1:
            cout<<"Specify the task: ";
            cin>>task;
            cout<<"\n\n";
            switch(task)
            {
                case 1:
                    executeFirstOpenMpTask();
                case 2:
                    executeSecondOpenMpTask();
                case 3:
                    executeThirdOpenMpTask();
                case 4:
                    executeFourthOpenMpTask();
                case 5:
                    executeFifthOpenMpTask();
                case 6:
                    executeSixthOpenMpTask();
                case 7:
                    executeSeventhOpenMpTask();
                case 9:
                    executeNinthOpenMpTask();
                case 10:
                    executeTenthOpenMpTask();
                case 11:
                    executeEleventhOpenMpTask();
                case 13:
                    executeThirteenthOpenMpTask();
                case 14:
                    executeFourteenthOpenMpTask();
            }
    }
}
