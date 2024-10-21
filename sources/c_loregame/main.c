#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Interface
//Inventário
//Mapa

//========================= Utils =========================
int len(char* x) {
    int len = -1;
    while (x[++len]) {}
    return len;
}

struct Point {short x; short y;};
bool comparePos(struct Point p1, struct Point p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}
//========================= Items =========================

struct Item
{
    short id;
    char name[50];
};

struct Item itemMap =           {1, "Mapa"};
struct Item itemBasementKey =   {3, "Chave do Porão"};
struct Item itemSafeKey =       {4, "Chave do Cofre"};
struct Item itemBag =           {5, "Bolsa"};
struct Item itemBandage =       {6, "Bandagem"};
struct Item itemKnife =         {7, "Faca"};

void itemMapUse();


//========================= Rooms =========================
struct Room
{
    struct Item* item;
    bool discovered;
};

//rooms definition

//X0
struct Room r_x0y1 = {&itemBag, true}; //has a safe with a money bag inside //requires safe key
struct Room r_x0y3 = {&itemKnife, false}; //gets knife

//X1
struct Room r_x1y0 = {NULL, false};
struct Room r_x1y1 = {&itemMap, false};
struct Room r_x1y2 = {&itemSafeKey, false}; // requires basement key to access //gets safe key

struct Room r_x1y3 = {NULL, false}; //steps on a razor and bleed //needs a bandage to stop bleeding

//X2
struct Room r_x2y1 = {&itemBasementKey, false}; //gets basement key
struct Room r_x2y3 = {NULL, false};

//X3
struct Room r_x3y2 = {NULL, false}; // exit
struct Room r_x3y3 = {NULL, false}; //enemy //need to be killed with a knife 

struct Point mapLength = {4, 4};

//map definition
struct Room* map[4][4] = {
    {   NULL, &r_x0y1,    NULL, &r_x0y3}, 
    {&r_x1y0, &r_x1y1, &r_x1y2, &r_x1y3}, 
    {   NULL, &r_x2y1,    NULL, &r_x2y3},
    {   NULL,    NULL, &r_x3y2, &r_x3y3}
}; 

char PLAYER_STATUS[3][50] = {
    "Aflito", 
    "Aliviado", 
    "Sangrando"
};

enum PlayerStatus
{
    AFLITO,
    ALIVIADO,
    SANGRANDO
};

struct Player 
{
    char name[50];
    short maxLife;
    short life;
    short status;
    struct Point pos;
    struct Item* inventory[5];
};

struct Player player = {
    .name = "littlesekii", 
    .maxLife = 10, 
    .life = 10, 
    .status = AFLITO, 
    .pos = {0, 1}, 
    .inventory = {NULL, NULL, NULL, NULL, NULL}
};

//base
void runTitle();
void askPlayerName(char*);
void runIntro(char*);
void runGame();

//interface
void showStatus();
char listenOption(short);

//walk
void listenWalkOptions();

//check
void checkAmbient();

//inventory
bool addInventoryItem(struct Item*);
bool removeInventoryItem(struct Item*);
bool checkInventoryItem(short);


bool basementLocked = true;
bool safeLocked = true;
int main(int argc, char const *argv[])
{
    system("chcp 65001");
    system("cls");

    
    // ItemMapUse();

    goto __GAME;

    //shows titled
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
    runGame();
    
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
    printf("Você me parece aflito, boa sorte, %s...\n\n", playerName);
    system("pause");
}

void runGame() 
{
    bool validOption = true;
    while (true) {
        system("cls");

        showStatus(player);
        char choice = listenOption(validOption);

        validOption = true;
        switch (choice) {
            case '1':   
                listenWalkOptions(validOption);
            break;
            case '2':
            break;
            case '3':
                checkAmbient();
            break;
            case '4':                
                if (checkInventoryItem(itemMap.id))
                    itemMapUse();                
                else
                    validOption = false;
            break;
            default:
                validOption = false;
        }
    }
}

void showStatus() 
{
    printf("Nome: %s", player.name);
    printf("\n");
    printf("Energia: %d/%d", player.life, player.maxLife);
    printf("\n");
    printf("Estado: %s", PLAYER_STATUS[player.status]);
    // printf("----------------------------------------------------");
    printf("\n\n");
}

char listenOption(short validOption) {

    printf("O que você vai fazer?");
    printf("\n\n");
    printf("1 - Andar");
    printf("\n");
    printf("2 - Abrir Inventário");
    printf("\n");
    printf("3 - Checar Ambiente");
    if (checkInventoryItem(itemMap.id)) {
        printf("\n");
        printf("4 - Ver mapa");
    }
    printf("\n");
    printf("\n");

    if (!validOption) {
        printf("Opção inválida");
        printf("\n");
    }

    printf("Escolha uma opção [1, 2, 3");
    if (checkInventoryItem(itemMap.id)) {
        printf(", 4");
    }
    printf("]: ");

    char choice[1000];
    scanf("%s", choice);

    if (len(choice) > 1)
        return 0;

    return *choice;
}

