require './FactoriaPrototipo.rb'
require './ClientePremium.rb'
require './TecnicoPremium.rb'

class FactoriaPrototipoPremium < FactoriaPrototipo

    def self.initialize
        puts "Factoria prototipo premium creada \n"
    end
    
    def crearCliente(n,e,dni)
        cliente= ClientePremium.clone
        cliente.nombre=n
        cliente.edad=e
        cliente.DNI=dni

        return cliente
    end

    def crearTecnico(n,e,dni,trabajos)
        tecnico = TecnicoPremium.clone
        tecnico.nombre = n
        tecnico.edad = e
        tecnico.DNI = dni
        tecnico.trabajos = trabajos

        return tecnico
    end

end