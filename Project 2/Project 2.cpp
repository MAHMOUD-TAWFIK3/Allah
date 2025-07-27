#include <iostream>
#include <string >
#include <cstdlib>
#include <ctime>
using namespace std;

enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mixe = 5 };

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    enOpType OpType;
    enQuestionLevel QuestionLevel;
};
struct stGameQueizz
{
    stQuestion arrQuestions[100];
    int NumberOfQuestions = 0;
    enOpType OpType;
    enQuestionLevel QuestionLevel;
    short NumberOfWrongAnswer = 0;
    short NumberOfRightAnswer = 0;
    bool IsPass = true;
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}
unsigned short ReadNumberOfQuestions()
{
    unsigned short NumberOfQuestions = 0;
    cout << "Enter Many Questions ? ";
    cin >> NumberOfQuestions;
    return NumberOfQuestions;
}
enQuestionLevel QuestionLevel()
{
    short QuestionLevel = 0;
    do
    {
        cout << "Enter Question Level [1]Easy, [2]Med, [3]Hard, [4]Mix ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);
    return (enQuestionLevel)QuestionLevel;
}
enOpType OpType()
{
    short OpType = 0;
    do
    {
        cout << "Enter Op Type [1]Add, [2]Sub, [3]Mul, [4]Div [5]Mix ? ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);
    return (enOpType)OpType;
}

int GetCorrectAnswer(int Number1, int Number2, enOpType Op)
{
    switch (Op)
    {
    case enOpType::Add:
        return Number1 + Number2;
    case enOpType::Sub:
        return Number1 - Number2;
    case enOpType::Mul:
        return Number1 * Number2;
    case enOpType::Div:
        return Number1 / Number2;
    default :
        return Number1 + Number2;
    }
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOpType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionLevel::Mix)
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);

    if (OpType == enOpType::Mixe)
        OpType = (enOpType)RandomNumber(1, 4);

    Question.OpType = OpType;

    if (QuestionLevel == enQuestionLevel::Easy)
    {
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = GetCorrectAnswer(Question.Number1, Question.Number2, Question.OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }
    if (QuestionLevel == enQuestionLevel::Med)
    {
        Question.Number1 = RandomNumber(10, 100);
        Question.Number2 = RandomNumber(10, 100);
        Question.CorrectAnswer = GetCorrectAnswer(Question.Number1, Question.Number2, Question.OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }
    if (QuestionLevel == enQuestionLevel::Hard)
    {
        Question.Number1 = RandomNumber(100, 1000);
        Question.Number2 = RandomNumber(100, 1000);
        Question.CorrectAnswer = GetCorrectAnswer(Question.Number1, Question.Number2, Question.OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }
    return Question;
}

void GenerateQueizzQuestions(stGameQueizz& Queizz)
{
    for (short Questions = 0; Questions < Queizz.NumberOfQuestions; Questions++)
    {
        Queizz.arrQuestions[Questions] = GenerateQuestion(Queizz.QuestionLevel, Queizz.OpType);
    }
}

string GetSymbolOpType(enOpType OpType)
{
    string arrOpType[5] = { "+","-","*","/","Mix" };
    return arrOpType[OpType - 1];
}

void PrintTheQuestion(stGameQueizz& Queizz, short Questions)
{
    cout << "\n\nQuestion [" << Questions << "/" << Queizz.NumberOfQuestions << "]" << endl;
    cout << Queizz.arrQuestions[Questions].Number1 << endl;
    cout << Queizz.arrQuestions[Questions].Number2 << GetSymbolOpType(Queizz.arrQuestions[Questions].OpType);
    cout << "\n___________" << endl;
}

int ReadQuestionAnswer()
{
    int Num = 0;
    cin >> Num;
    return Num;
}

void CorrectAnswer(stGameQueizz& Queizz, short Questions)
{
    if (Queizz.arrQuestions[Questions].PlayerAnswer == Queizz.arrQuestions[Questions].CorrectAnswer)
    {
        cout << "\nRight Answer :-)\n";
        system("color 2F");
        Queizz.NumberOfRightAnswer++;
    }
    else
    {
        cout << "\nWrong Answer :-(\n";
        system("color 4F");
        Queizz.NumberOfWrongAnswer++;
        cout << "Right Answer Is: "<< Queizz.arrQuestions[Questions].CorrectAnswer;

    }

}

void AskAndCorrectQuestionListAnswers(stGameQueizz& Queizz)
{
    for (short Questions = 0; Questions < Queizz.NumberOfQuestions; Questions++)
    {
        PrintTheQuestion(Queizz, Questions);
        Queizz.arrQuestions[Questions].PlayerAnswer = ReadQuestionAnswer();
        CorrectAnswer(Queizz, Questions);
    }
    Queizz.IsPass = (Queizz.NumberOfRightAnswer >= Queizz.NumberOfWrongAnswer);
}

string GetFinalResult(bool Result)
{
    if (Result) return "Pass :)";
    else return "Fail :(";
}

string GetSymbolQuestionLevel(enQuestionLevel QuestionLevel)
{
    string arrQuestionLevel[4] = { "Easy","Med","Hard" ,"Mix" };
    return arrQuestionLevel[QuestionLevel - 1];
}

void PrintResult(stGameQueizz& Queizz)
{
    cout << "\n______________________________\n\n";
    cout << "Final Result Is "<< GetFinalResult(Queizz.IsPass);
    cout << "\n\n______________________________\n\n";
    cout << "Number Of Question: " << Queizz.NumberOfQuestions << endl;
    cout << "Question Level    : " << GetSymbolQuestionLevel(Queizz.QuestionLevel) << endl;
    cout << "Op Type           : " << GetSymbolOpType(Queizz.OpType) << endl;
    cout << "Number Of Right Answer: " << Queizz.NumberOfRightAnswer << endl;
    cout << "Number Of Wrong Answer: " << Queizz.NumberOfWrongAnswer << endl;
    cout << "\n\n______________________________\n\n";
}

void PlayMathGame()
{
    stGameQueizz Queizz;
    Queizz.NumberOfQuestions = ReadNumberOfQuestions();
    Queizz.QuestionLevel = QuestionLevel();
    Queizz.OpType = OpType();

    GenerateQueizzQuestions(Queizz);
    AskAndCorrectQuestionListAnswers(Queizz);
    PrintResult(Queizz);
}

void ResetScreen()
{
    system("color 0F");
    system("cls");
}

void StartGame()
{
    char PlayAgain = 'y';
    do
    {
        ResetScreen();
        PlayMathGame();

        cout << "\nDo You Want Play Again? Y/N ";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}