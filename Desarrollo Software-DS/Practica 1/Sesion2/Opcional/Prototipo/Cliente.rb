require './Trabajo.rb'



class Cliente



        protected
    def self.clone()
        return cliente.new()
    end

    private
    def self.initialize(n, e,dni)
        @nombre=n
        @edad=e
        @DNI=dni
        @trabajosSubidos=Array.new()
    end

    public
    def crearTrabajo(of, tipo, num,trbs)
    end

    public
    attr_accessor :nombre, :edad, :DNI
    
end