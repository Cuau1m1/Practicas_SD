import java.io.*;
import java.net.*;
import java.util.Scanner;

public class cliente_entero {
    public static void main(String[] args) throws IOException {
        
        if (args.length != 2) {
            System.err.println("Uso: java Cliente <host> <puerto>");
            System.exit(1);
        }

        String nombreHost = args[0];
        int numeroPuerto = Integer.parseInt(args[1]);

        try (
            Socket socket = new Socket(nombreHost, numeroPuerto);
            PrintWriter escritor = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader lector = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            Scanner teclado = new Scanner(System.in)
        ) {            
            while(true) {
                System.out.print("> ");
                int enteroParaEnviar = teclado.nextInt();
                
                // Enviamos numero al servidor
                escritor.println(enteroParaEnviar);
 
                String respuestaServidor = lector.readLine();
                 if (respuestaServidor == null) {
                    System.out.println("El servidor cerro la conexion");
                    break;
                }
                System.out.println("Respuesta servidor: " + respuestaServidor);
            }

        } catch (Exception e) {
            System.err.println("error: " + e.getMessage());
            System.exit(1);
        }
    }
}