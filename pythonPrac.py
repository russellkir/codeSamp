#Russell Kirmayer, rkirmaye, F
import string

#given a list of integers, returns a dictionary mapping 
#integer values to their number of occurrences in the list
def getCounts(a):
    d = {}
    for i in a:
        if(i not in d):
            d[i] = 0
        d[i] += 1
    return d
#given a dictionary, return each value going to the key that mapped to it
#if a value occurs more than once, the list of keys going to that value is 
#mapped to
def invertDictionary(d):
    iD = {}
    for k in d:
        if (d[k] not in iD):
            iD[d[k]] = k
            continue
        elif type(iD[d[k]]) != list:
            iD[d[k]] = [iD[d[k]]]
        iD[d[k]].append(k)
    for k in iD:
        if type(iD[k]) == list:
            iD[k].sort()
    return iD

#given a list of integers, returns the integer that occurs most  If there
#are several such, returns a sorted list of them
def mode(a):
    d = invertDictionary(getCounts(a))
    if len(d) == 0:
        return None
    return d[max(d.keys())]

#checks if two given strings are anagrams of one another
def isAnagram(s1, s2):
    if(s1 == s2 or len(s1) != len(s2)):
        return False
    s1 = alpha(s1)
    s2 = alpha(s2)
    if (s1 == s2): 
        return True
    return False

def collectAnagrams(a):
    d = {}
    for word in a:
        key = alpha(word)
        if key in d:
            if word not in d[key]:
                d[key] += (word,)
        else:
            d[key] = (word,)
    n = []
    for key in d:
        tuple = ()
        for word in d[key]:
                tuple += (word,)
        n += [tuple]
    return n

def alpha(word):
    return string.join(sorted(word),'')

class MyDictionary (dict):
    def __le__(self, other):
        '''Implements a 'subset' method on dictionaries.'''
        dict2Keys = other.keys()

        # Loop over keys in first, check if in 2nd, then if values match.
        for key in self.keys():
            if key not in dict2Keys or self[key] != other[key]:
                return False

        return True

    def __and__(self, other):
        #produces a new dictionary with only elements that are common
        # to both
        result = MyDictionary()
        #use .keys(), not .viewkeys()
        keys1 = self.keys()
        keys2 = other.keys()
        for key in keys1:
            #add result dictionary iff in both
            if(key in keys2) and (self[key] == other[key]):
                result[key] = self[key]
        return result

    @classmethod
    def masterDictionary(cls, dictionaries):
        #combine a list of arbitrarily many dictionaries into a single
        #instance, where the result values are set of the input values

        result = MyDictionary()

        #loop over dictionaries
        for elt in dictionaries:
            #look at each key in the current dictionary
            for key in elt.keys():
                #add the key to the result if not present
                if key not in result.keys():
                    result[key] = set([elt[key]])
                #append to the list if value not already present
                elif elt[key] not in result[key]:
                    result[key].add(elt[key])
        return result


