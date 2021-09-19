require 'Trabajo.ruby'

public class cliente
    @trabajosSubidos=Array.new() # o [] 
    @sistema

        protected
    def clone
        return cliente.new(@nombre,@edad,@DNI)
    end

    private
    def initialize(n, e,dni)
        @nombre=n
        @edad=e
        @DNI=dni
    end

    public
    def crearTrabajo(of, tipo, num)
    end

    public
    attr_accessor :nombre, :edad, :DNI
    
end