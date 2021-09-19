
require './Trabajo.rb'
require './Cliente.rb'


class ClientePremium < Cliente

    @@seguro_obra=true

    protected
    def self.clone()
        return ClientePremium.new()
    end

    public
    def self.initialize(n,e,dni)
        super(n,e,dni)
    end

    public
    def crearTrabajo(of, tipo, num,trbs)
            trb=Trabajo.new(of,tipo,num,self)
            puts "El cliente PREMIUM #{@nombre} ha creado el trabajo con id #{num}"
            trbs.push(trb)

        return trbs
    end

    


end