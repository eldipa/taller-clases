import ctypes

_sumDLL = ctypes.CDLL('./libsum.so')
_sumDLL.sum.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)

def sumWrap(values):
    global _sumDLL
    # Declaro el tipo array de enteros
    array_type = ctypes.c_int * len(values)
    # Version CType del size del array
    cValuesSize = ctypes.c_int(len(values))
    result = _sumDLL.sum(array_type(*values), cValuesSize)
    return int(result)
