# Contexto del Proyecto
  - **Lenguaje/Stack:** FLTK, C++.
    - Sobre las versiones: el proyecto original utiliza FLTK 1.4.x. Mi intención es compatibilizarlo a FLTK 1.3.x.
- **Características**: FLTerm (Fast Light Terminal, anteriormente «tinyTerm2») es una reescritura de tinyTerm en C++ que utiliza FLTK y libssh2+mbedtls. Se trata de un emulador de terminal multiplataforma con soporte para múltiples pestañas que, al igual que su predecesor, destaca por ser ligero, sencillo y capaz de ejecutar scripts.

El diseño de la interfaz de usuario es minimalista: el programa se inicia sin pestañas, las cuales aparecen automáticamente al establecer una segunda conexión; la barra de desplazamiento permanece oculta hasta que el usuario intenta desplazarse hacia atrás, y cuenta con un único cuadro de diálogo para gestionar las conexiones.

- Rutas: el proyecto se instalará de la siguiente manera:
  - En $PREFIX/usr/local/bin estará el binario principal de la aplicación.
  - En $PREFIX/usr/local/share/flterm/color_themes/ se pondrán todos los temas.

# Reglas de Código (Estilo)
- Sé extremadamente conciso. No des explicaciones teóricas a menos que se pidan explícitamente.
- No agregues comentarios redundantes en el código.
- Prefiere soluciones simples y directas.
- Dividela en módulos manejables (si lo requieres), no hagas una aplicación contenida en un único archivo. Quiero evitar archivos super largos.
- No crees funciones nuevas en el caso de existir nativas.

# Restricciones
- Cada vez que hago una PREGUNTA (ó PRG), responde sin utilizar el código, a menos que lo solicite. Amplía la explicación solo cuando lo pida.
- Para resolver cuestiones técnicas, ignora todo lo mismo que se ignora en .gitignore.
- Nunca ejecutes la instalación de un paquete o CRUD sobre archivos o directorio fuera de este directorio. Sólo preguntarás en el caso de requerir instalar un paquete.

# Permisos sin solicitar autorización

- Cada vez que necesites crear un directorio dentro del proyecto de trabajo (el mismo que este archivo).
- Cuando necesites ejecutar un build del proyecto (con make por ejemplo).
- Cuando necesites ejecutar en test del proyecto.
