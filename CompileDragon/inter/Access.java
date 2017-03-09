package inter;

import lexer.*;
import symbols.*;

public class Access extends Op {
	public Id array;
	public Exper index;
	public Access(Id a, Exper i, Type p) {
		super(new Word("[]", Tag.INDEX), p);
		array = a;
		index = i;
	}
	public Exper gen() { 
		return new Access(array, index.reduce(), type);
	}
	public void jumping(int t, int f) { emitjumps(reduce().toString(), t, f); }
	public String toString() {
		return array.toString() + " [ " + index.toString() + " ] ";
	}
}