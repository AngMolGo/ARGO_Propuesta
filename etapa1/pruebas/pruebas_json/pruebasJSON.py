import json

def enviar_comando(mensaje):
    # Simula el envío del mensaje a través de la comunicación (adaptar según la tecnología real)
    print(f"Enviando comando: {mensaje}")

# Crear el comando como un diccionario JSON
comando = {
    "destino":"llantas",
    "comando": "iniciar_proceso",
    "parametros": {
        "nombre_proceso": "proceso_123",
        "parametro_adicional": 42
    }
}

# Convertir el comando a una cadena JSON
mensaje_json = json.dumps(comando)

# Llamar a la función para enviar el mensaje
enviar_comando(mensaje_json)
