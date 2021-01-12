import sys
import unittest


class Vacuum:

    def runAction(self, state, location):
        cost = 0
        actions = []
        while True:  #While loop until returns the sequence of actions as well as the cost
            if state == ["Clean", "Clean"]:
                print("The cost of Cleaning was ", cost, "\n")
                print("The actions were ", actions, "\n")
                print("--------------------------------\n")
                return actions, cost
            action, state, location = self.action(state, location)
            cost += 1  #action happened last time so time to add the cost
            actions.append(action)  
    
    def action(self, state, location):
        if state[location] == "Dirty":  #dirty so suck and then set location to clean
            action = "Suck"
            state[location] = "Clean"
            return action, state, location
        elif location == 0:  #left side is clean so move to the left
            action = "Right"
            location = 1
            return action, state, location
        elif location == 1:   #right side is clean so move to the right
            action = "Left"
            location = 0
            return action, state, location

#Runs through all the test cases
class Unit_Test(unittest.TestCase):
    def test_1(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.runAction(["Dirty", "Dirty"], 0), (["Suck", "Right", "Suck"], 3))
    def test_2(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.runAction(["Dirty", "Dirty"], 1), (["Suck", "Left", "Suck"], 3))
    def test_3(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.runAction(["Dirty", "Clean"], 0), (["Suck"], 1)) 
    def test_4(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.runAction(["Dirty", "Clean"], 1), (["Left", "Suck"], 2)) 
    def test_5(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.runAction(["Clean", "Dirty"], 0), (["Right", "Suck"], 2))
    def test_6(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.runAction(["Clean", "Dirty"], 1), (["Suck"], 1)) 
    def test_7(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.runAction(["Clean", "Clean"], 0), ([], 0)) 
    def test_8(self):
        vacuuming1 = Vacuum()
        self.assertEqual(vacuuming1.runAction(["Clean", "Clean"], 1), ([], 0)) 

if __name__ == '__main__':
    unittest.main()
