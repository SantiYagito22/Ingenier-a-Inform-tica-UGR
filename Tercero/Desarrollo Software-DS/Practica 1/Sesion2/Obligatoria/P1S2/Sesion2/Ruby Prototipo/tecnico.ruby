require 'Trabajo.ruby'

class Tecnico 
    @trbRealizar=Trabajo.new()
    
    protected
    def clone 
        return Tecnico.new(@nombre,@edad,@DNI,@trabajos)
    end

    private
    def initialize(n,e,dni,trbSist)
        @nombre=nombre
        @edad=e
        @DNI=dni
        @trabajos=trbSist
    end

    public
    def realizarPuja()
    end

    attr_reader :trbRealizar, :nombre, :edad, :DNI, :trabajos
end