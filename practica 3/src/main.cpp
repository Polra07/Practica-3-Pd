#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "Nautilus";  // Nombre de la red Wi-Fi
const char* password = "20000Leguas";  // Contraseña de la red Wi-Fi

WebServer server(80);  // Crear un servidor web en el puerto 80

int followers = 34000000;  // Número inicial de seguidores

String HTML = "<!DOCTYPE html>"
"<html lang=\"es\">"
"<head>"
"    <meta charset=\"UTF-8\">"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"    <title>Perfil de Instagram</title>"
"    <style>"
"        body {"
"            font-family: Arial, sans-serif;"
"            background-color: #f0f0f0;"
"            text-align: center;"
"        }"
"        .profile-container {"
"            max-width: 400px;"
"            margin: auto;"
"            background: white;"
"            padding: 20px;"
"            border-radius: 10px;"
"            box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1);"
"        }"
"        .profile-header {"
"            display: flex;"
"            align-items: center;"
"            justify-content: space-around;"
"        }"
"        .profile-pic {"
"            width: 100px;"
"            height: 100px;"
"            border-radius: 50%;"
"            border: 3px solid #ccc;"
"        }"
"        .stats {"
"            text-align: center;"
"        }"
"        .stats p {"
"            margin: 5px;"
"            font-weight: bold;"
"        }"
"        .bio {"
"            margin-top: 10px;"
"            font-size: 14px;"
"        }"
"        .buttons {"
"            margin-top: 10px;"
"        }"
"        .btn {"
"            padding: 8px 15px;"
"            margin: 5px;"
"            border: none;"
"            cursor: pointer;"
"            border-radius: 5px;"
"        }"
"        .btn.follow {"
"            background-color: #0095f6;"
"            color: white;"
"        }"
"        .btn.message {"
"            background-color: #e0e0e0;"
"        }"
"        .gallery {"
"            display: grid;"
"            grid-template-columns: repeat(3, 1fr);"
"            gap: 5px;"
"            margin-top: 15px;"
"        }"
"        .gallery img {"
"            width: 100%;"
"            border-radius: 5px;"
"        }"
"    </style>"
"    <script>"
"        function increaseFollowers() {"
"            fetch('/follow');"
"        }"
"    </script>"
"</head>"
"<body>"
"    <div class=\"profile-container\">"
"        <div class=\"profile-header\">"
"            <img class=\"profile-pic\" src=\"https://i.pinimg.com/736x/2a/8c/83/2a8c839914f9facd6fbaaef5abf9ff38.jpg\" alt=\"Foto de perfil\">"
"            <div class=\"stats\">"
"                <p>3</p>"
"                <p>Publicaciones</p>"
"            </div>"
"            <div class=\"stats\">"
"                <p id=\"followers\">" + String(followers) + "</p>"
"                <p>Seguidores</p>"
"            </div>"
"            <div class=\"stats\">"
"                <p>1</p>"
"                <p>Seguidos</p>"
"            </div>"
"        </div>"
"        <div class=\"bio\">"
"            <h3>milokete777</h3>"
"            <p>📍 fuengirola | ludopata | divorciao</p>"
"            <p>jugador de petanca</p>"
"        </div>"
"        <div class=\"buttons\">"
"            <button class=\"btn follow\" onclick=\"increaseFollowers()\">Seguir</button>"
"            <button class=\"btn message\">Mensaje</button>"
"        </div>"
"        <div class=\"gallery\">"
"            <a href=\"/foto1\"><img src=\"https://upload.wikimedia.org/wikipedia/commons/thumb/c/ce/IllojuanESLAND2022.png/440px-IllojuanESLAND2022.png\" alt=\"Imagen 1\"></a>"
"            <a href=\"/foto2\"><img src=\"https://www.orquestadeextremadura.com/wp-content/uploads/2017/05/en-familia-bestiario-del-circo-con-pepe-viyuela.jpg\" alt=\"Imagen 2\"></a>"
"            <a href=\"/foto3\"><img src=\"https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTN6dczXTcGmaxpZJfESWiGmlFTW8xH-iQrBg&s\" alt=\"Imagen 3\"></a>"
"        </div>"
"    </div>"
"</body>"
"</html>";

// Manejar la ruta raíz (/)
void handle_root() {
  server.send(200, "text/html", HTML);  // Enviar el contenido HTML como respuesta
}

// Manejar la ruta para aumentar los seguidores
void handle_follow() {
  followers++;  // Incrementar el número de seguidores
  server.sendHeader("Location", "/");  // Redirigir al perfil
  server.send(303);  // Responder con redirección HTTP
}

// Manejar la ruta para la foto 1
void handle_foto1() {
  String fotoHTML = "<html><body>"
                    "<h1>Foto 1</h1>"
                    "<img src=\"https://upload.wikimedia.org/wikipedia/commons/thumb/c/ce/IllojuanESLAND2022.png/440px-IllojuanESLAND2022.png\" alt=\"Imagen 1\" style=\"width:100%;\">"
                    "<form action=\"/comentario1\" method=\"POST\">"
                    "<textarea name=\"comentario\" placeholder=\"Escribe tu comentario...\" required></textarea><br>"
                    "<button type=\"submit\">Comentar</button>"
                    "</form>"
                    "</body></html>";
  server.send(200, "text/html", fotoHTML);
}

// Manejar los comentarios en la foto 1
void handle_comentario1() {
  if (server.hasArg("comentario")) {
    String comentario = server.arg("comentario");
    Serial.println("Comentario en foto 1: " + comentario);
  }
  server.send(200, "text/html", "<h1>Gracias por tu comentario</h1><a href=\"/\">Volver</a>");
}

// Configuración inicial
void setup() {
  Serial.begin(115200);  // Iniciar la comunicación serial a 115200 baudios
  Serial.println("Try Connecting to ");
  Serial.println(ssid);  // Mostrar el nombre de la red Wi-Fi en el monitor serial

  // Conectar al Wi-Fi
  WiFi.begin(ssid, password);  // Iniciar conexión Wi-Fi

  // Verificar si la conexión se realiza correctamente
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);  // Esperar 1 segundo
    Serial.print(".");  // Mostrar punto cada segundo mientras intenta conectar
  }

  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  // Mostrar la IP obtenida del ESP32

  // Configurar las rutas
  server.on("/", handle_root);  // Ruta raíz
  server.on("/follow", handle_follow);  // Ruta para seguir
  server.on("/foto1", HTTP_GET, handle_foto1);  // Ruta para foto 1
  server.on("/comentario1", HTTP_POST, handle_comentario1);  // Ruta para comentar en foto 1
  
  server.begin();  // Iniciar el servidor HTTP
  Serial.println("HTTP server started");  // Confirmar que el servidor ha comenzado
}

void loop() {
  server.handleClient();  // Manejar las solicitudes de los clientes
}
