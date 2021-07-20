//package pl.edu.uj.tcs.oop.satori.swir;
import java.util.ArrayList;
import java.util.Iterator;
 
public class a implements Iterable<a> {
    public a a;
    boolean isSorted, madeForIterators;
    private ArrayList <Integer> list;
    private a(a father) {
        a = father;
        isSorted  = true;
        list = new ArrayList<Integer>(); // try to remove
    }
    public a() {
        isSorted = false;
        a = new a(this);
        list = new ArrayList<Integer>();
    }
    public String toString() {
        if (madeForIterators) {
            return list.get(0).toString();
        }
        return a.list.toString();
    }
    private void addSortedList(int addElement) {
        boolean isInsered = false;
        for (int index = 0; index < list.size(); ++index)
            if (list.get(index) > addElement) {
                list.add(index, addElement);
                isInsered = true;
                break;
            }
        if (!isInsered) {
            list.add(addElement);
        }
    }
    private void addBackSimpleList(int addElement) {
        list.add(addElement);
    }
    private void addFrontSimpleList(int addElement) {
        list.add(0, addElement);
    }
    public a a(int addElement) {
        if (isSorted) {
            addSortedList(addElement);
            a.addBackSimpleList(addElement);
        } else {
            a.addSortedList(addElement);;
            addBackSimpleList(addElement);
        }
        if (isSorted) return a;
        return this;
    }
    public a a(Integer addElement) {
        if (!isSorted) return a.a(addElement);
        if (isSorted) {
            addSortedList(addElement);
            a.addFrontSimpleList(addElement);
        } else {
            a.addSortedList(addElement);;
            addFrontSimpleList(addElement);
        }
        return this;
    }
 
    public Integer a() {
        Integer temp = list.get(list.size() - 1);
        if (isSorted) {
            list.remove(temp);
            a.list.remove(list.size() - 1);
        } else {
            list.remove(list.size() - 1);
            a.list.remove(temp);
        }
        return temp;
    }
    private a(Integer value) {
        list = new ArrayList<Integer>();
        list.add(value);
        madeForIterators = true;
    }
    public Iterator<a> iterator() {
        return new MyIterator();
    }
    class MyIterator implements Iterator<a> {
        private int index = 0;
        public boolean hasNext() {
             return index < list.size();
            }
            public a next() {
                return new a(list.get(index++));
            }
            public void remove() {
                throw new UnsupportedOperationException("remove");
            }
        }
 
}
