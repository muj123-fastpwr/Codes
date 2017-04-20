
public class Test{

	public static void main(String[] args) {
		
		
		System.out.println("GCD = "+gcd(999,666));
		
		System.out.println("IfPrime = "+ifPrime(79));
		
	}
	
	
	
	
	
	public static long gcd(long a, long b){
		if(b==0)
			return a;
		else
			return gcd(b, a%b);
	}
	
	
	public static boolean ifPrime(long num){
		boolean flag = true;
		if(num==2)
			return true;
		for(int i=2;i<=num/2 +1; i++){
			if(num%i==0){
				flag = false;
				break;
			}
		}
		return flag;
	}
	
	
}
