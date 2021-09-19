var http = require("http");
var url = require("url");
var fs = require("fs");
var path = require("path");
var socketio = require("socket.io");

const request = require('request');
const nodemailer= require('nodemailer');


var MongoClient = require('mongodb').MongoClient;
var MongoServer = require('mongodb').Server;
var mimeTypes = { "html": "text/html", "jpeg": "image/jpeg", "jpg": "image/jpeg", "png": "image/png", "js": "text/javascript", "css": "text/css", "swf": "application/x-shockwave-flash" };



//Declaramos el transportador para enviar correos, con una cuenta creada unicamente para enviar mensaje a los usuarios
const tranporter = nodemailer.createTransport({
	
	service:'gmail',
	auth: {
		user:'servidordomativodsd3@gmail.com',
		pass: 'claveDSD'
	}
});


//Definimos los valores de la API de openWeather

let apiKey="ef0a7fe4932e717d50fa9f9de9db39d0";
let ciudad='Granada';
let urlApi=`http://api.openweathermap.org/data/2.5/weather?q=${ciudad}&appid=${apiKey}`;


//Variables de los sensores para el servidor inicializados a un valor
var temperatura = 20;
var luminosidad = 60;
var humedad;
var viento;

//Variables de los estados de los actuadores del servidor inicializados a un valor

var estadoPersianas = "subir";
var estadoAire = "apagar";
var estadoAgente = "encender";
var estadoAspersor= "apagar";
var estadoToldo="subir";


//Vector de alarmas de agente
var alarmas = Array();

//Umbrales predefinidos para el agente del servidor
var umbralTemperatura = 35;
var umbralMaxLuminosidad = 80;
var umbrarHumedad=30;



//Peticion para obtener los datos de Granada en openWeather de los cuales nos quedamos con la humedad y el viento
request(urlApi, function(err, response, body){
	if(err){
		console.log('error:',err);
	}
	else{
		let info= JSON.parse(body);
		humedad=info.main.humidity;
		viento=info.wind.speed;
	}
});



//Creamos el servidor con pagina inicial en la de sensores.html
var httpServer = http.createServer(
	function (request, response) {
		var uri = url.parse(request.url).pathname;
		if (uri == "/") uri = "/sensores.html";
		var fname = path.join(process.cwd(), uri);
		fs.exists(fname, function (exists) {
			if (exists) {
				fs.readFile(fname, function (err, data) {
					if (!err) {
						var extension = path.extname(fname).split(".")[1];
						var mimeType = mimeTypes[extension];
						response.writeHead(200, mimeType);
						response.write(data);
						response.end();
					}
					else {
						response.writeHead(200, { "Content-Type": "text/plain" });
						response.write('Error de lectura en el fichero: ' + uri);
						response.end();
					}
				});
			}
			else {
				console.log("Peticion invalida: " + uri);
				response.writeHead(200, { "Content-Type": "text/plain" });
				response.write('404 Not Found\n');
				response.end();
			}
		});
	}
);


//Nos conectamos a mongoDB 

