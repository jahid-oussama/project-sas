#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include <windows.h>

struct product {
  char code[20];
  char name[20];
  int quantity;
  float price;
  char time[64];
};

struct product products[400];

int chosenItem, numberOfProducts = 0;
float moy;
float totalprice = 0;
float numberOfProductsbuy = 0;
float Max = 0;
float Min = 0;
// PROTOTYPES
void SetColor(int ForgC);
void add_product();
void add_multiple_products();
void show_a_list_of_product();
void show_a_list_of_product_byprice();
void show_a_list_of_product_byname();
void buy_product();
void search_for_a_product();
void search_for_a_product_bycode();
void search_for_a_product_byquntity();
void stock_status();
void Supply_the_stock();
void delete_a_product();
void show_status();

void show_menu() {

  do {

    system("cls");
    SetColor(3);
    printf("\n\t                         ---  Welcome to Pharmacie  ---\n");
    printf("\n\t                      ---  You are  in the first menu  ---\n");
    printf("\n\t             ---  Please choose what do you want from the menu  ---\n\n");
    //printf("You are  in the first menu \n");
    SetColor(7);
    //printf("Please choose what do you want from the menu :\n");
    // system("Color 9");
    printf("->[1].Add a product \n->[2].add multiple products \n->[3].Show a list of product \n->[4].Buy a product \n->[5].Search for a product \n->[6].Stock status \n->[7].Supply the stock \n->[8].Delete a product \n->[9].Show statistics \n");
    scanf("%d", & chosenItem);

  } while (chosenItem > 9);

  switch (chosenItem) {
  case 1:
      system("cls");
    printf("         ~ 1.Add a product ~ \n\n");
    add_product();
    show_menu();
    break;
  case 2:
    add_multiple_products();
    show_menu();
    break;
  case 3:
    show_a_list_of_product();
     show_menu();
    break;
  case 4:
    buy_product();
    show_menu();
    break;
  case 5:
    search_for_a_product();
    break;
  case 6:
    stock_status();
    show_menu();
    break;
  case 7:
    Supply_the_stock();
    show_menu();
    break;
  case 8:
    delete_a_product();
    show_menu();
    break;
  case 9:
    show_status();
    show_menu();
    break;
  default:
    printf("Please choose from the menu! \n");
    show_menu();
    break;
  }
}

int main() {

  show_menu();
}

void add_product() {
  system("cls");
  printf("1.Add a product \n");
  printf("->[0].Back  \nEnter your code \n->");

  scanf("%s", products[numberOfProducts].code);
if (strlen(products[numberOfProducts].code) == 1 && products[numberOfProducts].code[0]=='0')//VARIABLE
{
     show_menu();
}

  printf("Enter the name \n");
  scanf("%s", products[numberOfProducts].name);

  printf("Quantity \n");
  scanf("%d", & products[numberOfProducts].quantity);

  printf("Price (DH)\n");
  scanf("%f", & products[numberOfProducts].price);

  numberOfProducts++;

}

void add_multiple_products() {
  int inputNumber;
  system("cls");
  printf("               ~ 2.Add multiple products ~ \n\n");
  printf("->[0].Back  \nEnter how many product you want to add  \n->");
  scanf("%d", & inputNumber);

  for (int i = 1; i <= inputNumber; i++) {
    add_product();
  }
}

void show_a_list_of_product() {
  int list;
  system("cls");
  printf("               ~ 3.show a list of product  (name , prix, prix TTC) ~  \n\n");
  printf("->[0].Back  \n->[1].List all products in ascending alphabetical order by name. \n->[2].Lister tous les produits selon l’ordre decroissant du prix. \n->");
  scanf("%d", & list);
  if (list == 2) {
    show_a_list_of_product_byprice();
  }
  else if (list == 1) {
    show_a_list_of_product_byname();
  }
  else
    {
        show_menu();
    }
  system("Pause");
}

void show_a_list_of_product_byprice() {

  for (int j = 0; j < numberOfProducts; j++) {
    for (int k = j + 1; k < numberOfProducts; k++) {
      if (products[j].price < products[k].price) {
        struct product ch;
        ch = products[k];
        products[k] = products[j];
        products[j] = ch;
      }
    }
  }
  for (int j = 0; j < numberOfProducts; j++) {
    printf("Code: %s| Name: %s |Quntity: %d| Price: %.2f | Price TTC: %.2f |\n", products[j].code, products[j].name, products[j].quantity, products[j].price, products[j].price * 1.15);
  }
  system("Pause");
  show_menu();
}
void show_a_list_of_product_byname() {
  for (int j = 0; j < numberOfProducts; j++) {
    for (int k = j + 1; k < numberOfProducts; k++) {
      if (strcasecmp(products[j].name, products[k].name) > 0) {
        struct product ch;
        ch = products[j];
        products[j] = products[k];
        products[k] = ch;
      }
    }
  }

  for (int j = 0; j < numberOfProducts; j++) {
    printf("Code: %s| Name: %s |Quntity: %d| Price: %.2f | Price TTC: %.2f |\n", products[j].code, products[j].name, products[j].quantity, products[j].price, products[j].price * 1.15);
  }
  system("Pause");
  show_menu();
}
void buy_product() {
  system("cls");
  int k=1;
  printf("         ~ 4.buy a product ~ \n\n");

  char tmpCode[20];

  printf("give the code : \n->");
  scanf("%s", tmpCode);

  for (int i = 0; i < numberOfProducts; i++) {
    if (strcmp(products[i].code, tmpCode) == 0) {
        k=0;
      printf("the product you are about to buy is %s and the quantity is: %d\n", products[i].name, products[i].quantity);
      int tmpQantity = 0;
      printf("give the quantity you want to buy: ");
      scanf("%d", & tmpQantity);
      if (tmpQantity <= products[i].quantity) {
        totalprice = totalprice + (products[i].price * tmpQantity);
        products[i].quantity = products[i].quantity - tmpQantity;
        numberOfProductsbuy += tmpQantity;
        ///showing time
        time_t t = time(NULL);
        struct tm * tm = localtime( & t);
        size_t ret = strftime(products[numberOfProducts].time, sizeof(products[numberOfProducts].time), "%c", tm);
        assert(ret);

        if (products[i].price > Max) {
          Max = products[i].price;
        }
        if (products[i].price < Min || Min == 0) {
          Min = products[i].price;
        }
       printf("your product quantity now is %d and the time is %s \n",products[i].quantity,products[i].time);
      } else
        printf("quantity is not avalaible\n");
    }
    }
    if(k==1)
        {
      printf("code doesn't match no product\n");
        }
        system("Pause");
  }

