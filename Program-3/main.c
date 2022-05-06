/// NAME: Tadas Baltrūnas
/// Group: 5
/// PROGRAM NR: 12
/// 2022.05
//--------------------------------------------------------
#include "header.h"
//--------------------------------------------------------
typedef struct WarehouseData
{
    int amount;
    int cost;
    float amountDeviation;
    float costDeviation;
    float surcharge;

} WarehouseData;
//--------------------------------------------------------
time_t t;
WarehouseData data;
int days;
//--------------------------------------------------------
void getDataFromFile()
{
    FILE *opener;

    opener = fopen("data.txt", "r");
    if(opener == NULL)
    {
        printf("ERROR: can't open data file");
    }
    fscanf(opener, "%d %f %d %f %f %d", &data.amount, &data.amountDeviation, &data.cost, &data.costDeviation, &data.surcharge, &days);
}
//--------------------------------------------------------
int getValueWithDeviation(int value, int error)
{
    int amount = value * error /  100;
    int e = rand() % (2 * amount + 1);
    return value + (e - amount);
}
//--------------------------------------------------------
int allStorageCost(StackNode *amount, StackNode *price)
{
    int x=0;

    while(amount != NULL && price != NULL)
    {
        x += (amount->data * price->data);
        amount = amount->next;
        price = price->next;
    }
    return x;
}
//--------------------------------------------------------
int main()
{
        srand(time(&t));

    int grainStorageFIFO = 0;
    int moneyStorageFIFO = 0;
    int grainStorageLIFO = 0;
    int moneyStorageLIFO = 0;
//--------------------------------------------------------
    Stack *amountS = (Stack*)malloc(sizeof(Stack));
    Stack *priceS = (Stack*)malloc(sizeof(Stack));
    *amountS = createStack();
    *priceS = createStack();
    if(amountS == NULL || priceS == NULL)
    {
        printf("ERROR: can't create stack");
        return 1;
    }
//--------------------------------------------------------
    Queue *amountQ = (Queue*)malloc(sizeof(Stack));
    Queue *priceQ = (Queue*)malloc(sizeof(Stack));
    createQueue(amountQ);
    createQueue(priceQ);
    if(amountQ == NULL || priceQ == NULL)
    {
        printf("ERROR: can't create queue");
        return 1;
    }
//--------------------------------------------------------
    getDataFromFile();
    printf("Company buys: %d tons of grains\nFor 1 ton of grain company pays: %d euros\nMaximal deviation of purchased grain amount: %.f%%\nMaximal deviation of the purchased grain price: %.f%%\nSurcharge: %.f%%\nNumber of days: %d\n\n", data.amount, data.cost, data.amountDeviation, data.costDeviation, data.surcharge, days);
//--------------------------------------------------------
    int costFrom, costTo, amountFrom, amountTo;
    costFrom = data.cost - (data.cost * (data.costDeviation/100));
    costTo   = data.cost + (data.cost * (data.costDeviation/100));
    amountFrom = data.amount - (data.amount * (data.amountDeviation/100));
    amountTo   = data.amount + (data.amount * (data.amountDeviation/100));
    printf("Because of the deviation company will:\nPurchase grain from %d to %d tons\nPurchase grain from %d to %d euros for ton\n\n", amountFrom, amountTo, costFrom, costTo);
//--------------------------------------------------------
    for(int i=1; i<=days; i++)
    {
        int todayBuyAmount = getValueWithDeviation(data.amount, data.amountDeviation);
        int todayBuyPrice  = getValueWithDeviation(data.cost, data.costDeviation);

        enqueue(amountQ, todayBuyAmount);
        enqueue(priceQ, todayBuyPrice);
        push(amountS, todayBuyAmount);
        push(priceS, todayBuyPrice);

        printf("____Day: %d\n\nToday buy amount: %d\nToday buy price:  %d\n------------------------\n", i, todayBuyAmount, todayBuyPrice);
        printf("Queue: \n");
        printQueue(amountQ->head);
        printQueue(priceQ->head);
        printf("Stack: \n");
        printStack(amountS->head);
        printStack(priceS->head);
        //--------------------------------------------------------
        grainStorageLIFO = sumStack(amountS->head);
        moneyStorageLIFO -= todayBuyAmount * todayBuyPrice;
        grainStorageFIFO = sumQueue(amountQ->head);
        moneyStorageFIFO -= todayBuyAmount * todayBuyPrice;

        printf("FIFO Money Storage: %d\nLIFO Money Storage: %d\n------------------------\n", moneyStorageFIFO, moneyStorageLIFO);
        //--------------------------------------------------------
        float todaySellPercent = rand()%100; // Should be rand()%101, because other way todaySellPercent will never be 100 (bug)
        int todaySellAmountLIFO  = sumStack(amountS->head) * (todaySellPercent/100);
        int todaySellAmountFIFO  = sumQueue(amountQ->head) * (todaySellPercent/100);
        int todaySellPriceFIFO   = priceQ->head->x + (priceQ->head->x*data.surcharge/100);
        int todaySellPriceLIFOwithoutSurcharge = allStorageCost(amountS->head, priceS->head) / sumStack(amountS->head);
        int todaySellPriceLIFO = todaySellPriceLIFOwithoutSurcharge * (1 + data.surcharge/100);

        printf("Today sell percent: %.1f\nToday sell amount: %d\nFIFO Today sell price:  %d\nLIFO Today sell price:  %d\n------------------------\n", todaySellPercent, todaySellAmountLIFO, todaySellPriceFIFO, todaySellPriceLIFO);
        //--------------------------------------------------------
        if(amountS->head->data - todaySellAmountLIFO > 0)
        {
            amountS->head->data -= todaySellAmountLIFO;
            moneyStorageLIFO += todaySellAmountLIFO*todaySellPriceLIFO;
        }
        else if(amountS->head->data - todaySellAmountLIFO == 0)
        {
            amountS->head->data -= todaySellAmountLIFO;
            moneyStorageLIFO += todaySellAmountLIFO*todaySellPriceLIFO;
            pop(amountS);
            pop(priceS);
        }
        else
        {
            double totalIncome = 0;
            int balance = todaySellAmountLIFO;
            while(amountS->head->data <= todaySellAmountLIFO)
            {
                totalIncome += amountS->head->data * allStorageCost(amountS->head, priceS->head) / sumStack(amountS->head) * (1 + data.surcharge/100);
                todaySellAmountLIFO -= amountS->head->data;
                amountS->head->data -= balance;
                balance = abs(amountS->head->data);
                pop(amountS);
                pop(priceS);

                if(isEmpty(amountS) || isEmpty(priceS))
                {
                    push(amountS, 0);
                    push(priceS, 0);
                }
            }
            amountS->head->data -= balance;
            totalIncome += balance * allStorageCost(amountS->head, priceS->head) / sumStack(amountS->head) * (1 + data.surcharge/100);
            moneyStorageLIFO += totalIncome;
        }
        //--------------------------------------------------------
        if(amountQ->head->x - todaySellAmountFIFO > 0)
        {
            amountQ->head->x -= todaySellAmountFIFO;
            moneyStorageFIFO += todaySellAmountFIFO*todaySellPriceFIFO;
        }
        else if(amountQ->head->x - todaySellAmountFIFO == 0)
        {
            amountQ->head->x -= todaySellAmountFIFO;
            moneyStorageFIFO += todaySellAmountFIFO*todaySellPriceFIFO;
            dequeue(amountQ);
            dequeue(priceQ);
        }
        else
        {
            int balance = todaySellAmountFIFO;
            while(amountQ->head->x <= todaySellAmountFIFO)
            {
                moneyStorageFIFO += amountQ->head->x * priceQ->head->x * (1 + data.surcharge/100);
                todaySellAmountFIFO -= amountQ->head->x;
                amountQ->head->x -= balance;
                balance = abs(amountQ->head->x);
                dequeue(amountQ);
                dequeue(priceQ);
            }
            amountQ->head->x -= balance;
            moneyStorageFIFO += balance * priceQ->head->x * (1 + data.surcharge/100);
        }
        //--------------------------------------------------------
        grainStorageFIFO = sumQueue(amountQ->head);
        grainStorageLIFO = sumStack(amountS->head);

        printf("Queue: \n");
        printQueue(amountQ->head);
        printQueue(priceQ->head);
        printf("Stack: \n");
        printStack(amountS->head);
        printStack(priceS->head);

        printf("FIFO Money Storage: %d\nLIFO Money Storage: %d\n------------------------\n", moneyStorageFIFO, moneyStorageLIFO);
        //--------------------------------------------------------
    }
//--------------------------------------------------------
    printf("\nCompany has worked for %d days:\nBy using FIFO method company gained approximately: %d\nBy using LIFO method company gained approximately: %d\n", days, moneyStorageFIFO, moneyStorageLIFO);

    if(moneyStorageFIFO > moneyStorageLIFO)
    {
        printf("The FIFO method was better and brought %d more money than LIFO method\n", moneyStorageFIFO-moneyStorageLIFO);
    }
    else
    {
        printf("The LIFO method was better and brought %d more money than FIFO method\n", moneyStorageLIFO-moneyStorageFIFO);
    }
//--------------------------------------------------------
    deleteStack(amountS);
    deleteStack(priceS);
    destroyQueue(amountQ);
    destroyQueue(priceQ);
    return 0;
}

