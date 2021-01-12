# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util
import sys
import copy

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def goalTest(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getActions(self, state):
        """
        Given a state, returns available actions.
        Returns a list of actions
        """        
        util.raiseNotDefined()

    def getResult(self, state, action):
        """
        Given a state and an action, returns resulting state.
        """
        util.raiseNotDefined()

    def getCost(self, state, action):
        """
        Given a state and an action, returns step cost, which is the incremental cost 
        of moving to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()

class Node:
    """
    Search node object for your convenience.

    This object uses the state of the node to compare equality and for its hash function,
    so you can use it in things like sets and priority queues if you want those structures
    to use the state for comparison.

    Example usage:
    >>> S = Node("Start", None, None, 0)
    >>> A1 = Node("A", S, "Up", 4)
    >>> B1 = Node("B", S, "Down", 3)
    >>> B2 = Node("B", A1, "Left", 6)
    >>> B1 == B2
    True
    >>> A1 == B2
    False
    >>> node_list1 = [B1, B2]
    >>> B1 in node_list1
    True
    >>> A1 in node_list1
    False
    """
    def __init__(self, state, parent, action, path_cost):
        self.state = state
        self.parent = parent
        self.action = action
        self.path_cost = path_cost

    def __hash__(self):
        return hash(self.state)

    def __eq__(self, other):
        return self.state == other.state

    def __ne__(self, other):
        return self.state != other.state


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def breadthFirstSearch(problem):
    """
    Search the shallowest nodes in the search tree first.

    You are not required to implement this, but you may find it useful for Q5.
    """
    "*** YOUR CODE HERE ***"

    from game import Directions
    from collections import deque

    visited = []
    deq = deque()

    if(problem.goalTest(problem.getStartState)):
        return []

    node = Node(problem.getStartState(), None, None, 0)
    deq.appendleft(node)
    found = False

    while(found != True):
        node = deq.pop()
        if(problem.goalTest(node.state) == True):
            found == True
            break
        acts = problem.getActions(node.state)
        visited.insert(0, node.state)
        for currentAction in acts:
            child_state = problem.getResult(node.state, currentAction)
            child_cost = problem.getCost(node.state, currentAction)
            child_Node = Node(child_state, node, currentAction, child_cost)
            if(child_state in visited):
                continue
            else:
                deq.appendleft(child_Node)

            
    finalActions = []
    while not node.state == problem.getStartState():
        finalActions.insert(0, node.action)
        node = node.parent
        
    return finalActions
    
def depthFirstSearch(problem): 

    from game import Directions

    node = Node(problem.getStartState(), None, None, 0)
    frontier = util.Stack()
    frontier.push(node)

    visited = []

    def iterate():
        tempNode = frontier.pop()
        if(problem.goalTest(tempNode.state) == True):
            return tempNode
        visited.insert(0, tempNode.state)
        acts = problem.getActions(tempNode.state)
        solution = "failed"
        for x in acts:
            child_state = problem.getResult(tempNode.state, x)
            child_cost = problem.getCost(tempNode.state, x)
            child_Node = Node(child_state, tempNode, x, child_cost)
            if(child_state in visited):
                continue            
            frontier.push(child_Node)
            solution = iterate()
            if (str(solution) != "failed"):
                    return solution
        return solution   
    
    goalNode = iterate()
    actions = []
    while not goalNode.state == problem.getStartState():
        actions.insert(0, goalNode.action)
        goalNode = goalNode.parent
            
    return actions



def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def iterativeDeepeningSearch(problem):
    """
    Perform DFS with increasingly larger depth. Begin with a depth of 1 and increment depth by 1 at every step.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.goalTest(problem.getStartState()))
    print("Actions from start state:", problem.getActions(problem.getStartState()))

    Then try to print the resulting state for one of those actions
    by calling problem.getResult(problem.getStartState(), one_of_the_actions)
    or the resulting cost for one of these actions
    by calling problem.getCost(problem.getStartState(), one_of_the_actions)

    """
    "*** YOUR CODE HERE ***"

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.goalTest(problem.getStartState()))
    print("Actions from start state:", problem.getActions(problem.getStartState()))



    util.raiseNotDefined()
    
def UniformCostSearch(problem):
    """Search the node that has the lowest path cost first."""
    "*** YOUR CODE HERE ***"  
    util.raiseNotDefined()
    

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    from game import Directions
    node = Node(problem.getStartState(), None, None, 0)
    frontier = util.PriorityQueue()
    frontier.push(node, heuristic(problem.getStartState(), problem))
    found = False
    #visited = []

    while(found != True):
        if frontier.isEmpty():
            return
        node = frontier.pop()
        if problem.goalTest(node.state):
            found = True
            continue
        #visited.insert(0, node.state)
        for acts in problem.getActions(node.state):
            child_state = problem.getResult(node.state, acts)
            child_cost = problem.getCost(node.state, acts)
            child_node = Node(child_state, node, acts, child_cost+node.path_cost)
            #if (acts in visited):
                #continue
            frontier.update(child_node, (heuristic(child_state, problem)+child_node.path_cost))
    
    actions = []
    while not node.state == problem.getStartState():
        actions.insert(0, node.action)
        node = node.parent
    return actions


# Abbreviations
bfs = breadthFirstSearch
astar = aStarSearch
ids = iterativeDeepeningSearch