void search_for_a_product() {
  int search = 0;
  tryagain:
    system("cls");
  printf("         ~ 5.search for a product ~\n\n");
  printf("->[0].Back  \n->[1].Search  Code \n->[2].Search Quantite.\n->");
  scanf("%d", & search);

  if (search == 1) {
    search_for_a_product_bycode();

  } else if (search == 2) {

    search_for_a_product_byquntity();
  }
  else if (search == 0)
  {
      show_menu();
  }
  else {
    printf("Please enter the right number 0 or 1 or 2  \n");
    system("Pause");
    goto tryagain;
  }
  system("Pause");
}

void search_for_a_product_bycode() {
  system("cls");
  char tmpCode[20];
  int
  var = 1;
  printf("Please enter the product code :  \n ");
  scanf("%s", tmpCode);
  for (int i = 0; i < numberOfProducts; i++) {
    if (strcmp(products[i].code, tmpCode) == 0) {
      printf("Code: %s| Name: %s |Quantity: %d| Price: %.2f | Price TTC: %.2f |\n", products[i].code, products[i].name, products[i].quantity, products[i].price, products[i].price * 1.15);
      var = 0;
      break;
    }
  }
  if (var == 1)
    printf("code doesn't match no product\n");

  system("Pause");
  show_menu();
}

void search_for_a_product_byquntity() {
  system("cls");
  int tmpquantity, k = 1;
  printf("Please enter the product quantity :  \n ");
  scanf("%d", & tmpquantity);

  for (int i = 0; i < numberOfProducts; i++) {
    if (products[i].quantity == tmpquantity) {
      k = 0;
      printf("Code: %s| Name: %s |Quntity: %d| Price: %.2f | Price TTC: %.2f |\n", products[i].code, products[i].name, products[i].quantity, products[i].price, products[i].price * 1.15);
    }
  }
  if (k == 1) {
    printf("code doesn't match no product\n");
  }
  system("Pause");
  show_menu();
}
void stock_status() {
  int a;
  system("cls");
  printf("           ~ 6.stock status ~ \n\n");
  printf("->[0].Back  \nHere is a list of product  where quantity <3.\n");
  for (int i = 0; i < numberOfProducts; i++) {
    if (products[i].quantity <= 3) {
      printf("Code: %s| Name: %s |Quntity: %d| Price: %.2f | Price TTC: %.2f |\n", products[i].code, products[i].name, products[i].quantity, products[i].price, products[i].price * 1.15);
    }
  }
  system("Pause");
}

void Supply_the_stock() {
  system("cls");
  int a=1;
  char tmpCode[20];
  printf("        ~ 7.Supply the stock ~\n\n");
  printf("->[0].Back  \nEnter product  the code \n->");
  scanf("%s", tmpCode);

  for (int i = 0; i < numberOfProducts; i++) {
    if (strcmp(products[i].code, tmpCode) == 0)
        {
            a=0;
              printf("the product you are about to SUPPLY is %s and the quantity is: %d\n", products[i].name, products[i].quantity);
              int tmpQantity = 0;
              printf("give the quantity you want to SUPPLY: ");
              scanf("%d", & tmpQantity);
              if (tmpQantity > 0) {
                products[i].quantity = products[i].quantity + tmpQantity;
              } else
            printf("quantity not avalaible\n");
        }
  }
   if(a==1)
        {
      printf("code doesn't match no product\n");
    }
    system("Pause");
}

void delete_a_product() {
  system("cls");
  printf("        ~ 8.delete a product ~\n\n");
  char tmpCode[20];
  int tmpindex = -1;
  printf("->[0].Back  \nEnter the product code  \n->");
  scanf("%s", tmpCode);

  for (int i = 0; i < numberOfProducts; i++) {
    if (strcmp(products[i].code, tmpCode) == 0) {
      tmpindex = i;
      break;
    }
  }
  if (tmpindex == -1) {
    printf("this code is not good");
  } else {
    for (int i = tmpindex; i < numberOfProducts; i++) {

      products[i] = products[i + 1];
    }
    numberOfProducts--;
  }
}

void show_status() {
    if(numberOfProductsbuy!=0)
       {
            moy = totalprice / numberOfProductsbuy;
       }
  system("cls");
  printf("          ~ 9.show_status ~ \n\n\n");
  printf("the total prices of the products sold on the current day : %.2f\n", totalprice);
  printf("the average price of products sold on the current day : %.2f\n", moy);
  printf("the Max of the prices of the products sold on the current day  : %.2f\n", Max);
  printf("the Min of the prices of the products sold on the current day :  %.2f\n\n", Min);

  system("Pause");

}
void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
}
