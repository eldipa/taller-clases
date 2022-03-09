import java.nio.ByteBuffer;
import java.io.File;
import java.io.FileInputStream;
import java.nio.ByteOrder;
import java.io.IOException;

public class ContarPrimos {
    private static final String DATA_FILENAME = "numeros.dat";

    private static final int NUMEROS = 1573888;
    private static final int MAX = 1023;

    public static void main(String[] args) {
        int[] numeros = new int[NUMEROS];
        byte [] tmp = new byte[NUMEROS * 4];
        boolean [] es_primo = new boolean[NUMEROS];

        try {
            FileInputStream f = new FileInputStream(new File(DATA_FILENAME));
            f.read(tmp);
            f.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        ByteBuffer tmpbuf = ByteBuffer.wrap(tmp);
        tmpbuf.order(ByteOrder.LITTLE_ENDIAN);

        for (int i = 0; i < NUMEROS; i++) {
            numeros[i] = tmpbuf.getInt(i*4);
            es_primo[i] = false;
        }

        tmpbuf = null;

        long begin = System.nanoTime();
        for (int divisor = 2; divisor < MAX; ++divisor) {
            for (int i = 0; i < NUMEROS; ++i) {
                if (es_primo[i] || divisor >= numeros[i]) {
                    continue;
                }
                else {
                    if (numeros[i] % divisor == 0) {
                        es_primo[i] = true;
                        continue;
                    }
                }
            }
        }

        long elapsed = System.nanoTime() - begin;

        int cant_primos = 0;
        for (int i = 0; i < NUMEROS; ++i) {
            if (es_primo[i]) {
                ++cant_primos;
            }
        }

        System.out.println("Hay "+cant_primos+" primos.");
        System.out.println("Procesado en "+elapsed/1000000+" milisegundos.");
    }

}

