class A {
    private int a;

    public A(int a) {
        this.a = a;
    }

    public String toString() {
        return "a=" + a;
    }
}

public class B extends A {
    private int a;

    public B() {
        super(20);
        a = 10;
    }

    public B(int a) {
        super(a * 2);
        this.a = a;
    }

    public String getA() {
        return "a=" + a;
    }

    public String toString() {
        return super.toString() + getA();
    }

    public static void main(String[] args) {
        System.out.println(new B(30));
    }
}
