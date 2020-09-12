'''Реализовать 4 алгоритма поиска расстояний'''

import random
import string
import time


def print_matrix(matr):
    for i in range(len(matr)):
        for j in range(len(matr[0])):
            print(matr[i][j], end = '')
        print()
    print()

def LevMatrix(s1, s2):
    n = len(s1) + 1
    m = len(s2) + 1
    matrix = [[i + j for j in range(m)] for i in range(n)]

    for i in range(1, n):
        for j in range(1, m):
            const = 0 if (s1[i - 1] == s2[j - 1]) else 1

            matrix[i][j] = min(matrix[i][j - 1] + 1,
                               matrix[i - 1][j] + 1,
                               matrix[i - 1][j - 1] + const)

    return matrix[n - 1][m - 1]

def LevRecursion_process(s1, s2, len1, len2):
    if len1 == 0 or len2 == 0:
        return abs(len1 - len2)

    const = 0 if (s1[len1 - 1] == s2[len2 - 1]) else 1
    return min(LevRecursion_process(s1, s2, len1, len2 - 1) + 1,
               LevRecursion_process(s1, s2, len1 - 1, len2 - 1) + const,
               LevRecursion_process(s1, s2, len1 - 1, len2) + 1)

def LevRecursion(s1, s2):
    return LevRecursion_process(s1, s2, len(s1), len(s2))

def LevMatrixRecursion_process(matrix, i, j, s1, s2):
    if i + 1 < len(matrix) and j + 1 < len(matrix[0]):
        const = 0 if s1[i] == s2[j] else 1
        if matrix[i + 1][j + 1] > matrix[i][j] + const:
            matrix[i + 1][j + 1] = matrix[i][j] + const
            LevMatrixRecursion_process(matrix, i + 1, j + 1, s1, s2)

    if j + 1 < len(matrix[0]) and matrix[i][j + 1] > matrix[i][j] + 1:
        matrix[i][j + 1] = matrix[i][j] + 1
        LevMatrixRecursion_process(matrix, i, j + 1, s1, s2)

    if i + 1 < len(matrix) and matrix[i + 1][j] > matrix[i][j] + 1:
        matrix[i + 1][j] = matrix[i][j] + 1
        LevMatrixRecursion_process(matrix, i + 1, j, s1, s2)

def LevMatrixRecursion(s1, s2):
    n = len(s1) + 1
    m = len(s2) + 1
    max_len = max(n, m)

    matrix = [[max_len for j in range(m)] for i in range(n)]
    matrix[0][0] = 0

    LevMatrixRecursion_process(matrix, 0, 0, s1, s2)

    return matrix[-1][-1]

def DamLev(s1, s2):
    n = len(s1) + 1
    m = len(s2) + 1

    matrix = [[0] * m for i in range(n)]

    for j in range(m):
        matrix[0][j] = j

    for i in range(n):
        matrix[i][0] = i

    for i in range(1, n):
        for j in range(1, m):
            const = 0 if (s1[i - 1] == s2[j - 1]) else 1

            matrix[i][j] = min(matrix[i][j - 1] + 1,
                               matrix[i - 1][j] + 1,
                               matrix[i - 1][j - 1] + const)

            if i > 1 and j > 1:
                if s1[i - 1] == s2[j - 2] and s2[j - 1] == s1[i - 2]:
                    matrix[i][j] = min(matrix[i][j - 1] + 1,
                                       matrix[i - 1][j] + 1,
                                       matrix[i - 1][j - 1] + const,
                                       matrix[i - 2][j - 2] + 1)

    return matrix[n - 1][m - 1]

def RandomString(number):
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(number))


def TestTime(function, s1, s2):
    time_start = time.process_time()
    num_oper = 0
    while time.process_time() - time_start < 1:
        function(s1, s2)
        num_oper += 1

    result_time = time.process_time() - time_start

    print("Выполнено {:} операций, затрачено {:} секунд".format(num_oper, result_time))
    print("Время: {:.4} секунд".format(result_time / num_oper))
    print()

def MeasureTime():
    length = [4, 6, 8, 10, 12, 14]

    for i in range(len(length)):
        print("\n--------------------------------------------------------------------------------")
        len1 = random.choice(length)
        len2 = random.choice(length)

        s1 = RandomString(len1)
        s2 = RandomString(len2)

        print(">>> Сгенерированная строка 1: ", s1)
        print(">>> Сгенерированная строка 2: ", s2)

        print("\n---Расстояние Левенштейна (матрица)---")
        TestTime(LevMatrix, s1, s2)
        print("---Расстояние Левенштейна (рекурсия)---")
        TestTime(LevRecursion, s1, s2)
        print("---Расстояние Левенштейна (матрица + рекурсия)---")
        TestTime(LevMatrixRecursion, s1, s2)
        print("---Расстояние Дамерау-Левенштейна (матрица)---")
        TestTime(DamLev, s1, s2)


def main():
    str1 = input("Введите строку 1: ")
    str2 = input("Введите строку 2: ")

    while True:
        choice = input("\nMENU\n"
                       "1. Расстояние Левенштейна (матрица)\n"
                       "2. Расстояние Левенштейна (рекурсия)\n"
                       "3. Расстояние Левенштейна (матрица + рекурсия)\n"
                       "4. Расстояние Дамерау-Левенштейна (матрица)\n"
                       "5. Тестирование: время\n"
                       "\n Ваш выбор: ")

        if choice == "1":
            print("\nМинимальное расстояние: ", LevMatrix(str1, str2))
        elif choice == "2":
            print("\nМинимальное расстояние: ", LevRecursion(str1, str2))
        elif choice == "3":
            print("\nМинимальное расстояние: ", LevMatrixRecursion(str1, str2))
        elif choice == "4":
            print("\nМинимальное расстояние: ", DamLev(str1, str2))
        elif choice == "5":
            MeasureTime()

if __name__ == "__main__":
    main()