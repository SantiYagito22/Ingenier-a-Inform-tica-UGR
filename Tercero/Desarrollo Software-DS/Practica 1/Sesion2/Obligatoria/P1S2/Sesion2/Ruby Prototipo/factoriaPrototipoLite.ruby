require 'FactoriaPrototipo.ruby'
require 'clienteLite.ruby'
require 'tecnicoLite.ruby'

class factoriaPrototipoLite < factoriaPrototipo

    def initialize
        puts "Factoria prototipo lite creada \n"
    end

    def crearCliente(n,e,dni)
        cliente= clienteLite.clone
        cliente.nombre=n
        cliente.edad=e
        cliente.DNI=dni

        return cliente
    end

    def crearTecnico(n,e,dni,trabajos)
        tecnico = tecnicoLite.clone
        tecnico.nombre = n
        tecnico.DNI = dni
        tecnico.trabajos = trabajos

        return tecnico
    end

end