MongoClient.connect("mongodb://localhost:27017/", { useNewUrlParser: true, useUnifiedTopology: true }, function (err, db) {
	httpServer.listen(8080);
	var io = socketio(httpServer);
	var usuariosSistema = Array();

	var dbo = db.db("sistemaDomotica");
	//creamos la sabe de datos donde guardaremos las acciones de los cambios en los sensores

	dbo.createCollection("acciones", function (err, collection) {
		io.sockets.on('connection',
			function (client) {
				
				//Nada mas acceder a la página, guardamos el host, puerto y fecha en una lista de usuarios

				usuariosSistema.push({ host: client.request.connection.remoteAddress, port: client.request.connection.remotePort });

				//Enviamos los valores iniciales a todos los usuarios del sistema

				io.sockets.emit('enviarValores', { temperatura: temperatura, luminosidad: luminosidad, aire: estadoAire, persiana: estadoPersianas, agente: estadoAgente, humedad:humedad, aspersor:estadoAspersor, toldo:estadoToldo, viento:viento });

				//Enviamos a sensores los usuarios activos del sistema, para que este los muestre 
				io.sockets.emit('usuariosSistema', usuariosSistema);


				//Accion donde se recibe y guarda la actuacion sobre las persianas

				client.on('accion-persiana', function (data) {
					estadoPersianas = data.accion;
					enviarDatos();
				});

				//Accion donde se recibe y guarda la actuacion sobre el aire
				client.on('accion-aire', function (data) {
					estadoAire = data.accion;
					enviarDatos();
				});

				

				//Accion donde se recibe y guarda la actuacion sobre el agente
				client.on('accion-agente', function (data) {
					estadoAgente = data.accion;
					enviarDatos();
				});

				//Accion donde se recibe y guarda la actuacion sobre los aspersores
				client.on('accion-aspersor', function (data) {
					estadoAspersor = data.accion;
					enviarDatos();
				});

				//Accion donde se recibe y guarda la actuacion sobre los toldos
				client.on('accion-toldo', function(data){
					estadoToldo=data.accion;
					enviarDatos();
				});

				//El servidor escucha un cambio en los sensores, lo guarda en la base de datos y realiza los cambios

				client.on('cambio-sensor', function (data) {
					dbo.collection("acciones").insertOne(data, { safe: true }, function (err, result) { });
					realizarCambio(data);
				});

				//El servidor escucha la eliminacion del historial, donde se inicializa a vacio el array de alarmas del agente
				client.on('eliminar-historial', function () {
					alarmas = Array();
					io.sockets.emit('vaciarLista', { alarmas: alarmas });
				});

				//El socket recibe la peticion de enviar correo

				client.on('enviar-correo',function(data){
					
					//Se crea el mensaje a enviar

					let mensaje="El estado de la casa es: \nTemperatura---> "+temperatura+"\nLuminosidad--->"+luminosidad+"\nHumedad--->"+humedad+
					"\nViento--->"+viento+"\nPersianas--->"+estadoPersianas+"\nAire--->"+estadoAire+"\nAspersores--->"+estadoAspersor+"\nToldos--->"+estadoToldo+"\nAgente--->"+estadoAgente;

					//Se define las opciones del email(escritor, destino,asunto y el mensaje)
					const mailOptions={
						from:'servidordomativodsd3@gmail.com' ,
						to: data.correo,
						subject:'Informe estado de la casa domótica',
						text: mensaje
					};

					//Se manda el email, en caso de acierto se notifica al usuario que ha realizado la peticion
					tranporter.sendMail(mailOptions,function(error, info){
						if(error)
						{
							console.log(error);
						}else{
							client.emit('confirmar-correo',{});
						}
					});

				});

				//Funcion donde se actualizan las variables de los sensores, pasan y pasan por el agente antes de ser enviados
				function realizarCambio(data) {
					if (data.cambio == "luminosidad") {
						luminosidad = data.valor;
					}
					else if (data.cambio == "temperatura") {
						temperatura = data.valor;
					}
					else if(data.cambio == "humedad")
					{
						humedad = data.valor;
					}
					else if(data.cambio=="viento")
					{
						viento=data.valor;
					}

					gestorAgente();

					enviarDatos();
				}

				//Envia a todos los usuarios del sistema los cambios realizado
				function enviarDatos() {
					io.sockets.emit('enviarValores', { temperatura: temperatura, luminosidad: luminosidad, aire: estadoAire, persiana: estadoPersianas, alarmas: alarmas, agente: estadoAgente, humedad:humedad, aspersor:estadoAspersor,  toldo:estadoToldo, viento:viento });
				}

				//Metodo por donde se pasa antes de enviar los valores nuevos al haber cambio del sensor,
				
				function gestorAgente() {
					alarmas = Array();

					 //Si el agente esta apagado, no entra directamente

					if (estadoAgente=="encender") {

						if (temperatura >= umbralTemperatura && luminosidad >= umbralMaxLuminosidad && estadoPersianas == "subir") {
							alarmas.push("La temperatura y luminosidad superan el umbral máximo por lo que se han cerrado las persianas");
							estadoPersianas = "bajar";
						}
						if (temperatura >= umbralTemperatura && estadoPersianas == "subir") {
							alarmas.push("La temperatura supera el umbral máximo por lo que se han cerrado las persianas");
							estadoPersianas = "bajar";
						}
						if (temperatura >= 40 && estadoAire == "apagar") {
							alarmas.push("La temperatura supera el umbral máximo por lo que se ha encendido el aire");
							estadoAire = "encender";
						}
						if(temperatura <=15 && estadoAire=="encender")
						{
							alarmas.push("La temperatura es baja por lo que se ha desactivado el aire");
							estadoAire = "apagar";
						}
						if (luminosidad >= umbralMaxLuminosidad && estadoPersianas == "subir") {
							alarmas.push("La luminosidad supera el umbral máximo por lo que se han cerrado las persianas");
							estadoPersianas = "bajar";
						}
						if(estadoAspersor=="apagar" && humedad<=umbrarHumedad)
						{
							alarmas.push("La humedad del jardín es muy baja por lo que se han activado los aspersores");
							estadoAspersor="encender";
						}
						if(estadoAspersor=="encender" && humedad>=70)
						{
							alarmas.push("La humedad del jardín es alta por lo que se han desactivado los aspersores");
							estadoAspersor="apagar";
						}
						if(estadoToldo=="subir" && viento>=35) {
							alarmas.push("La velocidad del viento es alta por lo que se han bajado los toldos");
							estadoToldo="bajar";
						}
						if(estadoToldo=="bajar" && viento<30 && temperatura>=35)
						{
							alarmas.push("La velocidad del viento es baja y la temperatura es alta por lo que se han subido los toldos");
							estadoToldo="subir";
						}
						
						
					}



				}

			});
	});
});

console.log("Servicio MongoDB iniciado");
