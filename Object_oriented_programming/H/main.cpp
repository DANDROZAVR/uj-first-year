//package pl.edu.uj.tcs.oop.satori.OwnListOfLists;
 
import java.util.*;
 
public class ArrayListSqrCloned <E>  implements Iterable<ArrayList<E>> {
    private ArrayList<ArrayList<E>> items = new ArrayList<>();
    public ArrayListSqrCloned(){};
    /*public ArrayListSqrCloned(ArrayListSqrCloned<? extends ArrayList<? extends E>> main1) {
        this((Collection<? extends ArrayList<? extends E>>) main1.items);
    }*/
    public ArrayListSqrCloned(Collection<? extends ArrayList<? extends E>> c) {
        Object[] o = c.toArray();
        for (int i = 0; i < o.length; ++i)
            add((ArrayList<E>) o[i]);
    }
    private ArrayList<E> clone(ArrayList<? extends E> cloneable) {
        return new ArrayList<>(cloneable);
    }
    public boolean add(ArrayList<? extends E> item) {
        items.add(clone(item));
        return true;
    }
    public void add(int index, ArrayList<? extends E> item) {
        items.add(index, clone(item));
    }
    public boolean addAll(Collection<? extends ArrayList<? extends E>> c) {
        Object[] a = c.toArray();
        for (Object o : a)
            add((ArrayList<E>) o);
        return c.size() > 0;
    }
    public boolean addAll(int index, Collection<? extends ArrayList<? extends E>> c) {
        if (index < 0 || index >= size()) throw new IndexOutOfBoundsException();
        for (Object item : c)
            add(index++, (ArrayList<E>) item);
        return c.size() > 0;
    }
    public ArrayList<E> set(int index, ArrayList<? extends E> item) {
        return items.set(index, clone(item));
    }
    public void clear() {
        items.clear();
    }
    public boolean contains(Object o) {
        if (!(o instanceof ArrayList)) return false;
        for (int i = 0; i < items.size(); ++i)
            if (items.get(i).equals((ArrayList<?>)o))
                return true;
        return false;
    }
    public boolean containsAll(Collection<?> c) {
        Object[] o = c.toArray();
        for (Object item : o)
            if (!contains(item)) return false;
        return true;
    }
    public ArrayList<E> get(int index) {
        return items.get(index);
    }
    public boolean equals(Object o) {
        if (!(o instanceof ArrayListSqrCloned<?>)) return false;
        ArrayListSqrCloned<?> other = (ArrayListSqrCloned<?>) o;
        if (items.size() != other.items.size()) return false;
        for (int i = 0; i < items.size(); ++i) {
            boolean equ = items.get(i).equals(other.items.get(i));
            if (!equ) return false;
        }
        return true;
    }
    public int indexOf(Object o) {
        if (!(o instanceof ArrayList)) return -1;
        for (int i = 0; i < items.size(); ++i)
            if (items.get(i).equals((ArrayList<?>)o)) return i;
        return -1;
    }
    public int lastIndexOf(Object o) {
        if (!(o instanceof ArrayList)) return -1;
        for (int i = items.size() - 1; i >= 0; --i)
            if (items.get(i).equals((ArrayList<?>)o)) return i;
        return -1;
    }
    public boolean isEmpty(){ return items.isEmpty(); }
    public Iterator<ArrayList<E>> iterator() { return items.iterator(); }
    public ListIterator<ArrayList<E>> listIterator(int index) { return items.listIterator(index); }
    public ListIterator<ArrayList<E>> listIterator() { return items.listIterator(); }
    public int hashCode() { return items.hashCode(); }
    public boolean remove(Object o) {
        if (!(o instanceof ArrayList)) return false;
        for (int i = 0; i < items.size(); ++i)
            if (items.get(i).equals((ArrayList<?>)o)) {
                items.remove(i);
                return true;
            }
        return false;
    }
    public ArrayList<E> remove(int index) {
        return items.remove(index);
    }
    public boolean removeAll(Collection<?> c) {
        Object[] o = c.toArray();
        boolean del = false;
        for (Object value : o) {
            if (remove(value)) del = true;
        }
        return del;
    }
    public int size(){ return items.size(); }
}
