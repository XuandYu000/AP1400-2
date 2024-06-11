from collections import Counter

def adjacentElementsProduct(input):
    return max(input[i] * input[i + 1] for i in range(len(input) - 1))

def allLongestStrings(inputArray):
    return [s for s in inputArray if len(s) == max(map(len, inputArray))]

def checkPalindrome(inputString):
    return inputString == inputString[::-1]

def commonCharacterCount(s1, s2):
    return sum(min(s1.count(char), s2.count(char)) for char in set(s1))

def areSimilar(A, B):
    return sorted(A) == sorted(B) and sum(a != b for a, b in zip(A, B)) <= 2

def palindromeRearranging(inputString):
    return sum(freq % 2 for freq in Counter(inputString).values()) <= 1

def arrayReplace(inputArray, elemToReplace, substitutionElem):
    return [substitutionElem if i == elemToReplace else i for i in inputArray]

def evenDigitsOnly(n):
    return sum(int(i) % 2 for i in str(n)) == 0

def alphabeticShift(inputstring):
    return ''.join(chr(((ord(char) - ord('a') + 1) % 26) + ord('a')) for char in inputstring)

def firstDigit(inputstring):
    return next(int(char) for char in inputstring if char.isdigit())