/*
12. Grūdų sandėlis (ADT: stekas, eilė).

Įmonė aktyviai prekiauja grūdais.
Kiekvieną dieną įmonė perka ir sandėliuoja grūdus bei juos parduoda (atsitiktinai nuo 0 iki 100% sandėlyje turimų grūdų).

Yra nustatyta
- per dieną superkamų grūdų norma (pvz., 100 t)
- supirkimo kaina (pvz., 200 LT/t),
bet natūralu, kad ne visomis dienomis vienodai sekasi,
todėl ekspertiškai žinomas
- superkamų grūdų kiekio maksimalus nuokrypis
(pvz., 15%, tai reiškia, kad kiekvieną dieną įmonė superka 85-115 t grūdų) ir
- maksimalus grūdų supirkimo kainos nuokrypis
(pvz., 5%, tai reiškia, kad įmonė superka gūdus po 190-210 LT/t).
Parduodama grūdus įmonė ima
- nustatytą antkainį (pvz., 10%) nuo apskaitinės grūdų kainos.

Gali būti naudojami tokie atsargų apskaitos metodai:
1) FIFO supirkimo: pirmiausia parduodami seniausiai įsigyti grūdai, apskaitinė grūdų kaina lygi supirkimo kainai;
2) LIFO svertinių vidurkių: pirmiausia parduodami šviežiausi grūdai;

apskaitinė gautų grūdų kaina nustatoma kaip tuo metu sandėlyje turimų grūdų kainų svertinis vidurkis
(pvz., jei sandėlyje turėjome 200 t grūdų, kurių apskaitinė kaina 95 LT/t ir įsigijome dar 100 t po 110 LT/t,
tai įsigytų grūdų apskaitinė kaina yra 100 LT/t = (200 * 95 + 100 * 110) / (200 + 100)).

Tikslas: patyrinėti, kurį grūdų apskaitos metodą naudodama įmonė gauna didesnį pelną.
*/
