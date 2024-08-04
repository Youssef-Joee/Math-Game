#include <iostream>

using namespace std;

enum enQuestionLevel { Easy = 1, Med, Hard, MixLevel };

enum enOperationType { Add = 1, Sub, Mult, Div, MixOp };

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionLevel QuestLevel;
    int RightAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = 0;

};

struct stQuiz
{
    stQuestion QuestionList[100];
    short NumberofQuest = 0;
    short NumberofRightAns = 0;
    short NumberofWrongAns = 0;
    enQuestionLevel QuestionLevel;
    enOperationType OperationType;
    bool isPass = 0;

};

short RandomNumber(short From, short To)
{
    return rand() % (To - From + 1) + From;

}

short ReadHowManyQuest()
{
    short NumberOfQuest = 0;
    do
    {
        cout << "How Many Questions do you want to answer ?";
        cin >> NumberOfQuest;

    } while (NumberOfQuest<1  || NumberOfQuest>10);

    return NumberOfQuest;

}

enQuestionLevel ReadQuestLevel()
{
    short QuestionLevel = 0;
    do
    {
        cout << "Enter Question Level [1]Easy, [2]Med, [3]Hard, [4]Mix ?";
        cin >> QuestionLevel;

    } while (QuestionLevel < 1 || QuestionLevel > 4);

    return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOperationType()
{
    short OpType = 0;

    do
    {
        cout << "Enter Operation Type [1]Add, [2]Sub, [3]Mul, [4]Div, [5]Mix ?";
        cin >> OpType;


    } while (OpType < 1 || OpType > 5);

    return (enOperationType)OpType;
}

int SimpleCalculator(int Number1, int Number2, enOperationType Operation)
{
    switch (Operation)
    {
    case Add:
        return Number1 + Number2;
    case Sub:
        return Number1 - Number2;
    case Mult:
        return Number1 * Number2;
    case Div:
        return Number1 / Number2;
    default:
        break;
    }

}

stQuestion Generate1Quest(enQuestionLevel QuestLevel ,enOperationType OpType)
{
    stQuestion Question;

    if (QuestLevel == enQuestionLevel::MixLevel)
    {
        QuestLevel = (enQuestionLevel)RandomNumber(1, 3);
    }

    if (OpType == enOperationType::MixOp)
    {
        OpType = (enOperationType)RandomNumber(1, 4);
    }

    Question.OperationType = OpType;

    switch (QuestLevel)
    {
    case Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.RightAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestLevel = QuestLevel;
        return Question;

    case Med:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.RightAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestLevel = QuestLevel;
        return Question;
        
    case Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.RightAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestLevel = QuestLevel;
        return Question;
        
    default:
        break;
    }

    return Question;

}

void GenerateQuizQuest(stQuiz& Quiz)
{
    for (short Question = 0; Question <= Quiz.NumberofQuest - 1; Question++)
    {
        Quiz.QuestionList[Question] = Generate1Quest(Quiz.QuestionLevel, Quiz.OperationType);
    }

}

string GetOpTypeSymbol(enOperationType OPeratoin)
{
    string arrOPeration[5] = { "+","-","*","/","Mix" };
    return arrOPeration[OPeratoin - 1];

}

void PrintTheQuestion(stQuiz Quiz, short QuestNumber)
{
    cout << "\n";
    cout << "Question [" << QuestNumber + 1 << "/" << Quiz.NumberofQuest << "] \n\n";
    cout << Quiz.QuestionList[QuestNumber].Number1 << endl;
    cout << Quiz.QuestionList[QuestNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quiz.QuestionList[QuestNumber].OperationType);
    cout << "\n _________" << endl;

}

int ReadPlayerAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;

}

void CorrectTheQuestAns(stQuiz& Quiz,short QuestionNumber)
{
    if (Quiz.QuestionList[QuestionNumber].PlayerAnswer != Quiz.QuestionList[QuestionNumber].RightAnswer)
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = false;
        Quiz.NumberofWrongAns++;

        system("Color 4F");
        cout << "Wrong Answer :-( \n" ;
        cout << "The Right answer is: " << Quiz.QuestionList[QuestionNumber].RightAnswer << endl;
    }
    else
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = true;
        Quiz.NumberofRightAns++;

        system("color 2F");
        cout << "Right Answer :-) \n" ;

    }
    cout << endl;

    
}

void AskandCorrectQuizQuests(stQuiz& Quiz)
{
    for (short Question = 0; Question <= Quiz.NumberofQuest - 1; Question++)
    {
        PrintTheQuestion(Quiz, Question);

        Quiz.QuestionList[Question].PlayerAnswer = ReadPlayerAnswer();

        CorrectTheQuestAns(Quiz, Question);

    }

    Quiz.isPass = (Quiz.NumberofRightAns >= Quiz.NumberofWrongAns);


}

string GetFinalResult(bool Pass)
{
    if (Pass == 1)
    {
        return "Pass";
    }
    else
        return "Fail";

}

string GetQuestLevelText(enQuestionLevel QuestionLevel)
{
    string arrQuestionLevel[4] = { "Easy" , "Medium", "Hard","Mix" };
    return arrQuestionLevel[QuestionLevel - 1];

}

void PrintQuizResults(stQuiz Quiz)
{
    cout << "________________________________ \n\n";
    cout << "  Final Results is " << GetFinalResult(Quiz.isPass) << endl;
    cout << "________________________________ \n";

    cout << "Number of Questions: " << Quiz.NumberofQuest << endl;
    cout << "Questions Level    : " << GetQuestLevelText(Quiz.QuestionLevel) << endl;
    cout << "Operation Type     : " << GetOpTypeSymbol(Quiz.OperationType) << endl;
    cout << "Number of Right Answers: " << Quiz.NumberofRightAns << endl;
    cout << "Number of Wrong Answers: " << Quiz.NumberofWrongAns << endl;
    cout << "________________________________ \n";



}

void PlayMathGame()
{
    stQuiz Quiz;

    Quiz.NumberofQuest = ReadHowManyQuest();
    Quiz.QuestionLevel = ReadQuestLevel();
    Quiz.OperationType = ReadOperationType();

    GenerateQuizQuest(Quiz);

    AskandCorrectQuizQuests(Quiz);

    PrintQuizResults(Quiz);
}

void ResetScreen()
{
    system("color 0F");
    system("cls");
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        PlayMathGame();

        cout << endl << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;


    } while (PlayAgain=='Y' || PlayAgain == 'y');


}

int main()
{
    //Seeds the random number generator in C++, Called only once in main()
    srand((unsigned)time(NULL));


    StartGame();


    return 0;
}
