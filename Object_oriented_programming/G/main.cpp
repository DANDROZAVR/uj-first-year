//package pl.edu.uj.tcs.oop.satori.gEasyOk;
 
import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.reflect.*;
import java.util.*;
 
public class SmartFactory {
    public static class HellNoException extends RuntimeException{ }
 
    public static boolean canCast(Method m1, Method m2) { // method m2 -> method m1)
        //System.out.println(m1.getName());
        if (!m1.getName().equals(m2.getName())) return false;
        Class<?>[] p1 = m1.getParameterTypes();
        Class<?>[] p2 = m2.getParameterTypes();
        if (p1.length != p2.length) return false;
        if (m1.getReturnType() != void.class && !m1.getReturnType().isAssignableFrom(m2.getReturnType())) return false;
        for (int i = 0; i < p1.length; ++i) {
            if (!p2[i].isAssignableFrom(p1[i])) return false;
        }
        Class<?>[] ex1 = m1.getExceptionTypes();
        Class<?>[] ex2 = m2.getExceptionTypes();
        for (int i = 0; i < ex2.length; ++i) {
            boolean dad = false;
            for (int j = 0; j < ex1.length; ++j)
                if (ex1[j].isAssignableFrom(ex2[i])) {
                    dad = true;
                    break;
                }
            if (!dad) return false;
        }
        return true;
    }
    public static <T> T fixIt(Class<T> cl, Object obj) {
 
        Object res = Proxy.newProxyInstance(cl.getClassLoader(), new Class[]{cl}, new InvocationHandler() {
            @Override
            public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
                Method res = null;
                if (obj != null)
                    for (Method met : obj.getClass().getMethods())
                        if (canCast(method, met)) {
                            if (res != null) throw new HellNoException();
                            res = met;
                        }
                if (res == null) {
                   if (method.getReturnType() == void.class) return null;
                   return findObject(method.getReturnType());
                } else {
                    try {
                        //res.setAccessible(true);
                        return res.invoke(obj, args);
                    } catch (InvocationTargetException e) {
                        throw e.getCause();
                    } catch (Exception e) {
                        throw new HellNoException();
                    }
                }
            }
            final ArrayList<Object> allReturnTypes = new ArrayList<>();
            public Object findObject(Class<?> needType) {
                try {
                    for (Object o : allReturnTypes)
                        if (needType.isInstance(o))
                            return o;
                    Constructor AAAAAAAAA = needType.getDeclaredConstructor();
                    Object result = AAAAAAAAA.newInstance();
                    allReturnTypes.add(result);
                    for (Field item : needType.getFields()) {
                        if (item.get(result) != null) continue;
                        if (item.getType().isArray() || item.getType().isPrimitive()) continue;
                        boolean calced = false;
                        for (Object o : allReturnTypes)
                            if (item.getType().isInstance(o)) {
                                item.set(result, o);
                                calced = true;
                                break;
                            }
                        if (calced) continue;
                        Object field = findObject(item.getType());
                        item.set(result, field);
                    }
                    return result;
                } catch(Exception e) {
                    throw new HellNoException();
                }
            }
        });
        return (T) res;
    }
    public interface testi {
        public B toStrin(Integer x) throws RuntimeException;
    }
    public static class A {
        String dd;
        String fuf;
        private A() throws Exception {
            dd = "34";
        }
    }
    public static class B {
        public A dich;
    }
    public static class test {
        public B toStrin(Number x) throws IndexOutOfBoundsException { System.out.println("fufel"); return new B();}
    }
    public static void main(String[] args) throws Exception {
        //Warning, raw type
        int x = 1;
        testi col = SmartFactory.fixIt(testi.class, new test());
        try {
            col.toStrin(6);
        } catch (SmartFactory.HellNoException e) {
            System.out.println("Well.... doesn't work.");
        }
 
    }
 
}