void itemMapUse() {

    system("cls");
    //shows map graphic
    for (int y = 0; y < mapLength.y; y++) {
        for (int x = 0; x < mapLength.x; x++) {
            struct Point p = {x, y};           

            if (comparePos(player.pos, p))
                printf("[x]");
            else if (
                map[x][y] != NULL 
                && map[x][y]->discovered
            )
                printf("[ ]");            
            else    
                printf("   ");
        }
        printf("\n");
    }
    printf("\n");

    system("pause");
}


void listenWalkOptions() {

    bool validOptions[4] = {false};
    bool validOption = true;
    char choice[1000];
    int choiceInt;

    do {
        system("cls");

        printf("Para onde você vai andar?");
        printf("\n");
        printf("\n");
    
        //VERIFY IF PLAYER CAN WALK LEFT
        if (player.pos.x > 0 && map[player.pos.x - 1][player.pos.y] != NULL) {
            validOptions[0] = true;
            printf("%d - Andar para a esquerda", 1);
            printf("\n");
        }

        //VERIFY IF PLAYER CAN WALK UP
        if (player.pos.y > 0 && map[player.pos.x][player.pos.y - 1] != NULL) {
            validOptions[1] = true;
            printf("%d - Andar para cima", 2);
            printf("\n");
        }

        //VERIFY IF PLAYER CAN WALK RIGHT
        if (player.pos.x < mapLength.x - 1 && map[player.pos.x + 1][player.pos.y] != NULL) {
            validOptions[2] = true;
            printf("%d - Andar para a direita", 3);
            printf("\n");
        }

        //VERIFY IF PLAYER CAN WALK DOWN
        if (player.pos.y < mapLength.y - 1 && map[player.pos.x][player.pos.y + 1] != NULL) {
            validOptions[3] = true;
            printf("%d - Andar para baixo", 4);
            printf("\n");
        }
        printf("\n");

        if (!validOption) {
           printf("Opção inválida");
            printf("\n");
        }

        printf("Escolha uma opção [");
        for (size_t i = 1; i <= 4; i++)
        {
            if(validOptions[i - 1]) {
                printf("%d, ", i);
            }
        }
        
        //removes the final ", " 
        printf("\b\b]: ");

        scanf("%s", choice);

        if (len(choice) > 1)
            strcpy(choice, "0");


        // printf("%d", *choice - '0');
        // printf("%d", validOptions[(*choice - '0') - 1]);
        validOption = false;
        choiceInt = *choice - '0'; //char - '0' = convert char '5' to 5 int

    } while( 
        (choiceInt <= 0 || choiceInt > 4) || //verify if options is in range
        (!validOptions[choiceInt - 1])
    ); 
    system("cls");

    switch(*choice) {
        case '1':
            player.pos.x--;     

            printf("Você andou para a sala da esquerda.");
            break;
        case '2':
            player.pos.y--;

            printf("Você andou para a sala de cima.");
            break;
        case '3':
            player.pos.x++;

            printf("Você andou para a sala da direita.");
            break;
        case '4':
            //verifica porta trancada
            if (player.pos.x == 1 && player.pos.y == 1) {
                if (basementLocked) {
                    printf("Uma gigastesca porta trancada impede que você entre na sala de baixo.");        
                    printf("\n");
                    printf("\n");

                    if (!checkInventoryItem(itemBasementKey.id)) {
                        system("pause");
                        return;
                    } else {
                        basementLocked = false;
                        removeInventoryItem(&itemBasementKey);

                        printf("Você conseguiu abrí-la com a enorme chave.");        
                        printf("\n");
                        printf("\n");

                        printf("~ Usou Chave do Porão");        
                        printf("\n");
                        printf("\n");

                        system("pause");
                        system("cls");
                    }
                }
            }
            player.pos.y++;

            printf("Você andou para a sala de baixo.");
            break;    
    }
    map[player.pos.x][player.pos.y]->discovered = true;

    printf("\n");
    printf("\n");
    system("pause");
}


