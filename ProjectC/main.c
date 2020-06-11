#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DATA_SIZE 1000

int main()
{
    const char* FileName = "ToTheDecision.txt";

    char buffer[DATA_SIZE];

    int firstNumber = -1, secondNumber = -1;
    bool isFirst = true, isSecond = false;
    char mark = ' ';

    int beginIndex = 0, endIndex = 0;
    
    FILE* fPtr = fopen(FileName, "r"); // Mode - Только чтение
    

    //Проверка на наличие файла
    if (fPtr == NULL)
    {
        printf("Unable to read file.\n");
        exit(EXIT_FAILURE);
    }

    fgets(buffer, DATA_SIZE, fPtr);

    fPtr = fopen(FileName, "w+"); // Mode - Чтение / Запись, и при этом сам файл становится пустым.

    while (true) {

        for (int i = beginIndex; i < DATA_SIZE; i++)
        {
            if (buffer[i] >= 48 && buffer[i] < 58) {

                int number = getNumber(buffer[i]);

                if (isFirst) {

                    if (firstNumber == -1) {
                        beginIndex = i;
                        firstNumber = 0;
                    }

                    firstNumber = ParseInt(firstNumber, number);
                }
                else if (isSecond) {

                    if (secondNumber == -1) {
                        secondNumber = 0;
                    }

                    endIndex = i;
                    secondNumber = ParseInt(secondNumber, number);

                }
                else 
                {
                    break;
                }

            }
            else if (buffer[i] == 42 || buffer[i] == 43 || buffer[i] == 45 || buffer[i] == 47) {
                mark = buffer[i];

                isFirst = false;
                isSecond = true;
            }
            else 
            {
                break;
            }

        }

        int resultInt = 0;
        float resultFloat = 0.0f;

        bool isInt = false;


        switch (mark)
        {

        case 42:

            if (true) {

                resultInt = (int)(firstNumber * secondNumber);
                isInt = true;
                printf("result * = %d", resultInt);

            }

            break;
        case 43:

            if (true) {

                resultInt = (int)(firstNumber + secondNumber);
                isInt = true;
                printf("result + = %d", resultInt);
            }

            break;
        case 45:

            if (true) {

                resultInt = (int)(firstNumber - secondNumber);
                isInt = true;
                printf("result - = %d", resultInt);
            }

            break;
        case 47:

            if (true) {

                resultFloat = (float)((float)firstNumber / (float)secondNumber);
                printf("result / = %.2f", resultFloat);
                
            }

            break;
        }

        //Для дебага в консоль
        printf("\n");

        char BufferToWrite[256];

        if (isInt) {
            sprintf(BufferToWrite, "%d", resultInt);
        }
        else 
        {
            sprintf(BufferToWrite, "%.2f", resultFloat);
        }

        //Запись в файлик
        fputs(BufferToWrite, fPtr);
        fputs(" ", fPtr);
        

        if (buffer[endIndex + 1] == '\0' || buffer[endIndex + 1] == -52) {

            break;
        }
        else 
        {

            beginIndex = endIndex + 2;

            isFirst = true;
            isSecond = false;

            firstNumber = -1;
            secondNumber = -1;

        }

    }

    fclose(fPtr);

    return 0;
}

int getNumber(char charToNumber){

    return (int)(charToNumber - 48);

}

int ParseInt(int toReturn,int toSet) {

    toReturn = ((toReturn * 10) + toSet);
    return toReturn;

}
