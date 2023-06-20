#include <autorelease/allocs.h>
#include <stdio.h>

typedef struct {
  int age;
  char *name;
  char *type;
} Animal;

char *zoo_name;
Animal *animals;
int count = 0;

void addAnimal() {
  Animal *buffer = alloc_b(Animal, count+1);
  memcpy(buffer, animals, count);
  animals = buffer;
  animals[count].name = 
}

int main() {
  autoreleasepool(
    printf("Welcome to your zoo!\n");
    zoo_name = alloc_b(char, 256);
    printf("Please enter your zoo name: ");
    scanf("%s", zoo_name);
    
    for(;;) {
      char feedback = 'n';
      while (feedback != 'y' && feedback != 'n') {
        printf("\nDo you want to add an animal? ");
        scanf("%c", feedabck);
      }
      if (feedback == 'y') {
        addAnimal();
      }
      else if (feedback == 'n') {
        break;
      }
    }
    printf("\nThese are all the animals you added:\n");
  )
  return 0;
}
