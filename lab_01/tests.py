import unittest
import main

# Общие для всех алгоритмов тесты
class GeneralTest(unittest.TestCase):
    @unittest.skip("General Tests were skipped")
    def setUp(self):
        self.function = None

    # Обработка пустых строк
    def test_empty_str(self):
        self.assertEqual(self.function("", ""), 0)
        self.assertEqual(self.function("", "12345"), 5)
        self.assertEqual(self.function("98765", ""), 5)

    # Совпадающие строки
    def test_match(self):
        self.assertEqual(self.function("1", "1"), 0)
        self.assertEqual(self.function("12qw", "12qw"), 0)
        self.assertEqual(self.function("AbC", "AbC"), 0)
        self.assertEqual(self.function("Abc", "abc"), 1)

    # Простые тесты
    def test_easy(self):
        self.assertEqual(self.function("1", "2"), 1)
        self.assertEqual(self.function("123", "1"), 2)
        self.assertEqual(self.function("1", "123"), 2)
        self.assertEqual(self.function("a", "ab"), 1)
        self.assertEqual(self.function("ab", "a"), 1)
        self.assertEqual(self.function("a5c", "abc"), 1)

# Тесты для алгоритма поиска расстояния Левенштейна
class LevTest(GeneralTest):
    def test_lev(self):
        self.assertEqual(self.function("тело", "столб"), 3)
        self.assertEqual(self.function("увлечение", "развлечения"), 4)
        self.assertEqual(self.function("касаться", "опасаться"), 2)
        self.assertEqual(self.function("abccde", "cdeabc"), 6)

# Тесты для алгоритма поиска расстояния Дамерау-Левенштейна
class DemLevTest(GeneralTest):
    def setUp(self):
        self.function = main.DamLev

    # Тесты на поиск транспозиций
    def test_demlev(self):
        self.assertEqual(self.function("qw", "wq"), 1)
        self.assertEqual(self.function("132", "123"), 1)
        self.assertEqual(self.function("1001", "0110"), 2)
        self.assertEqual(self.function("2143", "1234"), 2)

# Все алгоритмы поиска расстояния Левенштейна проходят не только
# общие тесты, но и специально написанные LevTest

# Алгоритм поиска расстояния Левенштейна (матричный)
class LevMatrixTest(LevTest):
    def setUp(self):
        self.function = main.LevMatrix

# Алгоритм поиска расстояния Левенштейна (рекурсия)
class LevRecursionTest(LevTest):
    def setUp(self):
        self.function = main.LevRecursion

# Алгоритм поиска расстояния Левенштейна (матрица + рекурсия)
class LevMatrixRecursionTest(LevTest):
    def setUp(self):
        self.function = main.LevMatrixRecursion


# Запуск тестов
if __name__ == "__main__":
    unittest.main()