class Polynomial(object):
    def __init__(self, coefficients):
        #simulates a polynomial
        self.coefs = []
        if isinstance(coefs, int) or isinstance(coefs, float):
            coefs = [coefs]
        if isinstance(coefs, list):
            self._addListCoefs(coefs)
        elif isinstance(coefs, dict):
            self._addDictCoefs(coefs)
        else:
            raise Exception("Can only make a polynomial from a list or dict")
        self.setDegree()

    def __add__(self, other):
        if isinstance(other, int) or isinstance(other, float):
            other = Polynomial(other)
        if not isinstance(other, Polynomial):
            raise Exception("Sorry, can't add a polynomial to %r" % other)
        toReturn = Polynomial()
        for i in xrange(max(self.degree, other.degree) + 1):
            toReturn[i] = self[i] + other[i]
        toReturn.setDegree()
        return toReturn

    def _addListCoefs(self, coefs):
        self.coefs = coefs[::-1]

    def _addDictCoefs(self,coefs):
        maxIndex = 0
        for key in coefs:
            if key < 0:
                raise Exception("")
            elif key > maxIndex:
                maxIndex = key
        self.coefs = [0] * (maxIndex + 1)
        for i in xrange(len(self.coefs)):
            self.coefs[i] = coefs.get(i,0)
    def setDegree(self):
        self.degree = len(self.coefs) - 1
        for i in xrange(len(self.coefs) - 1, -1, -1):
            if self.coefs[i] == 0:
                del self.coefs[i]
                self.degree = i - 1
            else:
                break

   def __mul__(self, other):
        if isinstance(other, int) or isinstance(other, float):
            other = Polynomial(other)
        if not isinstance(other, Polynomial):
            raise Exception("Sorry, can't add a polynomial to %r" % other)
        result = Polynomial()
        for i in xrange(self.degree + other.degree + 1):
            selfIndex = 0
            otherIndex = i
            while selfIndex <= i:
                result[i] = result[i] + self[selfIndex] * other[otherIndex]
                selfIndex += 1
                otherIndex -= 1
        result.setDegree()
        return result

    def __sub__(self, other):
        try:
            return self + (other * -1)
        except:
            raise Exception("Sorry, can't sub a polynomial to %r" % other)

        if isinstance(other, int) or isinstance(other, float):
            other = Polynomial(other)
        if not isinstance(other, Polynomial):
            pass
        toReturn = Polynomial()
        for i in xrange(max(self.degree, other.degree) + 1):
            toReturn[i] = self[i] - other[i]
        toReturn.setDegree()
        return toReturn

    def __div__(self, other):
        if not (isinstance(other, int) or isinstance(other, float)):
            raise Exception("Sorry, can't div a polynomial by %r" % other)

        other = float(other)
        toReturn = Polynomial()
        for i in xrange(self.degree + 1):
            toReturn[i] = self[i] / other 
        toReturn.setDegree()
        return toReturn

    def __pow__(self, other):
        toReturn = Polynomial(1)
        for i in xrange(other):
            toReturn *= self
        return toReturn

    def __str__(self):
        result = ""
        if self.coefs == []:
            return "0.00"

        if len(self.coefs) == 1:
            return "%.2f" % self.coefs[0]

        if self.coefs[0] > 0:
            result = " + %.2f" % abs(self.coefs[0])
        elif self.coefs[0] < 0:
            result = " - %.2f" % abs(self.coefs[0])

        if len(self.coefs) == 2:
            return ("%.2f*x" % self.coefs[1]) + result

        if self.coefs[1] > 0:
            result = (" + %.2f*x" % (abs(self.coefs[1]))) + result
        elif self.coefs[1] < 0:
            result = (" - %.2f*x" % (abs(self.coefs[1]))) + result


        for i in xrange(2, len(self.coefs) - 1):
            if self.coefs[i] > 0:
                result = (" + %.2f*x**%d" % (abs(self.coefs[i]), i)) + result
            elif self.coefs[i] < 0:
                result = (" - %.2f*x**%d" % (abs(self.coefs[i]), i)) + result

        

        result = ("%.2f*x**%d" % (self.coefs[-1], len(self.coefs) - 1)) + result
        return result

    # plusEquals and friends


    def __repr__(self):
        return "Polynomial(%r)" % (self.coefs[::-1])

    def __getitem__(self, i):
        if not (0 <= i <= self.degree):
            return 0
        return self.coefs[i]

    def __setitem__(self, key, value):
        if key < 0:
            raise Exception("Illegal degree")
        elif key <= self.degree:
            self.coefs[key] = value
        else:
            listToAdd = [0] * (key - self.degree)
            listToAdd[-1] = value
            self.coefs += listToAdd

        self.setDegree()

    def __getslice__(self, i, j):
        if j < 0:
            raise Exception("Illegal degree")
        newList = [0] * (j+1)
        for k in xrange(len(newList)):
            if i <= k <= j:
                newList[k] = self[k]

        return Polynomial(newList[::-1])

    def __lt__(self, other):
        for i in xrange(max(self.degree, other.degree), -1, -1):
            if self[i] < other[i]:
                return True
            if self[i] > other[i]:
                return False
        return False
    
    def __le__(self, other):
        for i in xrange(max(self.degree, other.degree), -1, -1):
            if self[i] < other[i]:
                return True
            if self[i] > other[i]:
                return False
        return True
    
    def __eq__(self, other):
        if not isinstance(other, Polynomial):
            return False
        return self.coefs == other.coefs
    
    def __ne__(self, other):
        if not isinstance(other, Polynomial):
            return False
        return self.coefs != other.coefs
    
    def __gt__(self, other):
        for i in xrange(max(self.degree, other.degree), -1, -1):
            if self[i] > other[i]:
                return True
            if self[i] < other[i]:
                return False
        return False

    def __ge__(self, other):
        for i in xrange(max(self.degree, other.degree), -1, -1):
            if self[i] > other[i]:
                return True
            if self[i] < other[i]:
                return False
        return True

    def __copy__(self):
        return Polynomial(self.coefs[::-1])

    def evaluate(self, x):
        return eval(str(self))

    def differentiate(self, level):
        newPoly = Polynomial(self.coefs[::-1])
        for i in xrange(level):
            for j in xrange(self.degree + 1):
                newPoly[j] = newPoly[j + 1] * (j + 1)
        return newPoly

    def integrate(self, C):
        newPoly = Polynomial()
        newPoly[0] = C
        for i in xrange(1, self.degree + 2):
            newPoly[i] = self[i-1] / (1.0 * i)
        return newPoly
 
