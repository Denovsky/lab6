#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct LINKED_LIST {
  char* info;
  int id;
  struct LINKED_LIST * nextElem;
};
typedef struct LINKED_LIST LL;
typedef char* String;

#define MAX_WORD_SIZE 1024

String ReadInfo();
int AddElemStart(String str);
int AddElemStartId(String str, int id);
int AddElemEnd(String str);
int AddElemEndId(String str, int id);
int AddElemPos(int pos, String str);
int RemoveElemStart();
int RemoveElemEnd();
int RemoveElemInfo(String str);
int RemoveElemId(int id);
int RemoveElemPos(int pos); // pos = id + 1;
int ChangeElem(int id, String str);
int ChoicePos();
int ShowList();
int RequestStop();

int labTask(String str);
int isEquals(String str1, String str2);
int isContain(String str1, String str2);
int strlength(String str);

int setData();
int getData();
int stopFlag = 1;

// int debug();

LL * firstElem = NULL;
int main() {
  srand(time(NULL)); 
  int choice;
  String info;
  while(stopFlag) {
    printf("Выберите действие:\n\t");
    printf("1. Добавить элемент;\n\t");
    printf("2. Удалить элемент;\n\t");
    printf("3. Изменить элемент;\n\t");
    printf("4. Выполнить задание;\n\t");
    printf("5. Работа с данными;\n\t");
    printf("0. Остановка программы.\n\t");
    printf("Введите: ");
    scanf("%d", &choice);
    switch(choice) {
      case 1:
        printf("\n\tСпособ добавления:\n\t\t");
        printf("1. В начало;\n\t\t");
        printf("2. В конец;\n\t\t");
        printf("3. По позиции;\n\t\t");
        printf("0. Назад.\n\t\t");
        printf("Введите: ");
        scanf("%d", &choice);
        fflush(stdin);
        switch(choice) {
          case 1:
            info = ReadInfo();
            AddElemStart(info);
            printf("Добавлено успешно!\n");
            break;
          case 2:
            info = ReadInfo();
            AddElemEnd(info);
            printf("Добавлено успешно!\n");
            break;
          case 3:
            int id1 = ChoicePos("номер позиции");
            info = ReadInfo();
            AddElemPos(id1, info);
            printf("Добавлено успешно!\n");
            break;
          case 0:
            break;
          default:
            printf("Такой команды не существует.");
            break;
        }
        break;
      case 2:
        printf("\n\tСпособ удаления:\n\t\t");
        printf("1. В начале;\n\t\t");
        printf("2. В конце;\n\t\t");
        printf("3. По информации;\n\t\t");
        printf("4. По идентификатору;\n\t\t");
        printf("5. По позиции;\n\t\t");
        printf("0. Назад.\n\t\t");
        printf("Введите: ");
        scanf("%d", &choice);
        fflush(stdin);
        switch(choice) {
          case 1:
            RemoveElemStart();
            printf("Успешно удалено!\n");
            break;
          case 2:
            RemoveElemEnd();
            printf("Успешно удалено!\n");
            break;
          case 3:
            info = ReadInfo();
            RemoveElemInfo(info);
            printf("Успешно удалено!\n");
            break;  
          case 4:
            int id2 = ChoicePos("номер идентификатора");
            RemoveElemId(id2);
            printf("Успешно удалено!\n");
            break;
          case 5:
            int pos = ChoicePos("номер позиции");
            RemoveElemPos(pos);
            printf("Успешно удалено!\n");
            break;
          case 0:
            break;
          default:
            printf("Такой команды не существует.");
            break;
        }
        break;
      case 3:
        int pos = ChoicePos("номер идентификатора");
        info = ReadInfo();
        ChangeElem(pos, info);
        break;
      case 4:
        fflush(stdin);
        info = ReadInfo();
        labTask(info);
        printf("Успешно выполнено!\n");
        break;
      case 5:
        printf("\n\tСпособ работы:\n\t\t");
        printf("1. Сохранить данные в файл;\n\t\t");
        printf("2. Выгрузить данные из файла;\n\t\t");
        printf("0. Назад.\n\t\t");
        printf("Введите: ");
        scanf("%d", &choice);
        fflush(stdin);
        switch(choice) {
          case 1:
            if (!firstElem) {
              printf("Сначала добавьте данные\n");
            } else {
              setData();
              printf("Данные были успешно добавлены\n");
            }
            break;
          case 2:
            getData();
            printf("Данные были успешно добавлены\n");
            break;
          case 0:
            break;
        }
        break;
      case 0:
        printf("Моя остановочка...");
        RequestStop();
        break;
      // case -1:
      //   debug();
      //   break;
      default:
        printf("Такой команды не существует.\n\n");
      }
      ShowList();
  }
  return 0;
}

