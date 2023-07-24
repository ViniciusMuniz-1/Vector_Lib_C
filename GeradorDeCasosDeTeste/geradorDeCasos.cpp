#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int random_number(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main() {
    int min_range = 0;
    int max_range = 140000000;

    int size = 140000000;

    int* array = new int[size];

    srand(time(0));

    for (int i = 0; i < size; i++) {
        array[i] = random_number(min_range, max_range);
    }

    std::ofstream file("CasosCasa100Milhões/caso_de_teste_140000000.txt");

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    file << size << std::endl;

    for (int i = 0; i < size; i++) {
        file << array[i] << " ";
    }

    file.close();

    delete[] array;

    return 0;
}