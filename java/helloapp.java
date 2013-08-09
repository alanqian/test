class HelloWorldApp {
    public static void main(String[] args) {
        int t = -1;
        int t1 = t >>> 1;
        int t2 = t >> 1;
        int t3 = t << 1;
        System.out.println(t1);
        System.out.println(t2);
        System.out.println(t3);
        for (int i = 1; i < 6; i++) {
            System.out.println("i=" + i);
        }

        int x = 1;
        int y = 2;
        System.out.println(x+y);
        System.out.format("format: %d,%d\n", x, y);

        test();
    }

    static void test() {
        try
        {
            System.out.println("test(): normal block");
            return;
        }
        finally {
            System.out.println("finally: always execute!");
        }
    }
}

