
require 'Trabajo.ruby'

class clientePremium < cliente

    @@seguro_obra=true

    protected
    def self.clone
        return clientePremium.new(@nombre,@edad,@DNI)
    end

    public
    def initialize(n,e,dni)
        super(n,e,dni)
    end

    public
    def crearTrabajo(of, tipo, num)
       
        buscado=true
        for i in (0..@sistema.length)
            if @sistema.trabajosSistema[i].num_trabajo == num
                puts "El trabajo ya existe en el sistema \n"
                buscado=false
            end
        end

        if buscado==true
            trb=Trabajo.new(of,tipo,num,self)
            puts "El cliente PREMIUM #{@nombre} ha creado el trabajo con id #{num}"
            @trabajosSubidos.push(trb)
            @sistema.trabajosSistema.push(trb)
        end
    end

    


end