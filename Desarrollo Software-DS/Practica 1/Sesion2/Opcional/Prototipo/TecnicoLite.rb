require './Trabajo.rb'

class TecnicoLite < Tecnico

    @@gastosTransporte=true

    protected
    def self.clone()
        return TecnicoLite.new()
    end


    public
    def self.initialize(n,e,dni,trbSist)
        super(n,e,dni,trbSist)

    end

    public
    def realizarPuja()

        numTrb=rand(@trabajos.length)
        ofertaRandom = rand(@trabajos[numTrb].oferta)

        if ofertaRandom<=20
            ofertaRandom=20
        end

        puts "El tecnico LITE #{@nombre} realiza una puja al trabajo con id #{@trabajos[numTrb].num_trabajo} de #{ofertaRandom}"

        @trabajos[numTrb].pujar(ofertaRandom,self,@@gastosTransporte)
    end


end
