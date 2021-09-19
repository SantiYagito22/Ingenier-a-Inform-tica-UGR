require './Trabajo.rb'

class ClienteLite < Cliente

    @@seguro_obra=false

    protected
    def self.clone()
      return ClienteLite.new()
    end

    public
    def self.initialize(n,e,dni)
        super(n,e,dni)
    end





    public
    def crearTrabajo(of, tipo, num,trbs)

            trb=Trabajo.new(of,tipo,num,self)
            puts "El cliente LITE #{@nombre} ha creado el trabajo con id #{num}"

            trbs.push(trb)

        return trbs
    end

    


end