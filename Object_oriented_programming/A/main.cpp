//package pl.edu.uj.tcs.oop.satori.zbiory;
 
public final class Set {
    static final Set EMPTY = emptySet();
    private final int n;
    private final Set[] sets;
    private static Set emptySet() {
        return new Set();
    }
    private Set() {
        n = 0;
        sets = new Set[0];
    }
    private static Set insert(Set main, Set son) {
        if (main.contains(son)) return main;
        return new Set(main.sets, son);
    }
    private Set(Set ... setContainer) {
        n = setContainer.length;
        sets = new Set[setContainer.length];
        System.arraycopy(setContainer, 0, sets, 0, n); // may be copy, not assign
    }
    private Set(Set [] setArray, Set brother) {
        n = setArray.length + 1;
        sets = new Set[n];
        System.arraycopy(setArray, 0, sets, 0, n - 1);
        sets[n - 1] = brother;
    }
    public static Set newSet() {
        return EMPTY;
    }
    public static Set newSet(Set ... setContainer) {
        if (setContainer.length == 0) return EMPTY;
        Set resultSet = new Set();
        for (Set son : setContainer)
            resultSet = insert(resultSet, son);
        return resultSet;
    }
    public int size() { return n; }
    public boolean isEmpty() { return n == 0;}
 
    public boolean equals(Object other) {
        if (!(other instanceof Set)) return false;
        Set otherSet = (Set) other;
        if (otherSet.size() == size() && subsetOf(otherSet)) return true;
        return false;
    }
    public boolean contains(Set element) {
        for (int i = 0; i < n; ++i)
            if (sets[i].equals(element)) return true;
        return false;
    }
    public boolean elementOf(Set father) {
        return father.contains(this);
    }
    public boolean subsetOf(Set superset) {
        for (int i = 0; i < n; ++i)
            if (!superset.contains(sets[i])) return false;
        return true;
    }
    public boolean supersetOf(Set subset) {
        return subset.subsetOf(this);
    }
    public Set union() {
        Set unitedSet = new Set();
        for (int i = 0; i < n; ++i)
            for (Set nextChild : sets[i].sets)
                unitedSet = insert(unitedSet, nextChild);
        return unitedSet;
    }
    public String toString() {
        StringBuilder result = new StringBuilder("{");
        for (int i = 0; i < n; ++i)
            result.append(sets[i].toString());
        result.append("}");
        return result.toString();
    }
    private static class parseStringSegment {
        private int actualEnd = 0;
        private Set parse(String source) {
            int brackets = 0;
            Set returnSet = new Set();
            while(true) {
                if (source.charAt(actualEnd) != '{' && source.charAt(actualEnd) != '}') {
                    ++actualEnd;
                    continue;
                }
                if (brackets > 0 && source.charAt(actualEnd) == '{') {
                    returnSet = insert(returnSet, parse(source));
                    continue;
                }
                if (source.charAt(actualEnd) == '{') ++brackets; else --brackets;
                ++actualEnd;
                if (brackets == 0) break;
            }
            return returnSet;
        }
    }
 
    public static Set parseString(String opis) {
        if (opis.length() == 0) return EMPTY;
        parseStringSegment solution = new parseStringSegment();
        solution.actualEnd = 0;
        return solution.parse(opis);
    }
}
