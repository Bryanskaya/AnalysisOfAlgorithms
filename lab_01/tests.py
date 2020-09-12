import unittest
import main

class GeneralTest(unittest.TestCase):
    @unittest.skip("General Tests were skipped")
    def setUp(self):
        self.function = None

    def test_empty_str(self):
        self.assertEqual(self.function("", ""), 0)
        self.assertEqual(self.function("", "12345"), 5)
        self.assertEqual(self.function("98765", ""), 5)

    def test_match(self):
        self.assertEqual(self.function("1", "1"), 0)
        self.assertEqual(self.function("12qw", "12qw"), 0)
        self.assertEqual(self.function("AbC", "AbC"), 0)

    def test_easy(self):
        self.assertEqual(self.function("1", "2"), 1)
        self.assertEqual(self.function("123", "1"), 2)
        self.assertEqual(self.function("1", "123"), 2)
        self.assertEqual(self.function("a", "ab"), 1)
        self.assertEqual(self.function("ab", "a"), 1)
        self.assertEqual(self.function("a5c", "abc"), 1)

class LevTest(GeneralTest):
    def test_lev(self):
        self.assertEqual(self.function("тело", "столб"), 3)
        self.assertEqual(self.function("увлечение", "развлечения"), 4)
        self.assertEqual(self.function("касаться", "опасаться"), 2)
        self.assertEqual(self.function("abccde", "cdeabc"), 6)

class DemLevTest(GeneralTest):
    def setUp(self):
        self.function = main.DamLev

    def test_demlev(self):
        self.assertEqual(self.function("qw", "wq"), 1)
        self.assertEqual(self.function("132", "123"), 1)
        self.assertEqual(self.function("1001", "0110"), 2)
        self.assertEqual(self.function("2143", "1234"), 2)

class LevMatrixTest(LevTest):
    def setUp(self):
        self.function = main.LevMatrix

class LevRecursionTest(LevTest):
    def setUp(self):
        self.function = main.LevRecursion

class LevMatrixRecursionTest(LevTest):
    def setUp(self):
        self.function = main.LevMatrixRecursion

def tests():
    unittest.main()

if __name__ == "__main__":
    tests()