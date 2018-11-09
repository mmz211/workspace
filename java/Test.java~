public class Test {  
  
    public static void main(String[] args) {  
        int a = test();  
        System.out.println(a);  
    }  
  
    private static int test() {  
        int count = 5;  
        try {  
            throw new RuntimeException("exception"); 
        } catch (RuntimeException e) {
            
            e.printStackTrace();
            return count += 5;
        }finally {  
            System.out.println("finally");   
            return count;  
        }  
    }  
}  
