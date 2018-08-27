import itertools
import sys

MAX_LEN = 4 # Mis palabras son de largo 4
ALPHA = 10 # Tengo 10 caracteres posibles (digitos del 0 al 9)

pythonIsOld = sys.version_info.major < 3

def sort(nums):
    bucketList = _buildBuckets(ALPHA)
    for i in reversed(range(MAX_LEN)):
        for num in nums:
            if pythonIsOld:
                bucketIdx = ord(num[i]) - 48
            else:
                bucketIdx = num[i] - 48
            bucketList[bucketIdx].append(num)
        nums = list(itertools.chain.from_iterable(bucketList))
        _clearBuckets(bucketList)
    return nums

def _buildBuckets(numBuckets):
    buckets = [None] * numBuckets
    for i in range(0, numBuckets):
        buckets[i] = list()
    return buckets

def _clearBuckets(buckets):
    for b in buckets:
        del b[:]
