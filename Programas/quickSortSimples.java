import java.util.Scanner;
import java.util.Vector;

// Use java -Xmx4g quickSortSimples para executar com 4GB

public class quickSortSimples{

	public static void main(String[] args){
		Vector<Integer> vetor = new Vector<>();
	
		Scanner s = new Scanner(System.in);
	
		while (s.hasNextInt()) {
    			vetor.add(s.nextInt());
		}
	}
}
