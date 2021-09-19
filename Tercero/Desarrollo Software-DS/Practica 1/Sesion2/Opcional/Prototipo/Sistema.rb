require './Cliente.rb'
require './Tecnico.rb'
require './Trabajo.rb'
require './FactoriaPrototipo.rb'
require './FactoriaPrototipoPremium.rb'
require './FactoriaPrototipoLite.rb'


class Sistema
    @trabajosSistema=Array.new
    @clientesSistema=Array.new
    @tecnicosSistema=Array.new
    
    @factoria=FactoriaPrototipo.new

    @nombresPosibles=["Fran","Santiago","Raul","Cristian","Angel","Pepe"]
    @DNIPosibles=["111111X", "22222Z", "3333333P", "4444444S", "77777V", "88888Z"]
    @trabajosPosibles=["Obra","Reparacion","Fontanero","Averia","Mantenimiento","Pintar"]
    
    def self.generarSistema
        @numClientesTecnicos=rand(5)+1
        
        @factoria=FactoriaPrototipoLite.new
        for i in (0...@numClientesTecnicos/2)
            edadRandom=rand(80)+18
            @clientesSistema.push(@factoria.crearCliente(@nombresPosibles[i],edadRandom,@DNIPosibles[i]))
            @trabajosSistema=@clientesSistema[i].crearTrabajo(5000,@trabajosPosibles[i],i,@trabajosSistema)
        end


        @factoria= FactoriaPrototipoPremium.new()

        for j in (@numClientesTecnicos/2...@numClientesTecnicos)
            edadRandom=rand(80)+18
            @clientesSistema.push(@factoria.crearCliente(@nombresPosibles[j],edadRandom,@DNIPosibles[j]))
            @trabajosSistema=@clientesSistema[j].crearTrabajo(5000,@trabajosPosibles[j],j,@trabajosSistema)
        end

        puts "\n"

        @factoria= FactoriaPrototipoLite.new()
        
        
        for z in (0...@numClientesTecnicos/2)
            edadRandom=rand(80)+18
            @tecnicosSistema.push(@factoria.crearTecnico(@nombresPosibles[z],edadRandom,@DNIPosibles[z],@trabajosSistema))
            
        end


        @factoria= FactoriaPrototipoPremium.new()
        

        for r in (@numClientesTecnicos/2...@numClientesTecnicos)
            edadRandom=rand(80)+18
            @tecnicosSistema.push(@factoria.crearTecnico(@nombresPosibles[r],edadRandom,@DNIPosibles[r],@trabajosSistema))
        end
        puts "\n"
    end

    
    def self.simulacion

        generarSistema()
        for k in (0...@tecnicosSistema.length)
            @tecnicosSistema[k].realizarPuja()
        end
        puts "\n"
    end

    def self.main
        simulacion()
        for i in (0...@trabajosSistema.length)
            @trabajosSistema[i].resultadoFinal()
        end
    end
    Sistema.main
    
    public
    attr_accessor :trabajosSistema
end