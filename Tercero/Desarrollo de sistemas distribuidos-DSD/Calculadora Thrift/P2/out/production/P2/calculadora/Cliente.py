

from calculadora import Calculator
from calculadora.ttypes import operacionInvalida, operacionBasica, operacionVectores, segundoGrado, combinada

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol


def main():
    # Make socket
    transport = TSocket.TSocket('localhost', 9090)

    # Buffering is critical. Raw sockets are very slow
    transport = TTransport.TBufferedTransport(transport)

    # Wrap in a protocol
    protocol = TBinaryProtocol.TBinaryProtocol(transport)

    # Create a client to use the protocol encoder
    client = Calculator.Client(protocol)

    # Connect!
    transport.open()

    oB= operacionBasica()
    oB.a=0
    oB.b=0.0


    sum_ = client.suma(oB)
    rest_=client.resta(oB)
    mult_ = client.multiplicacion(oB)



    print('Suma:',sum_)
    print('Resta:', rest_)
    print('Multiplicación:', mult_)



    try:
        div_ = client.division(oB)
        print('División:', div_)
    except operacionInvalida as e:
        print('Error', e.tipo, ':', e.why)


    oV=operacionVectores()

    oV.v1 = [2, 2, 3]
    oV.v2 = [4, 5, 6]

    try:
     a_ = client.divisionVectores(oV)
     for i in range(len(a_)):
         print(a_[i])
    except operacionInvalida as e:
        print('Error', e.tipo, ':', e.why)


    sg = segundoGrado()

    sg.a = 1.0
    sg.b = 1.0
    sg.c = 1.0
    try:
        w = client.ecuacionCuadratica(sg)
        print('Segundo grado')
        for i in range(len(w)):
         print(w[i])
    except operacionInvalida as e:
        print('Error', e.tipo, ':', e.why)


    cb = combinada()
    cb.op = []
    cb.op.append("+")
    cb.op.append("-")
    cb.op.append("*")
    cb.op.append("+")
    cb.op.append("/")
    cb.op.append("-")
    cb.op.append("*")

    cb.nums = []

    cb.nums.append(5)
    cb.nums.append(8)
    cb.nums.append(7)
    cb.nums.append(3)
    cb.nums.append(5)
    cb.nums.append(5)
    cb.nums.append(7)
    cb.nums.append(10)

    print('Combinada', client.operacionCombinada(cb))

    '''
    work = Work()

    work.op = Operation.DIVIDE
    work.num1 = 1
    work.num2 = 0

    try:
        quotient = client.calculate(1, work)
        print('Whoa? You know how to divide by zero?')
        print('FYI the answer is %d' % quotient)
    except InvalidOperation as e:
        print('InvalidOperation: %r' % e)

    work.op = Operation.SUBTRACT
    work.num1 = 15
    work.num2 = 10

    diff = client.calculate(1, work)
    print('15-10=%d' % diff)

    log = client.getStruct(1)
    print('Check log: %s' % log.value)
    '''
    # Close!
    transport.close()


if __name__ == '__main__':
    try:
        main()
    except Thrift.TException as tx:
        print('%s' % tx.message)