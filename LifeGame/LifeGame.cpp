//
// Created by Ali on 26.10.2023.
//

/*

//////////////////////

      LIFE GAME

//////////////////////

*/

/*
в пустой (мёртвой) клетке, с которой соседствуют три живые клетки, зарождается жизнь;
если у живой клетки есть две или три живые соседки, то эта клетка продолжает жить;
в противном случае (если живых соседей меньше двух или больше трёх) клетка умирает («от одиночества» или «от перенаселённости»).
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "windows.h"

int WIDTH = 102, HEIGHT = 27;

void DrawFrame(std::vector<std::vector<char>> map) {
    for (const auto& itMap : map) {
        for (const auto& itVec : itMap) {
            std::cout << itVec;
        }
    }
}

std::vector<std::vector<char>> CalcFrame(std::vector<std::vector<char>> map) {
    auto tempMap = map;
    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 1; j < WIDTH - 1; j++) {
            // Зеркалим координаты если находимся на границе
            int left = (j - 1 == 0) ? WIDTH - 2 : j - 1;
            int top = (i - 1 == 0) ? HEIGHT - 2 : i - 1;
            int right = (j + 1 == WIDTH - 1) ? 1 : j + 1;
            int bottom = (i + 1 == HEIGHT - 1) ? 1 : i + 1;

            // Проверяем всех соседей
            int count = 0;
            if (map[top][left] == '@') count++;
            if (map[top][j] == '@') count++;
            if (map[top][right] == '@') count++;
            if (map[i][left] == '@') count++;
            if (map[i][right] == '@') count++;
            if (map[bottom][left] == '@') count++;
            if (map[bottom][j] == '@') count++;
            if (map[bottom][right] == '@') count++;

            // Жить или не жить
            if (map[i][j] == ' ' && count == 3) {
                tempMap[i][j] = '@';
            }
            if (map[i][j] == '@') {
                if (count < 2 || count > 3) {
                    tempMap[i][j] = ' ';
                }
            }
        }
    }
    return tempMap;
}

int main() {
    std::ifstream myfile("map.txt");
    char ch;
    std::vector<std::vector<char>> map;

    // считываем построчно текстовый файл и записываем в мапу
    std::vector<char> row;
    while (myfile.get(ch)) {
        row.push_back(ch);
        if (ch == '\n') {
            map.push_back(row);
            row.clear();
        }
    }
    map.push_back(row);

    DrawFrame(map); // самый первый фрейм с оригинальной картой
    while (1) {
        Sleep(50);
        printf("\033[H\033[J"); // для очистки консоли

        map = CalcFrame(map); // после каждого расчета меняем оригинальную карту
        DrawFrame(map); // рисуем расчитаную карту
    }


    return 0;
}