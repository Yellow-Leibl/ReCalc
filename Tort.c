#include "tort.h"

int main(int argc, char ** argv)
{
    for (int i = 0; i < argc; i++)
    {
        if(isHelp(argv[i]))
        {
            printf("calc.exe [-?] expression [answer]\n");
            /*cout << "CALCULATOR" << endl << endl
            << "a.exe [-?] expression [answer]" 
            << endl << endl
            << "Скільки буде два плюс два?\n"
            << "Ой забула голова!\n"
            << "А для чого рахувати?\n"
            << "Є для цього калькулятор.\n"
            << endl
            << "З ним не лячно на контрольній.\n"
            << "Він надійний і кмітливий,\n"
            << "Порахує швидко, вмить,\n"
            << "Поки дзвоник задзвенить.\n"
            << endl
            << "Він додасть нам і відніме,\n"
            << "І помножить і поділить.\n"
            << "Слава! Слава! Є у нас\n"
            << "Калькулятор просто клас.\n"
            << endl
            << "Калькулятор не дитина\n"
            << "Він не вміє їсти й пить\n"
            << "Язика то він не має,\n"
            << "Тільки оком нам моргає\n"
            << endl
            << "Де ж він розуму набрався?\n"
            << "Може скаже нам секрет?\n"
            << "Чи чарівне слово знає,\n"
            << "Чи він носить амулет?\n"
            << endl
            << "Ось яка тут таємниця!\n"
            << "В нього ж старші браття є\n"
            << "Дистриб`ютор і комп`ютер\n"
            << "Йому снаги надає. " << endl;*/
            exit(1);
        }
    }
    
    if (argc > 1)
    {
        double res = Calculate(argv[1]);
        if (argc > 2)
        {
            if (res == atof(argv[2]))
                printf("%s\t%f\t-true\n", argv[1], res);
                // cout << argv[1] << "\t=" << res << "\t-true" << endl;
            else
                printf("%s\t%f\t-false\n", argv[1], res);
                // cout << argv[1] << "\t=" << res << "\t-false" << endl;
        }
        else
            printf("%f\n", res);
            // cout << res << endl;
    }
    else
    {
        char t[LNGP];
        while (fgets(t, LNGb, stdin))
        {
            if (keycmp(t, "z\n") || *t == '\n') break;
            // cout << Calc(t) << endl;
            printf("%f\n", Calculate(t));
        }
    }
}