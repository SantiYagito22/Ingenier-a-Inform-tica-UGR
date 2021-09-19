require './FactoriaPrototipo.rb'
require './ClienteLite.rb'
require './TecnicoLite.rb'

class FactoriaPrototipoLite < FactoriaPrototipo


    def self.initialize
        puts "Factoria prototipo lite creada \n"
    end

    def crearCliente(n,e,dni)
        cliente= ClienteLite.clone
        cliente.nombre=n
        cliente.edad=e
        cliente.DNI=dni

        return cliente
    end

    def crearTecnico(n,e,dni,trabajos)


        tecnico = TecnicoLite.clone
        tecnico.nombre=n
        tecnico.edad= e
        tecnico.DNI=dni
        tecnico.trabajos=trabajos

        return tecnico
    end

end