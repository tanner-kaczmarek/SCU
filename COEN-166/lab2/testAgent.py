import unittest
from agent import Vacuum

class Unit_Test(unittest.TestCase):
    def test_1(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.tester(["Dirty", "Dirty"], 0, []), (["Suck", "Right", "Suck"], 3))
    def test_2(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.tester(["Dirty", "Dirty"], 1, []), (["Suck", "Left", "Suck"], 3))
    def test_3(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.tester(["Dirty", "Clean"], 0, []), (["Suck"], 1)) 
    def test_4(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.tester(["Dirty", "Clean"], 1, []), (["Left", "Suck"], 2)) 
    def test_5(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.tester(["Clean", "Dirty"], 0, []), (["Right", "Suck"], 2))
    def test_6(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.tester(["Clean", "Dirty"], 1, []), (["Suck"], 1)) 
    def test_7(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.tester(["Clean", "Clean"], 0, []), ([], 0)) 
    def test_8(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.tester(["Clean", "Clean"], 1, []), ([], 0)) 

if __name__ == '__main__':
    unittest.main()

