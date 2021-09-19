# DIU - Practica 3, entregables
Hemos creado nuestro propio diseño visual identificable para los demas usuarios. Para ello hemos realizado un Moodboard o muro de inspiración que nos ha ayudado a tener las ideas claras para empezar nuestro proyecto.  

## Moodboard (diseño visual + logotipo)
En nuestro MoodBoard hemos tenido en cuenta nuestro logotipo, iconos, fuentes utilizadas, paleta de colores y tres imágenes inspiradoras con la apariencia visual deseada. 
  
![moodboard](https://github.com/FranJimenez88/DIU21/blob/master/P3/Moodboard/MoodBoard.png)  

  
Nuestro logotipo para la web TapaTour Granada 
  
![logo](https://github.com/FranJimenez88/DIU21/blob/master/P3/Moodboard/Logotipo.png)  
  
  
## Landing Page
A continuacion hemos creado nuestra landing page o pagina de aterrizaje, diseñada para convertir a nuestros visitantes en leads, es decir que estos visitantes se registren en la página. Para ello hemos utilizado un título y subtítulo motivadores y llamativos, una imagen atrayente y un CTA incitador.  
  
![landing2](https://github.com/FranJimenez88/DIU21/blob/master/P3/LandingPage/LP.png)  
  
## Guidelines
Nos van a permitir establecer un conjunto de reglas de utilidad general, estas reglas son de diseño visual, iconos y estilo para las ventanas.  

Guidelines que hemos utilizado:

* Paleta de colores: hemos utilizado una paleta llamativa con colores oscuros y claros para dar mayor contraste, el amarillo en las letras nos permite destacar su contenido frente al fondo oscuro, aportando al mismo tiempo una atracción visual agradable para el usuario.  
  
![paleta](https://github.com/FranJimenez88/DIU21/blob/master/P3/Guidelines/PaletaColores.png)  
  
* Tipografía:
  * Para titulos: hemos utilizado Teko, fuente clara, moderna y elegante, para titulos mas destados como el de inicio utilizaremos en negrita y para titulos menos relevantes sin ella.  
  
   ![normal](https://github.com/FranJimenez88/DIU21/blob/master/P3/Guidelines/teko.png)  
   ![negrita](https://github.com/FranJimenez88/DIU21/blob/master/P3/Guidelines/TekoNegrita.png)  
   
  * Para contenido: hemos utilizado SourceSans Pro, letra sencilla, fácil de leer y no cansa la vista. Para  texto normal utilizaremos el formato light y si queremos destacar algo utilizaremos italic bold.
  
   ![light](https://github.com/FranJimenez88/DIU21/blob/master/P3/Guidelines/SourceSansPro.png)  
   ![italicNegrita](https://github.com/FranJimenez88/DIU21/blob/master/P3/Guidelines/SourceSansProCursivaNegrita.png)  
   
* Iconos: los iconos son legibles y sencillos de reconocer, no es necesario añadir una descripcion a estos para entender su funcionamiento.  
  
  ![iconos](https://github.com/FranJimenez88/DIU21/blob/master/P3/Guidelines/Iconos.png)  
  
* Logotipo: llamativo y creativo, basado en las rutas que ofrece la web, tanto rutas gastronómicas como rutas culturales. Para hacer referencia a la gastronomia hemos puesto un chef y para referenciar Granada hemos puesto la "O" de tour una imagen de la alhambra.
  
  ![logo2](https://github.com/FranJimenez88/DIU21/blob/master/P3/Moodboard/Logotipo.png)  

## Patrones de diseño

Antes de comenzar a desarrollar los layouts, vamos a establecer los patrones de diseño que vamos a utilizar para conseguir un sistema interactivo con éxito:  

* Búsqueda:    
    * Patrón de caja de búsqueda: implementar un motor de búsqueda para que el usuario pueda localizar una ruta mediante sus datos relativos.  
    * Patrón filtrado de tabla:  complementado al patrón anterior para que el usuario haga una búsqueda mas concreta.  

* Navegación:  
    * Patrón tab navigation: integrar un diseño de menús sencillo anidados con tabuladores para facilitar la navegación entre grupos de items relacionados.   
    * Patrón pagination: para mostrar la diversa cantidad de rutas y no visualizar todos los eventos en una única pantalla.  

* Tareas:  
    * Patrón  picture manager / gallery: galería de imagenes para mostrar las diferentes rutas del sistema. Y otra galería dentro de cada una de las rutas para mostrar los     distintos sitios de esa ruta en específico.  
    * Patrón Form: implementar un formulario  para pago en el sistema.    
    * Patrón wizard: asistente para facilitar tareas como introducir fechas, rellenar campos obligatorios y asistencia de pasos para facilitar pago y registro.  
    * Patrón Account registration / sign-in: para conocer e identificar al usuario actual para ofrecer información personalizada y segura.  
  
* Paginación:  
    * Orientada a dispositivos: web reponsive adaptada a los diferentes dispositivos ya sea movil, tablet o pc.  
 
## Mockup: LAYOUT HI-FI
  
Por último hemos realizado el diseño de los layouts mediante la herramienta de diseño Adobe XD, donde hemos aplicado todos los patrones de diseño mencionados en el apartado anterior.  
  
El primer layout es de la página de inicio, en la parte superior hemos puesto el logo y un menú horizontal para indicar en que parte de la página web estamos (patrón de navegación) y hacia donde podemos ir (Inicio, Rutas, Sobre Nosotros y Perfil), complementariamente también aparece una foto de perfil donde si pinchas podrás registrarte o logearte en el sistema (patrón de Account registration). En la parte media aparece una foto bonita e incitadora para atraer a todo cliente que tendra que pulsar el botón de reserva ya el cual le llevara a la página de rutas. La parte inferior contiene unos logos que nos llevaran a las redes sociales de la app, el número de teléfono y un boton que nos llevara a la sección de ayuda. 

Tanto la parte inferior como la parte superior se conservan practicamente para el resto de layouts, solo cambiara la parte media.  
  
![index](https://github.com/FranJimenez88/DIU21/blob/master/P3/Layouts/Inicio.png)  

El segundo layout es la sección de rutas, en la cual tenemos en cuenta el patrón de búsqueda añadiendo un buscador al principio, a continuación apareceran 6 rutas cada una con una imagen (se puede consultar su ubicación pulsando en el pin) que da a entender en que consiste, una pequeña descripción, el precio y un botón que nos llevara a la página de información y reserva de esa ruta. Al final aparacere una paginación para ir a otra galería de rutas cumpliendo el patrón de paginación.  
  
![rutas](https://github.com/FranJimenez88/DIU21/blob/master/P3/Layouts/Rutas.png)  
  
El tercer layout consiste en mostrar información más especifica sobre una ruta, una imagen de google maps sobre la ruta a seguir y un formulario (patrón form) para reservar el lugar, en el cual se ofrece ayudas (patrón wizard) como un calendario para introducir la fecha de reserva y unos pasos para realizar la misma y facilitar al usuario.  
  
![rutasInfo](https://github.com/FranJimenez88/DIU21/blob/master/P3/Layouts/RutaReservar.png)  
  
El cuarto y último layout que hemos implementado es el de identificación (patrón de Account registration), en el cual puedes iniciar sesión mediante una cuenta creada en el sistema, o a partir de un acceso rápido a través de google, facebook y twitter. En caso de no tener cuenta tienes la opción de registrarte.  
  
![login](https://github.com/FranJimenez88/DIU21/blob/master/P3/Layouts/Login.png)  
  
  
Para poder ver las transiciones puedes descargar el archivo .xd y abrirlo con AdobeXD en su ordenador: [TapaTourGranada](https://github.com/FranJimenez88/DIU21/blob/master/P3/TapaTourGranada.xd)  

## Documentación: Publicación del Case Study

Valoración del equipo sobre la realización de esta práctica o los problemas surgidos  

Video explicando la practica 3: [Case Study](https://youtu.be/ytkFLyNQzmk)  

La realización de esta práctica nos ha ayudado a analizar mejor los diseños de las distintas páginas que visitamos.Como consecuencia hemos realizado mockups de una página, donde hemos intentado aplicar los mejores estilos y patrones aprendidos en la asignatura, basándonos al mismo tiempo en los mejores aspectos de estas páginas que hemos visitado.

Los únicos problemas que hemos tenido ha sido con Adobe XD, no ha sido difícil de utilizar pero hemos intentado implementar funcionalidades mas extensas, como un slider y nos hemos abrumado ante tanta opciones de realizarlo y su dificultad.

Para ser el primer diseño de interaz que hemos realizado y la primera vez utilizando Adobe XD, pensamos que nos ha quedado una buena página y nos sentimos satisfechos ya que en esta práctica hemos ampliado mucho nuestros conocimientos en el tema.

 
