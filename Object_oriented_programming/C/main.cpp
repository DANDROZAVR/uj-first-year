//package pl.edu.uj.tcs.oop.satori.zdalnaLista;
 
public class RemoteListAdapter<T> {
    private final RemoteList<T> list;
    private T firstElement, secondElement;
    private boolean hasFirst = false, hasSecond = false, isInConstructor;
    private int beforeEmptyList = 0, afterEmptyList = 0, wasEmptyList;
    public RemoteListAdapter(RemoteList<T> rl) {
        list = rl;
        isInConstructor = true;
        try {
            pop();
            try {
                pop();
            } catch (EmptyList ignored) {
            }
        } catch (EmptyList ignored) {
        }
        isInConstructor = false;
    }
    public T pop() throws EmptyList {
        T remotePop = null;
        if (wasEmptyList == 2 && !hasFirst) throw new EmptyList();
        while(wasEmptyList != 2) {
            try {
                remotePop = list.pop();
                if (wasEmptyList == 0) ++beforeEmptyList;
                break;
            } catch (EmptyList e) {
                wasEmptyList++;
                if (wasEmptyList == 2 && !hasFirst) throw e;
            } catch (TimeLimitExceded ignored) {
            } catch (MissingElement e) {
                if (wasEmptyList > 0) ++afterEmptyList;
                T temp = firstElement;
                firstElement = secondElement;
                secondElement = temp;
                if (wasEmptyList == 1 && afterEmptyList == beforeEmptyList) {
                    wasEmptyList = 2;
                }
            } catch (FakeElement e) {
                if (hasSecond) hasSecond = false; else hasFirst = false;
                if (wasEmptyList == 0) --beforeEmptyList;
                isInConstructor = true;
                pop();
                isInConstructor = false;
            }
        }
        if (wasEmptyList == 2 && !hasFirst) throw new EmptyList();
        if (isInConstructor && wasEmptyList != 2) {
            if (!hasFirst) {
                hasFirst = true;
                firstElement = remotePop;
            } else
            if (!hasSecond) {
                hasSecond = true;
                secondElement = remotePop;
            }
            return null;
        }
        T returnValue = firstElement;
        firstElement = secondElement;
        secondElement = remotePop;
        hasFirst = hasSecond;
        if (wasEmptyList == 2) hasSecond = false;
        return returnValue;
    }
    public boolean hasNext() {
        return hasFirst;
    }
}