String ReadInfo() {
  char inf[MAX_WORD_SIZE];
  printf("Enter info: ");
  fgets(inf, sizeof(inf), stdin);
  int i = 0;
  while(inf[i] != '\0') {
    i++;
  }
  String inf1 = (String ) malloc(i);
  i = 0;
  while(inf[i] != '\0') {
    inf1[i] = inf[i];
    i++;
  }
  inf1[i] = '\0';
  return inf1;
}

int AddElemStart(String info) {
  LL * element = (LL *) malloc(sizeof(info) + sizeof(int) + sizeof(LL));
  element->info = info;
  element->id = rand();
  element->nextElem = firstElem;
  firstElem = element;
  return 1;
}

int AddElemStartId(String info, int id) {
  LL * element = (LL *) malloc(sizeof(info) + sizeof(int) + sizeof(LL));
  element->info = info;
  element->id = id;
  element->nextElem = firstElem;
  firstElem = element;
  return 1;
}

int AddElemEnd(String info) {
  LL * element = firstElem;
  LL * lastElem = element;
  int flag = 0;
  while(element) {
    flag = 1;
    lastElem = element;
    element = element->nextElem;
  }
  if (!flag) {
    AddElemStart(info);
  } else {
    LL * element1 = (LL *) malloc(sizeof(info) + sizeof(int) + sizeof(LL));
    element1->info = info;
    element1->id = rand();  
    element1->nextElem = NULL;
    lastElem->nextElem = element1;
  }
  return 1;
}

int AddElemEndId(String info, int id) {
  LL * element = firstElem;
  LL * lastElem = element;
  int flag = 0;
  while(element) {
    flag = 1;
    lastElem = element;
    element = element->nextElem;
  }
  if (!flag) {
    AddElemStartId(info, id);
  } else {
    LL * element1 = (LL *) malloc(sizeof(info) + sizeof(int) + sizeof(LL));
    element1->info = info;
    element1->id = id;  
    element1->nextElem = NULL;
    lastElem->nextElem = element1;
  }
  return 1;
}

int AddElemPos(int pos, String info) {
  int i = 0;
  LL * element = firstElem;
  if(element = NULL) {
    AddElemStart(info);
    return 1;
  }
  while(i != pos-2 && i <= pos-1) {
    element = element->nextElem;
    i++;
  }
  printf("%d ", i);
  LL * posElem = (LL *) malloc(sizeof(info) + sizeof(int) + sizeof(LL));
  posElem->info = info;
  posElem->id = rand();
  posElem->nextElem = element->nextElem;
  element->nextElem = posElem;
  return 1;
}

int RemoveElemStart() {
  LL * element = firstElem;
  firstElem = firstElem->nextElem, free(element);
  return 1;
}

int RemoveElemEnd() {
  LL * element = firstElem;
  LL * prelastElem = element;
  int flag = 0;
  while(element->nextElem) {
    prelastElem = element;
    element = element->nextElem;
    int flag = 1;
  }
  LL * lastElem;
  if(!flag) {
    lastElem = prelastElem->nextElem;
    prelastElem->nextElem = NULL, free(lastElem);
  } else {
    RemoveElemStart();
  }
  return 1;
}

int RemoveElemInfo(String info) {
  LL * element = firstElem;
  LL * yourElement = element;
  int flag = 0;
  int i = 0;
  while(element) {
    i++;
    int statement = isEquals(element->info, info);
    if(statement) {
      flag = 1;
      break;
    }
    yourElement = element;
    element = element->nextElem;
  }
  if(flag && i > 1) {
    yourElement->nextElem = element->nextElem, free(element);
  } else if (flag && i == 1) {
    RemoveElemStart();
  } else {
    printf("Элемента по указанной информации не существует!");
    return 0;
  }
  return 1;
}

