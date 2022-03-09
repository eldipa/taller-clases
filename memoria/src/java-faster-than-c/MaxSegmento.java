import java.nio.ByteBuffer;
import java.io.File;
import java.io.FileInputStream;
import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.nio.ByteOrder;
import java.io.IOException;

class Punto {
    public int x;
    public int y;
};

class Segmento {
    public Punto a;
    public Punto b;
};

public class MaxSegmento {
    private static final String DATA_FILENAME = "numeros.dat";
    private static final int NUMEROS =      1573888;
    private static final int PUNTOS =       NUMEROS/2;
    private static final int SEGMENTOS =    PUNTOS/2;

    private static final int ROUNDS = 1000;

    public static void main(String[] args) {
        Segmento[] segmentos = new Segmento[SEGMENTOS];

        byte [] tmp = new byte[NUMEROS * 4];
        try {
            FileInputStream f = new FileInputStream(new File(DATA_FILENAME));
            f.read(tmp);
            f.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        ByteBuffer tmpbuf = ByteBuffer.wrap(tmp);
        tmpbuf.order(ByteOrder.LITTLE_ENDIAN);

        for (int i = 0; i < SEGMENTOS; i++) {
            Punto a = new Punto();
            a.x = tmpbuf.getInt(i*16 + 0);
            a.y = tmpbuf.getInt(i*16 + 4);

            Punto b = new Punto();
            b.x = tmpbuf.getInt(i*16 + 8);
            b.y = tmpbuf.getInt(i*16 + 12);

            segmentos[i] = new Segmento();
            segmentos[i].a = a;
            segmentos[i].b = b;
        }

        tmp = null;
        tmpbuf = null;

        long begin = System.nanoTime();

        int max_norma_al_cuadrado = 0;
        int max_segmento_i = 0;
        for (int r = 0; r < ROUNDS; ++r) {
            for (int i = 0; i < SEGMENTOS; ++i) {
                int norma_al_cuadrado =
                    (segmentos[i].a.x - segmentos[i].b.x) * (segmentos[i].a.x - segmentos[i].b.x) +
                    (segmentos[i].a.y - segmentos[i].b.y) * (segmentos[i].a.y - segmentos[i].b.y);
                if (norma_al_cuadrado > max_norma_al_cuadrado) {
                    max_segmento_i = i;
                    max_norma_al_cuadrado = norma_al_cuadrado;
                }
            }
        }

        long elapsed = (System.nanoTime() - begin);

        System.out.println("Segmento mas largo: " + max_segmento_i);
        System.out.println("Procesado en "+elapsed/1000000+" milisegundos.");
    }
}


