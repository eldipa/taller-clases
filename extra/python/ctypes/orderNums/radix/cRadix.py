import ctypes


class CVector(ctypes.Structure):
    _fields_ = [("data", ctypes.POINTER(ctypes.c_char_p)),
                ("size", ctypes.c_int)]

_radixDLL = ctypes.CDLL('radix/lib/libradix.so')
# Codigo C: void sort(MyVector indexes);
_radixDLL.sort.argtypes = [CVector]

def listToCVector(pyList):
    # Declaro el tipo array de char*
    array_type = (ctypes.c_char_p * len(pyList))
    # Si leyera en modo texto, deberia aplicar str encode sobre todos
    # los elemntos para obtener los bytes
    # valuesMap = map(lambda s: str.encode(s), values) es mas lento, no usar
    cArray = array_type(*pyList)
    # Version CType del size del array
    cSize = ctypes.c_int(len(pyList))
    return CVector(cArray, cSize)


#@profile
def sort(values):
    global _radixDLL
    cVector = listToCVector(values)
    # Ordena in-place
    _radixDLL.sort(cVector)
    return convertResult(cVector)

    
def convertResult(cVector):
    #Ya no se usa la conversion porque trabajo con datos binarios
    #valuesMap = map(lambda b: b.decode('utf-8'), cResult) no usar
    #values = [result.decode('utf-8') for result in cResult]
    # le tengo que especificar el rango porque sino hay overflow
    return list(cVector.data[:cVector.size])