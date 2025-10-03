import java.io.*;
import java.net.*;

public class servidor_hola {
    public static void main(String[] args) throws IOException {

        if (args.length != 1) {
            System.err.println("Uso desde consola:  <numero puerto>");
            System.exit(1);
        }
        int numeroPuerto = Integer.parseInt(args[0]);

        try (ServerSocket servidorSocket = new ServerSocket(numeroPuerto)) {

                try (Socket socketCliente = servidorSocket.accept()) {
                    
                    PrintWriter escritor = new PrintWriter(socketCliente.getOutputStream(), true);
                    BufferedReader lector = new BufferedReader(new InputStreamReader(socketCliente.getInputStream()));
                    
                    escritor.println("Conectado! ");

                    String lineaLeida;
                    // Bucle de conversación, solo termina si el cliente se desconecta
                    while ((lineaLeida = lector.readLine()) != null) {                        
                        String respuesta = "hola";
                        escritor.println(respuesta);
                    }
                }            
        } catch (IOException e) {
            System.out.println(" ocurrio una excepcion cuando intentamos escuchar "
                + numeroPuerto + " o esperando por una conexicon");
            System.out.println(e.getMessage());
        }
    }
}