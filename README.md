/*
README.md - Servidor Web en ESP32 con Simulación de Perfil de Instagram
=======================================================================

📌 Objetivo
-----------
Crear un servidor web con ESP32 que simule un perfil de Instagram accesible desde un navegador en la misma red Wi-Fi.

🛠 Requisitos
-------------
- ESP32
- IDE Arduino (con librería ESP32 y WiFi)
- Conexión Wi-Fi
- Navegador web

📄 Descripción del proyecto
---------------------------
El ESP32 se conecta a una red Wi-Fi y lanza un servidor HTTP en el puerto 80.
El usuario puede visitar una página con una interfaz que simula Instagram, incluyendo:

- Imagen de perfil
- Número de publicaciones, seguidores y seguidos
- Botones "Seguir" y "Mensaje"
- Biografía ficticia
- Galería de imágenes (3 fotos)
- Formulario de comentarios en una imagen

📁 Rutas del servidor
---------------------
- `/` → Página principal del perfil
- `/follow` → Incrementa el contador de seguidores y redirige a `/`
- `/foto1` → Muestra la imagen ampliada y formulario de comentario
- `/comentario1` → Procesa y muestra el comentario enviado

🧠 Lógica destacada
-------------------


📈 Incrementar seguidores:
```cpp
void handle_follow() {
  followers++;
  server.sendHeader("Location", "/");
  server.send(303);
}
