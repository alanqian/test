// StringDemo reversed a palindrome
public class StringDemo1 {
    public static void main(String[] args) {
        String palindrome = "Dot saw I was Tod";
        StringBuilder t = new StringBuilder(palindrome);
        t.reverse();
        System.out.println(t.toString());
    }
}