void checkAmbient() {
    
    system("cls");

    //SALA [x]
    if (player.pos.x == 0 && player.pos.y == 1) {
        
        if(safeLocked) {
            printf("Você olha ao redor e encontra um cofre.");
            printf("\n");
            printf("\n");
            if (checkInventoryItem(itemSafeKey.id)) {
                removeInventoryItem(&itemSafeKey);
                addInventoryItem(&itemBag);
                safeLocked = false;
                
                printf("Você destranca o cofre com a chave e encontra uma bolsa.");
                printf("\n");
                printf("\n");
                printf("~ Usou Chave do Porão");  
                printf("\n");
                printf("~ Obteve Bolsa");
                printf("\n");
                printf("\n");
                system("pause");
                return;
            } 
            else {
                printf("Você tenta abrí-lo a força, mas não consegue.");
                printf("\n");
                printf("\n");
                system("pause");
                return;
            }
        }

        printf("Você não encontra mais nada além do cofre já aberto.");
        printf("\n");
        printf("\n");
        system("pause");
        return;
    }

    //SALA [ ][x]
    if (player.pos.x == 1 && player.pos.y == 1) {
        if (!checkInventoryItem(itemMap.id)) {
            addInventoryItem(&itemMap);
            printf("Você encontra um mapa manchado de sangue preso em uma pelúcia.");
            printf("\n");
            printf("\n");
            printf("~ Obteve Mapa");
            printf("\n");
            printf("\n");
            system("pause");
            return;
        }

        printf("Você não encontra mais nada, além da pelúcia ensopada de sangue.");
        printf("\n");
        printf("\n");
        system("pause");
        return;
    }

    //        [x]
    //SALA [ ][ ]
    if (player.pos.x == 1 && player.pos.y == 0) {
        if (!checkInventoryItem(itemBasementKey.id) && basementLocked) {
            addInventoryItem(&itemBasementKey);
            printf("Você abre as portas e gavetas de um armário velho, você encontra");
            printf("\n");
            printf("roupas destruídas pelas traças com uma chave grande e pesada no meio delas.");
            printf("\n");
            printf("\n");
            printf("~ Obteve Chave do Porão");
            printf("\n");
            printf("\n");
            system("pause");
            return;
        }

        printf("Você não encontra mais nada além das roupas velhas.");
        printf("\n");
        printf("\n");
        system("pause");
        return;
    }

    //        [ ]
    //SALA [ ][ ]
    //        [x]
    if (player.pos.x == 1 && player.pos.y == 2) {

        if(safeLocked) {
            if (!checkInventoryItem(itemSafeKey.id)) {
                addInventoryItem(&itemSafeKey);
                printf("Há um quadro pendurado ao lado da grande porta com uma chave pequena.");
                printf("\n");
                printf("O quadro está bem alto, você pula para tentar alcançá-lo.");
                printf("\n");
                printf("\n");
                printf("Você bate os dedos na parte de baixo do quadro, ele cai no chão");
                printf("\n");
                printf("e o vidro se despedaça e você consegue pegar a chave.");
                printf("\n");
                printf("\n");
                printf("~ Obteve Chave do Cofre");
                printf("\n");
                printf("\n");
                system("pause");
                return;
            }
        }

        printf("Você não encontra mais nada, mas toma muito cuidado para não pisar nos cacos de vidro.");
        printf("\n");
        printf("\n");
        system("pause");
        return;
    }

    printf("Você olha ao redor e não encontra nada.");
    printf("\n");
    printf("\n");
    system("pause");
}

bool addInventoryItem(struct Item* item) {
    for(int i = 0; i < 5; i++) {
        if (player.inventory[i] == NULL) {
            player.inventory[i] = item;
            return true;
        }
    }

    return false;
}

bool removeInventoryItem(struct Item* item) {
    for(int i = 0; i < 5; i++) {
        if (player.inventory[i] != NULL && player.inventory[i]->id == item->id) {
            player.inventory[i] = NULL;
            return true;
        }
    }

    return false;
}

bool checkInventoryItem(short itemId) {
    for(int i = 0; i < 5; i++) {
        if (player.inventory[i] != NULL && player.inventory[i]->id == itemId)
            return true;
    }

    return false;
}


// //X0
// struct Room r_x0y1 = {&itemBag, true}; //has a safe with a money bag inside //requires safe key
// struct Room r_x0y3 = {&itemKnife, false}; //gets knife

// //X1
// struct Room r_x1y0 = {NULL, false};
// struct Room r_x1y1 = {&itemMap, false};
// struct Room r_x1y2 = {&itemSafeKey, false}; // requires basement key to access //gets safe key
// struct Room r_x1y3 = {NULL, false}; //steps on a razor and bleed //needs a bandage to stop bleeding

// //X2
// struct Room r_x2y1 = {&itemBasementKey, false}; //gets basement key
// struct Room r_x2y3 = {NULL, false};

// //X3
// struct Room r_x3y2 = {NULL, false}; // exit
// struct Room r_x3y3 = {NULL, false}; //enemy //need to be killed with a knife 