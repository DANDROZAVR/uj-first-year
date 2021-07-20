//package pl.edu.uj.tcs.oop.satori.callThread;
import java.util.concurrent.*;
 
public class Scheduler {
    private final ConcurrentHashMap<Thread, LinkedBlockingQueue<callThread<?>>> actions = new ConcurrentHashMap<>();
    private static class callThread <T> {
        Thread requiredThread, returnThread;
        Callable<T> callableTask;
        Object result;
        boolean isCalced = false, throwException = false;
        Exception returnException;
        callThread(Thread returnThread, Thread t, Callable<T> c) {
            this.returnThread = returnThread;
            this.requiredThread = t;
            this.callableTask = c;
        }
        void setResult(Object result) {
            this.result = result;
        }
        void setCalced() { isCalced = true; }
        void setException(Exception e) {
            this.returnException = e;
            throwException = true;
        }
    }
 
    public <T> T delegate(Thread t, Callable<T> c) throws Exception {
        actions.putIfAbsent(t, new LinkedBlockingQueue<>());
        actions.putIfAbsent(Thread.currentThread(), new LinkedBlockingQueue<>());
        actions.get(t).put(new callThread<>(Thread.currentThread(), t, c));
        while(true) {
            callThread<?> action = actions.get(Thread.currentThread()).take();
            if (action.isCalced) {
                if (action.throwException) throw action.returnException; else return (T)action.result;
            } else {
                try {
                    Object result = action.callableTask.call();
                    action.setCalced();
                    action.setResult(result);
                } catch (Exception e) {
                    action.setCalced();
                    action.setException(e);
                }
                actions.get(action.returnThread).put(action);
            }
        }
    }
}
