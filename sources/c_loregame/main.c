#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Interface
//Inventário
//Mapa

const char PLAYER_STATUS[3][50] = {
    "Aflito", 
    "Aliviado", 
    "Desgastado"
};

enum PlayerStatus
{
    AFLITO,
    ALIVIADO,
    DESGASTADO
};

struct Player 
{
    char name[50];
    int maxLife;
    int currentLife;
    char status[50];
};

void runTitle();
void askPlayerName(char*);
void runIntro(char*);
void runGame(struct Player*);

void showStatus(struct Player*);

int main(int argc, char const *argv[])
{
    system("chcp 65001");
    system("cls");

    struct Player player;

    strcpy(player.name, "littlesekii");
    strcpy(player.status, PLAYER_STATUS[AFLITO]);
    player.maxLife = 10;
    player.currentLife = player.maxLife;

    goto __GAME;
    Sleep(1000);

    //shows title
    runTitle();
    system("cls");

    //ask player name
    askPlayerName(player.name);
    system("cls");

    //shows game intro
    runIntro(player.name);
    system("cls");

__GAME:
    //runs game
    runGame(&player);
    
    return 0;
}

void runTitle() 
{
    printf("               C/Lore\n\n");
    printf("    ");
    system("pause");
}

void askPlayerName(char* playerName)
{
    printf("Como devo lhe chamar, viajante?\n\n");
    printf("Entre com seu nome: ");
    scanf("%s", playerName);
}

void runIntro(char* playerName) 
{
    printf("         Você me parece aflito, boa sorte, %s...\n\n", playerName);
    printf("              ");
    system("pause");
}

void runGame(struct Player* player) 
{
    showStatus(player);
}

void showStatus(struct Player* player) 
{
    printf("Nome: %s", player->name);
    printf("\n");
    printf("Energia: %d/%d", player->currentLife, player->maxLife);
    printf("\n");
    printf("Estado: %s", player->status);
    printf("\n");
    printf("----------------------------------------------------");
}
