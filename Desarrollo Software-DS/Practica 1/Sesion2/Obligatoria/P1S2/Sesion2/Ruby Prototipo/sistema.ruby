require 'cliente.ruby'
require 'tecnico.ruby'
require 'Trabajo.ruby'
require 'FactoriaPrototipo.ruby'

class sistema

    @@trabajosSistema=Array.new
    @clientesSistema=Array.new
    @tecnicosSistema=Array.new
    
    @factoria=factoriaPrototipo.new

    @nombresPosibles=["Fran","Santiago","Raul","Cristian","Angel","Pepe"]
    @DNIPosibles=["111111X", "22222Z", "3333333P", "4444444S", "77777V", "88888Z"]
    @trabajosPosibles=["Obra","Reparacion","Fontanero","Averia","Mantenimiento","Pintar"]
    
    def generarSistema()
        numClientesTecnicos=rand(5)+1
        
        @factoria= factoriaPrototipoLite.new()

        for i in (0..@numClientesTecnicos/2)
            edadRandom=rand(80)+18
            @clientesSistema.push(factoria.crearCliente(@nombresPosibles[i],edadRandom,@DNIPosibles[i]))
            @clientesSistema[i].crearTrabajo(5000,@trabajosPosibles[i],i)
        end

        @factoria= factoriaPrototipoPremium.new()

        for i in (@numClientesTecnicos/2..@numClientesTecnicos)
            edadRandom=rand(80)+18
            @clientesSistema.push(factoria.crearCliente(@nombresPosibles[i],edadRandom,@DNIPosibles[i]))
            @clientesSistema[i].crearTrabajo(5000,@trabajosPosibles[i],i)
        end

        @factoria= factoriaPrototipoLite.new()
        
        
        for i in (0..@numClientesTecnicos/2)
            edadRandom=rand(80)+18
            @tecnicosSistema.push(factoria.crearTecnico(@nombresPosibles[i],edadRandom,@DNIPosibles[i],@@trabajosSistema))
            
        end

        @factoria= factoriaPrototipoPremium.new()
        
        
        for i in (@numClientesTecnicos/2..@numClientesTecnicos)
            edadRandom=rand(80)+18
            @tecnicosSistema.push(factoria.crearTecnico(@nombresPosibles[i],edadRandom,@DNIPosibles[i],@@trabajosSistema))
        end
        
    end
    
    
    def simulacion()
        generarSistema()
        for i in (0..@numClientesTecnicos)
            @tecnicosSistema[i].realizarPuja()
        end
    end

    def main
        simulacion()
        for i in (0..@numClientesTecnicos)
            @trabajosSistema[i].resultadoFinal()
        end
    end
    
    public
    attr_accessor :trabajosSistema
end