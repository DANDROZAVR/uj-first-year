//package pl.edu.uj.tcs.oop.satori.OwnStream;
 
 
import java.util.Iterator;
import java.util.function.BiFunction;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;
 
public class StreamUtils {
    public static <T> Stream<T> generateRest(Stream<? extends T> s, BiFunction<? super T, ? super T,? extends T> func) {
        Iterable<T> iter = () -> new Iterator<>() {
            T prev = null, last = null;
            int count = 0;
            final Iterator<? extends T> iter = s.iterator();
            public boolean hasNext() {
                return true;
            }
            public T next() {
                if (iter.hasNext()) {
                    ++count;
                    prev = last;
                    last = iter.next();
                    return last;
                }
                T newElement = func.apply(prev, last);
                prev = last;
                last = newElement;
                return last;
            }
        };
        return StreamSupport.stream(iter.spliterator(), false);
    }
}
