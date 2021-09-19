

from calculadora import Calculator
from calculadora.ttypes import operacionInvalida



from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer
import math

class CalculatorHandler:
    def __init__(self):
        self.log = {}

    def ping(self):
        print('ping()')

    def suma(self, oB):
        return oB.a + oB.b

    def resta(self, oB):
        return oB.a - oB.b

    def multiplicacion(self, oB):
        return oB.a * oB.b

    def division(self, oB):
        if oB.b==0:
            raise operacionInvalida('division','No se puede dividir un número entre 0, es una indeterminación')
        return oB.a / oB.b

    def sumaVectores(self, oV):
        a = []
        if range(len(oV.v1)) != range(len(oV.v2)):
            raise operacionInvalida('Parametros inválidos', 'El tamaño de los dos vectores no son iguales')
        for i in range(len(oV.v1)):
            a.append(oV.v1[i]+oV.v2[i])
        return a

    def restaVectores(self, oV):
        a = []
        if range(len(oV.v1)) != range(len(oV.v2)):
            raise operacionInvalida('Parametros inválidos', 'El tamaño de los dos vectores no son iguales')
        for i in range(len(oV.v1)):
            a.append(oV.v1[i]-oV.v2[i])
        return a

    def multiplicacionVectores(self, oV):
        a = []
        if range(len(oV.v1)) != range(len(oV.v2)):
            raise operacionInvalida('Parametros inválidos', 'El tamaño de los dos vectores no son iguales')
        for i in range(len(oV.v1)):
            a.append(oV.v1[i] * oV.v2[i])
        return a

    def divisionVectores(self,oV):
        a = []
        if range(len(oV.v1)) != range(len(oV.v2)):
            raise operacionInvalida('parametros inválidos', 'El tamaño de los dos vectores no son iguales')
        for i in range(len(oV.v1)):
            if oV.v2[i] == 0:
                raise operacionInvalida('division', 'No se puede dividir un número entre 0, es una indeterminación')
            a.append(oV.v1[i] / oV.v2[i])
        return a

    def ecuacionCuadratica(self, sg):

        a=[0,0]

        raiz=(sg.b*sg.b) - (4*sg.a*sg.c)
        if raiz > 0 :
           a[0]= (-sg.b+math.sqrt(raiz))/(2 * sg.a)
           a[1] = (-sg.b-math.sqrt(raiz))/(2 * sg.a)
        elif raiz==0:
            a[0] = -sg.b / (2 * sg.a)
            a[1] = a[0]
        else:
            raise operacionInvalida('ecuación de segundo grado', 'La ecuación cuadrática no tiene solución')

        return a

    def operacionCombinada(self, cb):


        if len(cb.nums) == len(cb.op):
            cb.op.pop(0)
            cb.nums[0] = cb.nums[0] * -1

        i=0
        while(i != len(cb.op)):
            if cb.op[i] == "x" or cb.op[i] == "*":
                cb.nums[i]= cb.nums[i] * cb.nums[ i + 1]
                cb.op.pop(i)
                cb.nums.pop(i+1)
                if i != 0:
                    i = i - 1
            elif cb.op[i] == "/":
                cb.nums[i] = cb.nums[i] / cb.nums[i + 1]
                cb.op.pop(i)
                cb.nums.pop(i + 1)
                if i != 0:
                    i = i - 1
            else:
                i = i + 1


        j=0
        while (j != len(cb.op)):

            if cb.op[j] == "+":
                cb.nums[j] = cb.nums[j] + cb.nums[j + 1]
                cb.op.pop(j)
                cb.nums.pop(j + 1)
                if j != 0:
                    j = j - 1
            elif cb.op[j] == "-":
                cb.nums[j] = cb.nums[j] - cb.nums[j + 1]
                cb.op.pop(j)
                cb.nums.pop(j + 1)
                if j != 0:
                    j = j - 1
            else:
                j = j + 1


        result = cb.nums[0]

        return result


    '''
    def calculate(self, logid, work):
        print('calculate(%d, %r)' % (logid, work))

        if work.op == Operation.ADD:
            val = work.num1 + work.num2
        elif work.op == Operation.SUBTRACT:
            val = work.num1 - work.num2
        elif work.op == Operation.MULTIPLY:
            val = work.num1 * work.num2
        elif work.op == Operation.DIVIDE:
            if work.num2 == 0:
                raise InvalidOperation(work.op, 'Cannot divide by 0')
            val = work.num1 / work.num2
        else:
            raise InvalidOperation(work.op, 'Invalid operation')

        log = SharedStruct()
        log.key = logid
        log.value = '%d' % (val)
        self.log[logid] = log

        return val

    def getStruct(self, key):
        print('getStruct(%d)' % (key))
        return self.log[key]

    def zip(self):
        print('zip()')

    '''

if __name__ == '__main__':
    handler = CalculatorHandler()
    processor = Calculator.Processor(handler)
    transport = TSocket.TServerSocket(host='127.0.0.1', port=9090)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    # You could do one of these for a multithreaded server
    # server = TServer.TThreadedServer(
    #     processor, transport, tfactory, pfactory)
    # server = TServer.TThreadPoolServer(
    #     processor, transport, tfactory, pfactory)

    print('Starting the server...')
    server.serve()
    print('done.')