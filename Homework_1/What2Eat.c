/*
    Program name: What2Eat.c
    Copyright (C) 2022  Yiğit Demirşan (yigit.demirsan@ozu.edu.tr)
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see https://www.gnu.org/licenses.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUMBER_OF_STRING 5
#define MAX_STRING_SIZE 40

struct Food{
    int score;
    char menuItemNo[50];
};
char *copy_func(char *str1, const char *str2){
    if (str1 == NULL || str2 == NULL )
        return NULL;
    char *temp = str1;
    while ((*str1++ = *str2++) != '\0');
    return temp;
}
int itemNo(int size,struct Food array[]){
    int biggestPoint = 0;
    int index = 0;
    for(int i=0; i<size; i++){
        if(array[i].score == 0)
            break;
        if(array[i].score > biggestPoint){
            biggestPoint = array[i].score;
            index = i;
        }
    }
    return index;
}
int checkList(char* name, struct Food array[], int size){
    for(int i=0; i<size; i++){
        if(array[i].score == 0)
            break;
        if(strcmp(array[i].menuItemNo, name) == 0)
            return i;
    }
    return -1;
}

int position = 0;
void mealAdder(struct Food m,int roommateNo, struct Food array[]){
    if(checkList(m.menuItemNo, array, roommateNo * 5) != -1)
        array[checkList(m.menuItemNo, array, roommateNo * 5)].score += m.score;
    else if(checkList(m.menuItemNo, array, roommateNo * 5) == -1){
        array[position].score = m.score;
        copy_func(array[position].menuItemNo, m.menuItemNo);
        position += 1;
    }
}

int main() {
    const int mealScore = 8;
    int roomMateNo = 0;
    int foundBiggerThanTrashHold = 0;
    char foodList[NUMBER_OF_STRING][MAX_STRING_SIZE] = {"Kebab","Salad","Burger","Lahmacun","Pasta"};
    printf("What2Eat\nRoommate no:\n");
    scanf("%d", &roomMateNo);

    struct Food pointsOfMeals[roomMateNo * 5];
    struct Food pointsOfMealsAboveThresh[roomMateNo * 5];
    struct Food finalList[roomMateNo * 5];

    printf("First round: \n");
    printf("Menu Items are:\n");
    for (int i = 0; i < NUMBER_OF_STRING; ++i) {
        printf("%d-%s\n",i+1,foodList[i]);
    }
    for(int i=0; i < roomMateNo; i++){
        printf("Please Enter number of your favorite food:(1-5)\n");
        struct Food item1;struct Food item2;struct Food item3;struct Food item4;struct Food item5;
        scanf("%s %s %s %s %s", item1.menuItemNo, item2.menuItemNo, item3.menuItemNo, item4.menuItemNo, item5.menuItemNo);
        item1.score = 5;
        item2.score = 4;
        item3.score = 3;
        item4.score = 2;
        item5.score = 1;
        mealAdder(item1,roomMateNo*5, pointsOfMeals);
        mealAdder(item2,roomMateNo * 5, pointsOfMeals);
        mealAdder(item3,roomMateNo * 5, pointsOfMeals);
        mealAdder(item4,roomMateNo * 5, pointsOfMeals);
        mealAdder(item5,roomMateNo * 5,pointsOfMeals);
    }

    for(int i=position; i < roomMateNo * 5; i++){
        pointsOfMeals[i].score = 0;
    }

    position = 0;
    printf("Most preferable food in the menu score is %d: \n", mealScore);
    for(int i=0; i < roomMateNo * 5; i++){
        if(pointsOfMeals[i].score >= mealScore){
            foundBiggerThanTrashHold = 1;
            printf("%s : %d \n", foodList[i], pointsOfMeals[i].score);
            pointsOfMealsAboveThresh[position] = pointsOfMeals[i];
            position += 1;
        }
    }

    for(int i=position; i < roomMateNo * 5; i++){
        pointsOfMealsAboveThresh[i].score = 0;
    }

    position = 0;
    if(foundBiggerThanTrashHold == 0)
        printf("You are eating at home/dorm today! \n");
    else{
        printf("Second round: \n");
        if(sizeof(pointsOfMealsAboveThresh) == 1)
            printf("%s only ordered item", pointsOfMealsAboveThresh[0].menuItemNo);

        for(int i=0; i < roomMateNo; i++){
            printf("Could roommate %d chose it\n", i+1);

            struct Food item6;
            scanf("%s", item6.menuItemNo);
            item6.score = pointsOfMealsAboveThresh[checkList(item6.menuItemNo, pointsOfMealsAboveThresh, roomMateNo * 5)].score;
            mealAdder(item6, roomMateNo * 5, finalList);
        }

        for(int i=position; i < roomMateNo * 5; i++)
            finalList[i].score = 0;
        printf("You're gonna eat number %s chose today have a nice dinner.\n",finalList->menuItemNo);
    }
    return 0;
}
