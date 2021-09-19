require './Trabajo.rb'

class Tecnico

    protected
    def self.clone()
        return Tecnico.new()
    end

    private
    def self.initialize(n,e,dni,trbSist)
        @nombre=n
        @edad=e
        @DNI=dni
        @trabajos=trbSist

    end

    public
    def realizarPuja()
    end


    public
    attr_accessor :trbRealizar, :nombre, :edad, :DNI, :trabajos
end