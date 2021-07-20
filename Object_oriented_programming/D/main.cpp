//package pl.edu.uj.tcs.oop.satori.map_list_converter;
 
import java.util.*;
 
public class Switch {
    public static <T> Map<Integer, T> toMap(List<T> initList) {
        return new AbstractMap<>() {
            final List<T> list = initList;
            private transient Set<Map.Entry<Integer, T>> set;
            @Override
            public T remove(Object key){ throw new UnsupportedOperationException();}
            @Override
            public Set<Entry<Integer, T>> entrySet() {
                if (set == null) {
                    set = new AbstractSet<>() {
                        public Iterator<Map.Entry<Integer, T>> iterator() {
                            return new Iterator<>() {
                                int idx = 0;
 
                                @Override
                                public boolean hasNext() {
                                    return idx < list.size();
                                }
 
                                @Override
                                public Entry<Integer, T> next() {
                                    if (idx >= list.size()) return null;
                                    ++idx;
                                    return new AbstractMap.SimpleEntry<>(idx - 1, list.get(idx - 1)) {
                                    };
                                }
                            };
                        }
                        public int size() {
                            return list.size();
                        }
                        @Override
                        public boolean remove(Object o) {
                            throw new UnsupportedOperationException();
                        }
                    };
                }
                return set;
            }
        };
    }
    public static <T> List<T> toList(Map<Integer, T> initMap) {
        return new AbstractList<>() {
            final Map<Integer, T> map = initMap;
 
            private void check() {
                for (int i = 0; i < map.size(); ++i)
                    if (!map.containsKey(i)) throw new MapIsNotListException();
            }
 
            @Override
            public T get(int index) {
                check();
                return map.get(index);
            }
 
            @Override
            public int size() {
                return map.size();
            }
        };
    }
 
}
