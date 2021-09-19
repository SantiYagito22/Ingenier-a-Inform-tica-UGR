require './Cliente.rb'
require './Tecnico.rb'


class Trabajo

    private
    def initialize(of,tip,num_trb,cl)
        @oferta=of
        @num_trabajo=num_trb
        @tipo=tip
        @c=cl
        @tec=Tecnico.new()
    end

    public
    def pujar(puja,t,gastos)
        if puja<@oferta
            @tec=t
            @oferta=puja
            if gastos
                puts "El tecnico LITE #{t.nombre} se queda por ahora con la subasta con una oferta de #{@oferta} del trabajo #{@num_trabajo}"
            else
                puts "El tecnico PREMIUM #{t.nombre} se queda por ahora con la subasta con una oferta de #{@oferta} del trabajo #{@num_trabajo}"
            end
        end    
    end

    public
    def resultadoFinal()
        if @tec.nombre!=nil
         puts "El trabajo con id #{@num_trabajo} ha sido otorgado al tecnico #{@tec.nombre}"
        end
    end


    attr_accessor :oferta, :num_trabajo, :tipo
end