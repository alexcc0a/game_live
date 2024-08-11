#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

void delete_map(char **map, int x);
void generation(char **map, int x, int y, int &cells);
bool is_gameover(int &cells, bool &null_new_cells);

void copy_temp_map(char **origin_map, char **temp_map, int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            temp_map[i][j] = origin_map[i][j];
        }
    }
}

char **creat_map(int x, int y) {
    char **map = new char *[x];
    for (int i = 0; i < x; i++) {
        map[i] = new char[y];
    }
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            map[i][j] = '-';
        }
    }
    return map;
}

void print_map(char **map, int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
}

void take_live_point(char **map, int &cells, int x, int y) {
    int k, g = 0;

    do {
        std::cout
                << "\nВведите координаты ячейки или напишите -1 -1, "
                   "чтобы выйти из создания ячеек: ";
        std::cin >> k >> g;
        // std::cout << "\x1B[2J\x1B[H"; // Очистка экрана
        std::cout << "\nВы ввели: " << k << " " << g << std::endl;
        if (k <= -1 || g <= -1) {
            std::cout << "\x1B[2J\x1B[H";
            break;
        } else if (k >= x || g >= y)
            std::cout << "\nНеверный индекс, повторите попытку." << std::endl;
        else if (map[k][g] == '-') {
            map[k][g] = '*';
            cells += 1;
            std::cout << "\nЯчейка: " << cells << std::endl;
        } else {
            std::cout << "\nВы уже заполнили эту ячейку" << std::endl;
        }
    } while (true);
}

void live_point_next_move(char **map, char **temp_map, int x, int y, int row,
                          int col, int &cells, bool &new_cells) {
    int counter = 0;
    int maxCol = (y == (col - 1)) ? 1 : 2;
    int maxRow = x == (row - 1) ? 1 : 2;
    int minROw = x == 0 ? 0 : -1;
    int minCol = y == 0 ? 0 : -1;

    for (int i = minROw; i < maxRow; i++) {
        for (int j = minCol; j < maxCol; j++) {
            if (temp_map[x + i][y + j] == '*' && !(j == 0 && i == 0)) {
                ++counter;
            }
        }
    }
    if (temp_map[x][y] == '*' && (counter == 2 || counter == 3)) {
        
    } else if (temp_map[x][y] == '*' && (counter < 2 || 3 < counter)) {
        map[x][y] = '-';
        cells -= 1;
        new_cells = true;
    } else if (temp_map[x][y] == '-' && counter == 3) {
        map[x][y] = '*';
        cells += 1;
        new_cells = true;
    }
}

void pass_cells(char **map, char **temp_map, int x, int y, int &cells,
                bool &new_cells_bool) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            live_point_next_move(map, temp_map, i, j, x, y, cells,
                                 new_cells_bool);
        }
    }
}

void next_move(char **map, int x, int y, int &cells, bool &new_cells_bool) {
    char **temp_map = creat_map(x, y);

    copy_temp_map(map, temp_map, x, y);
    pass_cells(map, temp_map, x, y, cells, new_cells_bool);
    generation(map, x, y, cells);

    delete_map(temp_map, x);
}

void generation(char **map, int x, int y, int &cells) {
    static int count = 0;
    print_map(map, x, y);
    std::cout << "Поколение: " << ++count << " Живые клетки: " << cells
              << std::endl;
}

void end_game(char **map, int x, int &cells, bool &new_cells_bool) {
    if (cells == 0) {
        std::cout << "Все клетки мертвы. Игра закончена" << std::endl;
    } else if (new_cells_bool) {
        std::cout << "Мир застопорился. Игра закончена" << std::endl;
    } else
        std::cout << "Игра закончена. Живые клетки: " << cells << std::endl;

    delete_map(map, x);
}

bool is_gameover(char **map, int x, int &cells, bool &null_new_cells) {
    if (cells == 0 || null_new_cells == false) {
        end_game(map, x, cells, null_new_cells);
        return false;
    } else {
        sleep(4);
        std::cout << "\x1B[2J\x1B[H";
        return true;
    }
}

void delete_map(char **map, int x) {
    for (int i = 0; i < x; i++) {
        delete[] map[i];
    }
    delete[] map;
}

int main() {
    int x, y;
    int cells = 0;
    bool new_cells = false;

    std::cout << "Введите размер карты: ";
    std::cin >> x >> y;
    std::cout << "\x1B[2J\x1B[H";

    char **map = creat_map(x, y);

    take_live_point(map, cells, x, y);
    std::cout << "\x1B[2J\x1B[H";

    generation(map, x, y, cells);
    sleep(4);
    std::cout << "\x1B[2J\x1B[H";

    do {
        new_cells = false;
        next_move(map, x, y, cells, new_cells);
    } while (is_gameover(map, x, cells, new_cells));

    return 0;
}
