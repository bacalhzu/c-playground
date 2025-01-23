#include <stdio.h>
#include <string.h>

// ITEM DEFINITION

//struct type definition
typedef struct s_Item Item; 

//item use method type definition
typedef void (use_f)(Item *); 

//struct definition
struct s_Item 
{
    int code;
    char name[64];
    char desc[256];
    use_f * use;
};

//item use methods definitions
void itemUseFunction_default(Item * self) {}
void itemUseFunction_default_place(Item * self) {printf("Item %s placed.", self->name);}

//item manip methods definitions
void setItem(Item *, int, const char *, const char *, use_f *);
void listItem(Item *);


//INVENTORY DEFINITION

const int INVENTORY_SIZE = 36;
Item inventory[36];

void pushInventoryItem(Item [], Item);

// MAIN METHOD
int main() 
{

    Item wood, water;


    setItem(&wood, 1, "Wood", "A small piece of wood. Can be used to craft items.", itemUseFunction_default_place);
    setItem(&water, 2, "Water", "A fluid and clear liquid.", itemUseFunction_default_place);

    // listItem(&wood);
    // printf("\n");
    // wood.use(&wood);
    // printf("\n");
    
    // printf("\n");
    // listItem(&water);
    // printf("\n");
    // wood.use(&water);

    pushInventoryItem(inventory, wood);
    pushInventoryItem(inventory, wood); 
    pushInventoryItem(inventory, water);
    pushInventoryItem(inventory, water);
    pushInventoryItem(inventory, wood);


    
    for (size_t i = 0; i < INVENTORY_SIZE; i++)
    {
        if (inventory[i].code != 0)
            listItem(&inventory[i]);
    }
    
    return 0;
}

void setItem(Item * item, int code, const char * name, const char * desc, use_f * useFunction) {
    item->code = code;
    strcpy(item->name, name);
    strcpy(item->desc, desc);
    item->use = useFunction;
}

void listItem(Item * item) {
    printf("ITEM %d\n\n"
        "%s\n"
        "%s\n\n",
        item->code, item->name, item->desc);
}

void pushInventoryItem(Item inventory[], Item item) {
    for (size_t i = 0; i < INVENTORY_SIZE; i++)
    {
        if (inventory[i].code == 0) {
            inventory[i] = item;
            printf("Item \"%s\" Added! %d of %d\n", item.name, i + 1, INVENTORY_SIZE);
            return;
        }
    }
    printf("Inventory is full!\n");
}