int RemoveElemId(int id) {
  LL * element = firstElem;
  LL * yourElement = element;
  int i = 0;
  int flag = 0;
  while(element) {
    i++;
    if(element->id == id) {
      flag = 1;
      break;
    }
    yourElement = element;
    element = element->nextElem;
  }
  if(flag && i > 1) {
    yourElement->nextElem = element->nextElem, free(element);
  } else if (flag && i == 1) {
    RemoveElemStart();
  } else {
    printf("Элемента по указанному идентификатору не существует!");
    return 0;
  }
  return 1;
}

int RemoveElemPos(int pos) {
  LL * element = firstElem;
  LL * yourElement = element;
  int i = 0;
  while(element) {
    yourElement = element;
    element = element->nextElem;
    i++;
  }
  if(i == pos && i >= 2) {
    yourElement->nextElem = element->nextElem, free(element);
  } else if(i == pos && i == 1) {
    RemoveElemStart();
  } else {
    printf("Элемента по указанной позиции не существует!");
    return 0;
  }
  return 1;
}

int ChangeElem(int id, String info) {
  LL * element = firstElem;
  int flag = 0;
  while(element) {
    if(element->id == id) {
      flag = 1;
      element->info = info;
    }
    element = element->nextElem;
  }
  if(!flag) {
    return 0;
  }
  return 1;
}

int ChoicePos(String str) {
  int pos;
  printf("Введите %s: ", str);
  scanf("%d", &pos);
  fflush(stdin);
  return pos;
}

int ShowList() {
  LL * chain = firstElem;
  int i = 1;
  while(chain) {
    printf("\nElement No.%d:", i);
    printf("\n\tInfo - %s\tID - %d\n\n", chain->info, chain->id);
    chain = chain->nextElem;
    i++;
  }
  return 1;
}

int isEquals(String str1, String str2) {
  int i = 0;
  int flag = 0;
  while(str1[i] == str2[i]) {
    if(str1[i] == '\0' && str2[i] == '\0') {
      flag = 1;
    }
    i++;
  }
  return flag;
}

int RequestStop() {
  stopFlag = 0;
  return 1;
}

int labTask(String str) {
  LL * element = firstElem;
  int counter = 0;
  int count_of_print = 0;
  int lettersNum = strlength(str);
  printf("Результат поиска: ");
  while(element) {
    int letterNumInfo = strlength(element->info);
    String info = element->info;
    for(int i = 0; i < letterNumInfo; i++) {
      if(counter == lettersNum) {
        printf("%s", info);
        count_of_print++;
        break;
      }
      if (info[i] == str[counter]) {
        counter++;
      }
    }
    counter = 0;
    element = element->nextElem;
  }
  if (count_of_print == 0) {
    printf("Пусто!");
  }
  return 1;
}

int strlength(String str) {
  int i = 0;
  while(str[i] != '\0' && str[i+1] != '\0') {
    i++;
  }
  return i;
}

int setData() {
  FILE * file = fopen("data.dat", "w");
  LL * element = firstElem;
  while(element) {
      fprintf(file, "%s\n", element->info);
      fprintf(file, "%d\n", element->id);
      element = element->nextElem;
  }
  fclose(file);
  return 1;
}

int getData() {
  FILE * file = fopen("data.dat", "r");
  char str[MAX_WORD_SIZE];
  while (fscanf(file, "%s", &str) == 1) {
    int id;
    fscanf(file, "%d", &id);
    String info;
    int i = 0;
    while (str[i] != '\0') {
      i++;
    }
    i++;
    info = (String) malloc(i+1);
    for (int j = 0; j < i-1; j++) {
      info[j] = str[j];
    }
    info[i-1] = '\n';
    info[i] = '\0';
    AddElemEndId(info, id);
  }
  fclose(file);
  return 1;
}

// int debug() {
//   LL * element = firstElem;
//   while(element) {
//     int i = 0;
//     while(element->info[i] != '\0') {
//       printf("%c", element->info[i]);
//       i++;
//     }
//     printf("%c", element->info[i]);
//     element = element->nextElem;
//   }
//   return 1;
// }