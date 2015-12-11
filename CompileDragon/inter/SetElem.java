package inter;

import lexer.*; 
import symbols.*;

public class SetElem extends Stmt {
	public Id array;
	public Exper index;
	public Exper exper;
	public SetElem(Access x, Exper y) {
		array = x.array;
		index = x.index;
		exper = y;
		if (check(x.type, exper.type) == null) 
			error("type error");
	}
	public Type check(Type p1, Type p2) {
		if (p1 instanceof Array || p2 instanceof Array)
			return null;
		else if (p1 == p2) 
			return p2;
		else if (Type.numeric(p1) && Type.numeric(p2)) 
			return p2;
		else
			return null;
	}
	public void gen(int b, int a) {
		String s1 = index.reduce().toString();
		String s2 = exper.reduce().toString();
		emit(array.toString() + " [ " + s1 + " ] = " + s2);
	}
}