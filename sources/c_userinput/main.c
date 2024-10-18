#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{

    system("chcp 65001");
    system("cls");

    char firstName[50], lastName[50], fullName[101];
    int birthYear, age;

    printf("Digite seu primeiro nome: ");
    scanf("%s", firstName);
    printf("Digite seu último nome: ");
    scanf("%s", lastName);

    printf("Digite o ano você nasceu: ");
    scanf("%d", &birthYear);

    //calculate age by difference between current year and birthYear

    time_t now = time(0); //get current time value
    struct tm currentTime = *localtime(&now); //convert time value to a localtime struct
    int currentYear = currentTime.tm_year + 1900; //get the current year by adding the 1900 gap

    age = currentYear - birthYear;

    system("cls");

    printf("Muito bem, %s %s é seu nome e nesse ano você fez ou fará %d anos!", firstName, lastName, age);

    return 0;
}
