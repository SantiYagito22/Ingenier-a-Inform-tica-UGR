require 'Trabajo.ruby'

class tecnicoLite < tecnico

    protected
    def clone 
        return Tecnico.new(@nombre,@edad,@DNI,@trabajos)
    end


    private
    def initialize(n,e,dni,trbSist)
        super(n,e,dni,trbSist)

    end


    def realizarPuja()
        numTrb=rand(@trabajos.length)
        ofertaRandom = rand(@trabajos[numTrb].oferta)

        if ofertaRandom<=20
            ofertaRandom=20
        end

        puts "El tecnico LITE #{@nombre} realiza una puja al trabajo con id #{@trabajos[numTrb].num_trabajo} de #{ofertaRandom}"
        @trabajos[numTrb].pujar(ofertaRandom,self,@gastosTransporte)
    end