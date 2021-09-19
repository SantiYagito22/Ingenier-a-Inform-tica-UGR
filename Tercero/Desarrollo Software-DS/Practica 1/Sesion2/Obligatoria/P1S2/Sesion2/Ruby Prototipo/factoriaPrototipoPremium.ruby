require 'FactoriaPrototipo.ruby'
require 'clientePremium.ruby'
require 'tecnicoPremium.ruby'

class factoriaPrototipoPremium < factoriaPrototipo

    def initialize
        puts "Factoria prototipo premium creada \n"
    end
    
    def crearCliente(n,e,dni)
        cliente= clientePremium.clone
        cliente.nombre=n
        cliente.edad=e
        cliente.DNI=dni

        return cliente
    end

    def crearTecnico(n,e,dni,trabajos)
        tecnico = tecnicoPremium.clone
        tecnico.nombre = n
        tecnico.DNI = dni
        tecnico.trabajos = trabajos

        return tecnico
    end

end