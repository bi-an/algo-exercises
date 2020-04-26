#include "PersonBuilder.h"

int main()
{
  PersonThinBuilder thin;
  PersonDirector dirThin(&thin);
  dirThin.CreatePerson();

  PersonFatBuilder fat;
  PersonDirector dirFat(&fat);
  dirFat.CreatePerson();

  return 0;
}